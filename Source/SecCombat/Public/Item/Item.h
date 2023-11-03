#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UENUM(BlueprintType)
enum class EItemState : uint8
{
	EIS_Hovering UMETA(DisplayName = "Hovering"),
	EIS_Equipped UMETA(DisplayName = Equipped)
};

UCLASS()
class SECCOMBAT_API AItem : public AActor
{
	GENERATED_BODY()

public:
	AItem();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;
	UFUNCTION()
		virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	EItemState ItemState = EItemState::EIS_Hovering;
private:

UPROPERTY(VisibleAnywhere)
UStaticMeshComponent* ItemMesh;


	UPROPERTY(EditAnywhere, Category = "Sin")
	float GameTime;
	UPROPERTY(EditAnywhere, Category = "Sin")
	float Amplitude = 0.2;
	UPROPERTY(EditAnywhere, Category = "Sin")
	float TimeConstance = 0.5;


	

};