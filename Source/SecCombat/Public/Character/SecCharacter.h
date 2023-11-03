// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterType.h"
#include "SecCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AWeapon;
class AItem;

UCLASS()
class SECCOMBAT_API ASecCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASecCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;	
	UFUNCTION(BlueprintCallable)
	void EquipEnd();
	UFUNCTION(BlueprintCallable)
	void AttachToBack();
	UFUNCTION(BlueprintCallable)
	void AttachToHand();
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	UFUNCTION(BlueprintCallable)
	void SetWeaponCollision(ECollisionEnabled::Type CollisionEnable);



private:

	void MoveForWard(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void Equip();
	virtual void Jump() override;
	void Attack();
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere)
	AItem* OverlappingItem;
	UPROPERTY(VisibleAnywhere)
	ECharacterState CharacterState = ECharacterState::EST_Unequipped;
	UPROPERTY(VisibleAnywhere)
	EActionState ActionState = EActionState::EAS_Unoccupied;
	AWeapon* EquippedWeapon;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* EquipMontage;
	UFUNCTION()
	void PlayMontage(FName SectionName, UAnimMontage* Montage);
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* AttackMontage;
	UFUNCTION()
	void PlayAttackMontage();

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
