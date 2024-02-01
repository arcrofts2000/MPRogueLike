// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Game/MPRLGameplayInterface.h"
#include "MPRLPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class MPROGUELIKE_API AMPRLPotion : public AActor, public IMPRLGameplayInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPRLPotion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComp;

	void Interact_Implementation(APawn* InstigatorPawn);

};
