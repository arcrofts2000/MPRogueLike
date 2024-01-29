// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPRLBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;
class UParticleSystem;

UCLASS()
class MPROGUELIKE_API AMPRLBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPRLBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<URadialForceComponent> RadialForce;

	UPROPERTY(EditAnywhere, Category = "Cosmetic")
	TObjectPtr<UParticleSystem> ParticleSystem;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse, 
		const FHitResult& Hit);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

};
