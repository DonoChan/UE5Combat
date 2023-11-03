
// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributesComponent.h"

// Sets default values for this component's properties
UAttributesComponent::UAttributesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAttributesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

float UAttributesComponent::GetHealthPercent()
{
	return Health / MaxHealth;
}

bool UAttributesComponent::IsAlive()
{
	return Health > 0;
}

void UAttributesComponent::ReceivedDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0, MaxHealth);
}


// Called every frame
void UAttributesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

