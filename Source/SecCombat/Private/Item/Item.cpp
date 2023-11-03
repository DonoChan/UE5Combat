// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Item.h"
#include "Character/SecCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
// Sets default values
AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(RootComponent);


}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
	
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FString OtherActorName = OtherActor->GetName();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 4.f, FColor::Blue, OtherActorName);
	}
	ASecCharacter* SecCharacter = Cast<ASecCharacter>(OtherActor);
	if (SecCharacter)
	{
		SecCharacter->SetOverlappingItem(this);
	}

}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const FString OtherActorName = OtherActor->GetName();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 4.f, FColor::Blue, OtherActorName);
	}
	ASecCharacter* SecCharacter = Cast<ASecCharacter>(OtherActor);
	if (SecCharacter)
	{
		SecCharacter->SetOverlappingItem(nullptr);
	}
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ItemState == EItemState::EIS_Hovering)
	{
		GameTime += DeltaTime;

		float DeltaZ = Amplitude * FMath::Sin(GameTime * TimeConstance);
		FVector SinVector = FVector(0.f, 0.f, DeltaZ);

		AddActorWorldOffset(SinVector);
	}
	
}


