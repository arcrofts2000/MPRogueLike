// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MPRLCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/MPRLInteractionComponent.h"
#include "Components/MPRLAttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMPRLCharacter::AMPRLCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComp->SetupAttachment(GetRootComponent());
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<UMPRLInteractionComponent>("InteractionComp");
	AttributeComp = CreateDefaultSubobject<UMPRLAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

void AMPRLCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &AMPRLCharacter::OnHealthChanged);
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
	InputComp->BindAction(Input_Jump, ETriggerEvent::Started, this, &ACharacter::Jump);
	InputComp->BindAction(Input_PrimaryInteract, ETriggerEvent::Started, this, &AMPRLCharacter::PrimaryInteract);

	// Sprint while holding key


	// MKB

	// Gamepad


	// Abilities
	InputComp->BindAction(Input_PrimaryAttack, ETriggerEvent::Completed, this, &AMPRLCharacter::PrimaryAttack);
	InputComp->BindAction(Input_BlackholeAttack, ETriggerEvent::Completed, this, &AMPRLCharacter::BlackholeAttack);
	InputComp->BindAction(Input_DashAttack, ETriggerEvent::Completed, this, &AMPRLCharacter::DashAttack);

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

void AMPRLCharacter::PrimaryAttack()
{
	PlayAnimMontage(PrimaryAttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMPRLCharacter::PrimaryAttack_TimeElapsed, 0.2f);

}

void AMPRLCharacter::DashAttack()
{
	PlayAnimMontage(PrimaryAttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMPRLCharacter::DashAttack_TimeElapsed, .2f);
}

void AMPRLCharacter::BlackholeAttack()
{
	PlayAnimMontage(PrimaryAttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &AMPRLCharacter::BlackholeAttack_TimeElapsed, .2f);
}

void AMPRLCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(MagicProjectileClass);
}

void AMPRLCharacter::DashAttack_TimeElapsed()
{
	SpawnProjectile(DashProjectileClass);
}

void AMPRLCharacter::BlackholeAttack_TimeElapsed()
{
	SpawnProjectile(BlackholeProjectileClass);
}

void AMPRLCharacter::SpawnProjectile(TSubclassOf<AActor> SpawnedProjectile)
{
	if (ensureAlways(SpawnedProjectile))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjectParams;
		ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector StartTrace = CameraComp->GetComponentLocation();

		FVector EndTrace = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000.f);
		FHitResult Hit;

		FRotator ProjectileRotation;
		if (GetWorld()->SweepSingleByObjectType(Hit, StartTrace, EndTrace, FQuat::Identity, ObjectParams, Shape, Params))
		{
			ProjectileRotation = FRotationMatrix::MakeFromX(Hit.ImpactPoint - HandLocation).Rotator();
		}
		else
		{
			ProjectileRotation = FRotationMatrix::MakeFromX(EndTrace - HandLocation).Rotator();
		}


		FTransform SpawnTM = FTransform(ProjectileRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(SpawnedProjectile, SpawnTM, SpawnParams);
	}
}

void AMPRLCharacter::PrimaryInteract()
{
	if (InteractionComp)
		InteractionComp->PrimaryInteract();
}

void AMPRLCharacter::OnHealthChanged(AActor* InstigatorActor, UMPRLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (NewHealth <= 0.f && Delta < 0.f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}