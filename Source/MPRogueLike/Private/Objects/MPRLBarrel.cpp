// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/MPRLBarrel.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/StaticMeshComponent.h"

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
	RadialForce->bAutoActivate = false;

	RadialForce->Radius = 750.f;
	RadialForce->ImpulseStrength = 2000.f;
	RadialForce->bImpulseVelChange = true;

	RadialForce->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void AMPRLBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	StaticMesh->OnComponentHit.AddDynamic(this, &AMPRLBarrel::OnActorHit);
}

void AMPRLBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	RadialForce->FireImpulse();
	Destroy();
}

// Called every frame
void AMPRLBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

