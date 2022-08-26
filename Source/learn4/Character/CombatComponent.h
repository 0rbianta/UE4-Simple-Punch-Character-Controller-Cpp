// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "learn4/NPC/NPC.h"
#include "CombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARN4_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();

public:
	bool bIsAiming;
	bool bIsFiring;
	
public:
	void SetAiming(bool IsAiming);
	void SetFiring(bool IsFiring);

private:
	UFUNCTION()
	void PunchTimer_Elapsed(ANPC* AffectedNPC);
	
private:
	class ARudeCharacter* RudeCharacter;
	UPROPERTY(EditAnywhere, meta=( AllowPrivateAccess = true ))
	class USoundBase* PunchSound;
	struct FTimerHandle TimerHandlePunch;
	
protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
