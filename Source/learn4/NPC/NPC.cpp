// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "learn4/Character/CombatComponent.h"
#include "learn4/Character/RudeCharacter.h"

ANPC::ANPC()
{
	PrimaryActorTick.bCanEverTick = true;
	
	
	SetCanBeDamaged(true);
	GetMesh()->AddLocalOffset(GetActorUpVector() * -90);
	GetMesh()->AddLocalRotation(FRotator(0, -90, 0));

}


void ANPC::BeginPlay()
{
	Super::BeginPlay();

	OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeDamage);
}

void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ANPC::OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                        class AController* InstigatedBy, AActor* DamageCauser)
{

	if (HurtSound)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), HurtSound, 1.2f, 1.f, 0);
	}
	
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);

	FTimerDelegate TimerDelegateDestroy;
	TimerDelegateDestroy.BindUFunction(this, "TimerDestroy_Elapsed");
	GetWorld()->GetTimerManager().SetTimer(TimerHandleDestroy, TimerDelegateDestroy, 5.f, false);
}

void ANPC::TimerDestroy_Elapsed()
{
	Destroy();
}
