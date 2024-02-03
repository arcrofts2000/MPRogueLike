// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MPRLAICharacter.h"

// Sets default values
AMPRLAICharacter::AMPRLAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMPRLAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPRLAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
