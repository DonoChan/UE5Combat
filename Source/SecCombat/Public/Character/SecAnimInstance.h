// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CharacterType.h"
#include "SecAnimInstance.generated.h"


class ASecCharacter;
class UCharacterMovementComponent;
UCLASS()
class SECCOMBAT_API USecAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ASecCharacter* SecCharacter;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	UCharacterMovementComponent* SecCharacterMovement;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	bool IsFalling;

	UPROPERTY(BlueprintReadOnly, Category = "Character")
	ECharacterState CharacterState;
	UPROPERTY(BlueprintReadOnly, Category = "Character")
	EActionState ActionState;

	
};
