// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/MPRLBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Particles/ParticleSystem.h"

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
	Destroy();
}

// Called every frame
void AMPRLBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

