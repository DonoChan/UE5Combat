// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Treasure.h"
#include "Character/SecCharacter.h"

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASecCharacter* SecCharacter = Cast<ASecCharacter>(OtherActor);
	if (SecCharacter)
	{
		Destroy();
	}
}
