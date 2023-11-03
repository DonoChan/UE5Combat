// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarUserWidget.generated.h"

class UProgressBar;

UCLASS()
class SECCOMBAT_API UHealthBarUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BlindWidget))
	UProgressBar* HealthBar;
};
