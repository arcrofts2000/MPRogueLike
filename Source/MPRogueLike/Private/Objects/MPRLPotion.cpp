// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/MPRLPotion.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AMPRLPotion::AMPRLPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	SetRootComponent(MeshComp);
}

void AMPRLPotion::BeginPlay()
{
	Super::BeginPlay();
}

void AMPRLPotion::Interact_Implementation(APawn* InstigatorPawn)
{

}