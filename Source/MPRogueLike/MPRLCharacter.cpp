// Fill out your copyright notice in the Description page of Project Settings.


#include "MPRLCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
AMPRLCharacter::AMPRLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(GetRootComponent());

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void AMPRLCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPRLCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMPRLCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();

	// Add the mappings for the game!
	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	// New Enhanced Input System
	UEnhancedInputComponent* InputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	// General
	InputComp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AMPRLCharacter::Move);
	InputComp->BindAction(Input_LookMouse, ETriggerEvent::Triggered, this, &AMPRLCharacter::LookMouse);

	// Sprint while holding key


	// MKB

	// Gamepad


	// Abilities

}

void AMPRLCharacter::Move(const FInputActionValue& InputValue)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.f;
	ControlRot.Roll = 0.f;

	const FVector2D AxisValue = InputValue.Get<FVector2D>();

	// Move Forward or Backward
	AddMovementInput(ControlRot.Vector(), AxisValue.Y);

	// Move Left or Right
	const FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, AxisValue.X);
}

void AMPRLCharacter::LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}