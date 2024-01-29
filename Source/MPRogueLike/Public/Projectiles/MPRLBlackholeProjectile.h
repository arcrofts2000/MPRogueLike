// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MPRLProjectile.h"
#include "MPRLBlackholeProjectile.generated.h"

class URadialForceComponent;
class USphereComponent;

UCLASS()
class MPROGUELIKE_API AMPRLBlackholeProjectile : public AMPRLProjectile
{
	GENERATED_BODY()

public:
	AMPRLBlackholeProjectile();

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USphereComponent> BlackholeComp;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<URadialForceComponent> RadialForceComp;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};