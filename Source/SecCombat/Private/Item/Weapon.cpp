// Fill out your copyright notice in the Description page of Project Settings.

#include "Item/Weapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SceneComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/HitInterface.h"
#include "Components/SphereComponent.h"




AWeapon::AWeapon()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	TraceStart = CreateDefaultSubobject<USceneComponent>(TEXT("Start"));
	TraceStart->SetupAttachment(GetRootComponent());

	TraceEnd = CreateDefaultSubobject<USceneComponent>(TEXT("End"));
	TraceEnd->SetupAttachment(GetRootComponent());
}
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxOverlap);
	
}




void AWeapon::AttachToHand(USceneComponent* Parent, const FName& SocketName, AActor* NewOwner, APawn* NewInstigator)
{
	AttachToMesh(Parent, SocketName);
	ItemState = EItemState::EIS_Equipped;
	if (Sphere)
	{
		Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}
	if (BoxComponent)
	{
		BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	SetOwner(NewOwner);
	SetInstigator(NewInstigator);

}

void AWeapon::AttachToMesh(USceneComponent* Parent, const FName& SocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(Parent, TransformRules, SocketName);
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::OnBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	const FVector Start = TraceStart->GetComponentLocation();
	const FVector End = TraceEnd->GetComponentLocation();
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	for (AActor* Actor: IgnoreActor)
	{
		ActorsToIgnore.AddUnique(Actor);
	}
	FHitResult BoxHit;

	UKismetSystemLibrary::BoxTraceSingle(this,
		Start,
		End,
		FVector(2.5, 2.5, 2.5),
		TraceStart->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		BoxHit,
		true);

	UGameplayStatics::ApplyDamage(
		BoxHit.GetActor(),
		WeaponDamage,
		GetInstigator()->GetController(),
		GetOwner(),
		UDamageType::StaticClass());

	UWorld* World = GetWorld();
		if (World)
		{
			DrawDebugSphere(World, BoxHit.ImpactPoint, 12.f, 12, FColor::Green, false, 5.f);
		}
		IHitInterface* Interface = Cast<IHitInterface>(BoxHit.GetActor());
		if (Interface)
		{
			Interface->Execute_GetHit(BoxHit.GetActor(), BoxHit.ImpactPoint);
		}

		IgnoreActor.AddUnique(BoxHit.GetActor());
		CreateField(BoxHit.ImpactPoint);

}

