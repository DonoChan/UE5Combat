// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/HitInterface.h"
#include "Character/CharacterType.h"
#include "Enemy.generated.h"

class UAnimMontage;
class UAttributesComponent;
class UHealthBarComponent;
class AAIController;
class UHealthBarUserWidget;
class UPawnSensingComponent;

UCLASS()
class SECCOMBAT_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	AEnemy();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;
	UFUNCTION()
	bool InTargetRange(AActor* Target, double Radius);

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint);
	void DirectionalHitReaction(const FVector& ImpactPoint);
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarComponent;
	UPROPERTY(VisibleAnywhere)
	UAttributesComponent* AttributesComponent;

	UPROPERTY()
	UHealthBarUserWidget* HealthBarWidget;

private:
	//Montage/////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* HitReactMontage;
	UFUNCTION()
	void PlayHitReactMontage(FName SectionName);
	UFUNCTION()
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	UPROPERTY(EditAnywhere, Category = "Montage")
	UAnimMontage* DeathMontage;
	UFUNCTION()
	void PlayDeathMontage();

	UPROPERTY()
	AActor* CombatTarget;
	UPROPERTY(EditAnywhere, Category = "Combat")
	double CombatRadius = 500.f;

	UPROPERTY()
	AAIController* EnemyController;
	UPROPERTY(EditAnywhere, Category = "Target")
	AActor* PatrolTarget;
	UPROPERTY(EditAnywhere, Category = "Target")
	TArray<AActor*> PatrolTargets;
	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* SensingComponent;
	UFUNCTION()
	void OnSeePawn(APawn* SeePawn);
	UPROPERTY(EditAnywhere, Category = "AI")
	float PatrolRadius = 200.f;



};
