// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RudeCharacter.generated.h"

UCLASS()
class LEARN4_API ARudeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ARudeCharacter();

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void AimButtonPressed();
	void AimButtonReleased();
	void FireButtonPressed();
	void FireButtonReleased();
	
public:
	UPROPERTY(EditAnywhere)
	class USpringArmComponent* CameraSpringArm;
	UPROPERTY(EditAnywhere)
	class UCameraComponent* PlayerCamera;
	UPROPERTY(EditAnywhere)
	class URudeCharacterAnim* RudeCharacterAnim;
	UPROPERTY(EditAnywhere)
	class UCombatComponent* Combat;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
