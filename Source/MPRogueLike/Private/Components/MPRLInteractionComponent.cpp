// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MPRLInteractionComponent.h"
#include "Game/MPRLGameplayInterface.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UMPRLInteractionComponent::UMPRLInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMPRLInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMPRLInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMPRLInteractionComponent::PrimaryInteract()
{
	TArray<FHitResult> Hits;

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	AActor* MyOwner = GetOwner();
	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	FVector EndLocation = EyeLocation + (EyeRotation.Vector() * 1000.f);

	FCollisionShape Shape;
	float Radius = 30.f;
	Shape.SetSphere(Radius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, EndLocation, FQuat::Identity, ObjectQueryParams, Shape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (FHitResult Hit : Hits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (HitActor->Implements<UMPRLGameplayInterface>())
			{
				APawn* MyPawn = Cast<APawn>(MyOwner);
				IMPRLGameplayInterface::Execute_Interact(HitActor, MyPawn);
			}
		}
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.f);
	}

	

	
}