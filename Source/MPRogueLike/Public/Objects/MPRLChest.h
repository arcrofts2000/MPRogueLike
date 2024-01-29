// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game/MPRLGameplayInterface.h"
#include "MPRLChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class MPROGUELIKE_API AMPRLChest : public AActor, public IMPRLGameplayInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Interaction")
	float TargetPitch;

	void Interact_Implementation(APawn* InstigatorPawn);
	
protected:

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> LidMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties
	AMPRLChest();
};
