// Fill out your copyright notice in the Description page of Project Settings.


#include "RudeCharacter.h"

#include "CombatComponent.h"
#include "RudeCharacterAnim.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ARudeCharacter::ARudeCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 350.f;


	ConstructorHelpers::FObjectFinder<USkeletalMesh> CharacterSkeletalMesh (TEXT("/Game/Mixamo/Swat/Ch35_nonPBR"));
	if (CharacterSkeletalMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(CharacterSkeletalMesh.Object);
		GetMesh()->AddLocalOffset(GetActorUpVector() * -90);
		GetMesh()->AddLocalRotation(FRotator(0, -90, 0));
	}

	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ConstructorHelpers::FObjectFinder<UAnimBlueprint> CharacterAnimBP (TEXT("/Game/Blueprints/RudeCharacterAnim/RudeCharacterAnim"));
	if (CharacterAnimBP.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(CharacterAnimBP.Object->GeneratedClass);
	}

	
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetMesh());
	CameraSpringArm->TargetArmLength = 350.f;
	CameraSpringArm->bUsePawnControlRotation = true;
	CameraSpringArm->AddLocalOffset(GetActorUpVector() * 90);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->bUsePawnControlRotation = false;
	PlayerCamera->SetupAttachment(CameraSpringArm);

	Combat = CreateDefaultSubobject<UCombatComponent>(TEXT("Combat"));
	
}



// Called when the game starts or when spawned
void ARudeCharacter::BeginPlay()
{
	Super::BeginPlay();

	RudeCharacterAnim = Cast<URudeCharacterAnim>(GetMesh()->GetAnimInstance());
	
}

// Called every frame
void ARudeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARudeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARudeCharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARudeCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARudeCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ARudeCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ARudeCharacter::LookUp);

	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &ARudeCharacter::AimButtonPressed);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &ARudeCharacter::AimButtonReleased);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ARudeCharacter::FireButtonPressed);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ARudeCharacter::FireButtonReleased);
}

void ARudeCharacter::MoveForward(float Value)
{
	if (RudeCharacterAnim)
		if (abs(RudeCharacterAnim->Direction) > 42 && abs(RudeCharacterAnim->Direction) < 92)	return;
	
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));
		AddMovementInput(Direction, Value);
	}
}

void ARudeCharacter::MoveRight(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));
		AddMovementInput(Direction, Value);
	}
}

void ARudeCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}

void ARudeCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

void ARudeCharacter::AimButtonPressed()
{
	Combat->SetAiming(true);
}

void ARudeCharacter::AimButtonReleased()
{
	Combat->SetAiming(false);
}

void ARudeCharacter::FireButtonPressed()
{
	
	Combat->SetFiring(true);
}

void ARudeCharacter::FireButtonReleased()
{
	Combat->SetFiring(false);
}
