// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MPRLBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Components/SphereComponent.h"

AMPRLBlackholeProjectile::AMPRLBlackholeProjectile()
{
	RadialForceComp = CreateDefaultSubobject<URadialForceComponent>("RadialForceComp");
	RadialForceComp->ForceStrength = -1000.f;

	BlackholeComp = CreateDefaultSubobject<USphereComponent>("BlackholeComp");
}

void AMPRLBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BlackholeComp->OnComponentBeginOverlap.AddDynamic(this, &AMPRLBlackholeProjectile::OnComponentBeginOverlap);
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