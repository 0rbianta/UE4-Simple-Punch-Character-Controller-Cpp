// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC.generated.h"

UCLASS()
class LEARN4_API ANPC : public ACharacter
{
	GENERATED_BODY()

public:
	ANPC();

private:
	UPROPERTY(EditAnywhere, meta=( AllowPrivateAccess = true ))
	class USoundBase* HurtSound;
	struct FTimerHandle TimerHandleDestroy;

public:
	UFUNCTION()
	void TimerDestroy_Elapsed();
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UFUNCTION()
	void OnTakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	
};
