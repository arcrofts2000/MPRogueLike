// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MPRLProjectileBase.h"
#include "MPRLBlackholeProjectile.generated.h"

class URadialForceComponent;
class USphereComponent;

UCLASS()
class MPROGUELIKE_API AMPRLBlackholeProjectile : public AMPRLProjectileBase
{
	GENERATED_BODY()

public:
	AMPRLBlackholeProjectile();

	

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Blackhole")
	float DestroyDelay;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComp;

	FTimerHandle TimerHandle_DestroySelf;

	void DestroySelf();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
	
};