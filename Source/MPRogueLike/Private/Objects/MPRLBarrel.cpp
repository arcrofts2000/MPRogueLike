// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/MPRLBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"
#include "Components/MPRLAttributeComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMPRLBarrel::AMPRLBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetSimulatePhysics(true);
	SetRootComponent(StaticMesh);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(StaticMesh);
	RadialForce->SetAutoActivate(false);

	RadialForce->Radius = 750.f;
	RadialForce->ImpulseStrength = 2000.f;
	RadialForce->bImpulseVelChange = true;

	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);

	ParticleSystem = CreateDefaultSubobject<UParticleSystem>("ParticleSystem");
}

void AMPRLBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	StaticMesh->OnComponentHit.AddDynamic(this, &AMPRLBarrel::OnActorHit);
}

// Called when the game starts or when spawned
void AMPRLBarrel::BeginPlay()
{
	Super::BeginPlay();
	

}

void AMPRLBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, GetActorLocation());

	if (UMPRLAttributeComponent* AttributeComp = Cast<UMPRLAttributeComponent>(OtherActor->GetComponentByClass(UMPRLAttributeComponent::StaticClass())))
	{
		AttributeComp->ApplyHealthChange(-30.f);
	}

	Destroy();

	UE_LOG(LogTemp, Log, TEXT("OnActorHit in MPRLBarrel"));

	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.f, true);
}

// Called every frame
void AMPRLBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

