// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/MPRLProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/MPRLAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMPRLProjectile::AMPRLProjectile()
{
	SphereComp->SetSphereRadius(20.f);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMPRLProjectile::OnActorOverlap);

	DamageAmount = 20.f;
}

void AMPRLProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		if (UMPRLAttributeComponent* AttributeComp = Cast<UMPRLAttributeComponent>(OtherActor->GetComponentByClass(UMPRLAttributeComponent::StaticClass())))
		{
			AttributeComp->ApplyHealthChange(-20.f);
		}

		Explode();
	}
}

