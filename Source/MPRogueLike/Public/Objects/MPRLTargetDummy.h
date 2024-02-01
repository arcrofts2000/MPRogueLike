// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPRLTargetDummy.generated.h"

class USkeletalMeshComponent;
class UMPRLAttributeComponent;

UCLASS()
class MPROGUELIKE_API AMPRLTargetDummy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPRLTargetDummy();

protected:
	
	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UMPRLAttributeComponent> AttributeComp;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UMPRLAttributeComponent* OwningComp, float NewHealth, float Delta);

};
