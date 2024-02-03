// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MPRLAIController.generated.h"

class UBehaviorTree;

/**
 * 
 */
UCLASS()
class MPROGUELIKE_API AMPRLAIController : public AAIController
{
	GENERATED_BODY()
	

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviourTree;

	virtual void BeginPlay() override;
};
