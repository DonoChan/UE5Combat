// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SecCharacter.h"
#include "Character/SecAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharacterType.generated.h"


void USecAnimInstance::NativeInitializeAnimation()
{
	SecCharacter = Cast<ASecCharacter>(TryGetPawnOwner());
	if (SecCharacter)
	{
		SecCharacterMovement = SecCharacter->GetCharacterMovement();
	}
}

void USecAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	if (SecCharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(SecCharacterMovement->Velocity);
		IsFalling = SecCharacterMovement->IsFalling();
		CharacterState = SecCharacter->GetCharacterState();
		ActionState = SecCharacter->GetActionState();
	}
}
