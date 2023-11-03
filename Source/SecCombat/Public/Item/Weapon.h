// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Item.h"
#include "Weapon.generated.h"

class UBoxComponent;
class USceneComponent;

UCLASS()
class SECCOMBAT_API AWeapon : public AItem
{
	GENERATED_BODY()
public:
	
	AWeapon();
	void AttachToHand(USceneComponent* Parent, const FName& SocketName, AActor* NewOwner, APawn* NewInstigator);

	void AttachToMesh(USceneComponent* Parent, const FName& SocketName);
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	UFUNCTION()
	void OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	virtual void BeginPlay() override;



private:
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* TraceStart;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* TraceEnd;
	UPROPERTY(EditAnywhere, Category = "Combat")
	float WeaponDamage = 20.f;

	



public:

	FORCEINLINE UBoxComponent* GetBoxComponent() const {return BoxComponent;}
	TArray<AActor*> IgnoreActor;
	UFUNCTION(BlueprintImplementableEvent)
	void CreateField(FVector ImpactPoint);

};
