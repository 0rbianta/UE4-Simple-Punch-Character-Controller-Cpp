// Fill out your copyright notice in the Description page of Project Settings.


#include "RudeCharacterAnim.h"

#include "CombatComponent.h"
#include "RudeCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void URudeCharacterAnim::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	RudeCharacter = Cast<ARudeCharacter>(TryGetPawnOwner());
}


void URudeCharacterAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (RudeCharacter)
	{
		FVector VelocityVec = RudeCharacter->GetVelocity();
		VelocityVec.Z = 0;
		Velocity = VelocityVec.Size();

		Direction = CalculateDirection(VelocityVec, RudeCharacter->GetActorRotation());
		// UE_LOG(LogTemp, Warning, TEXT("%f"), Direction);
		
		
		bInAir = RudeCharacter->GetCharacterMovement()->IsFalling();
		bIsAiming = RudeCharacter->Combat->bIsAiming;
		bIsFiring = RudeCharacter->Combat->bIsFiring;
	}
	
}
