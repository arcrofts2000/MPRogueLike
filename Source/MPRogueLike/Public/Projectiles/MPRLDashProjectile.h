// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles/MPRLProjectile.h"
#include "MPRLDashProjectile.generated.h"

UCLASS()
class MPROGUELIKE_API AMPRLDashProjectile : public AMPRLProjectile
{
	GENERATED_BODY()
public:


protected:
	
	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//virtual void Explode() override;

	FTimerHandle TimerHandle_Explode;
	void Explode_TimeElapsed();

	FTimerHandle TimerHandle_Teleport;
	void Teleport_TimeElapsed();

};
