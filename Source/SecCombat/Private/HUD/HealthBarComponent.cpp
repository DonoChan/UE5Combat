// Fill out your copyright notice in the Description page of Project Settings.

#include "HUD/HealthBarUserWidget.h"
#include "HUD/HealthBarComponent.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	UHealthBarUserWidget* HealthBarUserWidget = Cast<UHealthBarUserWidget>(GetUserWidgetObject());
	if (HealthBarUserWidget)
	{
		HealthBarUserWidget->HealthBar->SetPercent(Percent);
	}
}
