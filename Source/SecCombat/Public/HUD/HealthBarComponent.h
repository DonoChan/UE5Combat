// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarComponent.generated.h"

/**
 * 
 */
UCLASS()
class SECCOMBAT_API UHealthBarComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetHealthPercent(float Percent);
};
