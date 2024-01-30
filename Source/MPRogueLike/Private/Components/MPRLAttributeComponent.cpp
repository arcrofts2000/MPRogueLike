// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/MPRLAttributeComponent.h"

// Sets default values for this component's properties
UMPRLAttributeComponent::UMPRLAttributeComponent()
{
	Health = 100.f;
}

bool UMPRLAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}