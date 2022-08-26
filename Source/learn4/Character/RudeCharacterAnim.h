// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RudeCharacterAnim.generated.h"

/**
 * 
 */
UCLASS()
class LEARN4_API URudeCharacterAnim : public UAnimInstance
{
	GENERATED_BODY()

private:
	class ARudeCharacter* RudeCharacter;

public:
	UPROPERTY(BlueprintReadOnly)
	float Velocity;
	UPROPERTY(BlueprintReadOnly)
	float Direction;
	UPROPERTY(BlueprintReadOnly)
	bool bInAir;
	UPROPERTY(BlueprintReadOnly)
	bool bIsAiming;
	UPROPERTY(BlueprintReadOnly)
	bool bIsFiring;


	
protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
};
