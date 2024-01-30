// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/MPRLTargetDummy.h"
#include "Components/MPRLAttributeComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMPRLTargetDummy::AMPRLTargetDummy()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	SetRootComponent(SkeletalMesh);

	AttributeComp = CreateDefaultSubobject<UMPRLAttributeComponent>("AttributeComp");
	AttributeComp->OnHealthChanged.AddDynamic(this, &AMPRLTargetDummy::OnHealthChanged);
}

void AMPRLTargetDummy::OnHealthChanged(AActor* InstigatorActor, UMPRLAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
		SkeletalMesh->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->DeltaTimeSeconds);
}