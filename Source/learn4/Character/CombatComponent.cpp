// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatComponent.h"

#include "RudeCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "learn4/NPC/NPC.h"

UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	RudeCharacter = Cast<ARudeCharacter>(GetOwner());
}


void UCombatComponent::SetAiming(bool IsAiming)
{
	bIsAiming = IsAiming;
	if (RudeCharacter)
	{
		RudeCharacter->GetCharacterMovement()->MaxWalkSpeed = bIsAiming ? 100.f : 350.f;
		RudeCharacter->GetCharacterMovement()->bOrientRotationToMovement = !bIsAiming;
		RudeCharacter->GetCharacterMovement()->SetJumpAllowed(!bIsAiming);
	}
}

void UCombatComponent::SetFiring(bool IsFiring)
{
	bIsFiring = IsFiring;
	if (IsFiring)
	{
		RudeCharacter->GetCharacterMovement()->Deactivate();
	}
	else
	{
		RudeCharacter->GetCharacterMovement()->Activate();
	}

	FVector Start = RudeCharacter->GetActorLocation() + RudeCharacter->GetActorForwardVector() * 40;
	FVector End = Start + RudeCharacter->GetActorForwardVector() * 100;

	FHitResult HitResult;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECollisionChannel::ECC_Pawn
	);

	
	UE_LOG(LogTemp, Warning, TEXT("%i"), IsHit ? 1 : 0);
	
	ANPC *AffectedNPC = Cast<ANPC>(HitResult.GetActor());
	if (AffectedNPC)
	{
		FTimerDelegate TimerDelegatePunch;
		TimerDelegatePunch.BindUFunction(this, "PunchTimer_Elapsed", AffectedNPC);
		GetWorld()->GetTimerManager().SetTimer(TimerHandlePunch, TimerDelegatePunch, .5f, false);
	}
	
}

void UCombatComponent::PunchTimer_Elapsed(ANPC* AffectedNPC)
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandlePunch);
	if (AffectedNPC == nullptr)	return;
	if (PunchSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PunchSound, 1.2f, 1.f, 0);
	}
	AffectedNPC->TakeDamage(5, FDamageEvent(), RudeCharacter->GetInstigatorController(), RudeCharacter);
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}


void UCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsAiming)
	{
		FRotator CameraRotation = RudeCharacter->PlayerCamera->GetComponentRotation();
		CameraRotation.Pitch = 0;
		CameraRotation.Roll = 0;
		RudeCharacter->SetActorRotation(CameraRotation);
	}

}

