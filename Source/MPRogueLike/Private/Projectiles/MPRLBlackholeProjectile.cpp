// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MPRLBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"

AMPRLBlackholeProjectile::AMPRLBlackholeProjectile()
{
	DestroyDelay = 5.f;

	SphereComp->SetSphereRadius(55.f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMPRLBlackholeProjectile::OnComponentBeginOverlap);

	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->SetupAttachment(SphereComp);
	RadialForceComp->Radius = 1000.f;
	RadialForceComp->ForceStrength = -200000.f;
}

void AMPRLBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DestroySelf, this, &AMPRLBlackholeProjectile::DestroySelf, DestroyDelay);
}

void AMPRLBlackholeProjectile::DestroySelf()
{
	Destroy();
}

void AMPRLBlackholeProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics())
	{
		OtherComp->GetOwner()->Destroy();
	}
}