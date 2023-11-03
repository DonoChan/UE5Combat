// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Enemy.h"
#include "HUD/HealthBarComponent.h"
#include "Components/AttributesComponent.h"
#include "HUD/HealthBarUserWidget.h"
#include "Animation/AnimMontage.h"
#include "AIController.h"
#include "Perception/PawnSensingComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	AttributesComponent = CreateDefaultSubobject<UAttributesComponent>(TEXT("AttributesComponent"));

	HealthBarComponent = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBarComponent"));
	HealthBarComponent->SetupAttachment(GetRootComponent());

	SensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("SensingComponent"));
	SensingComponent->SightRadius = 2500.f;
	SensingComponent->SetPeripheralVisionAngle(55.f);
	


}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(false);
	}
	EnemyController = Cast<AAIController>(GetController());



}

bool AEnemy::InTargetRange(AActor* Target, double Radius)
{
	const double DistanceToTarget = (Target->GetActorLocation() - GetActorLocation()).Size();

	return DistanceToTarget <= Radius;
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CombatTarget)
	{
		if (!InTargetRange(CombatTarget, CombatRadius))
		{
			CombatTarget = nullptr;
			if (HealthBarComponent)
			{
				HealthBarComponent->SetVisibility(false);
			}
		}
	}
	if (PatrolTarget && EnemyController)
	{
		if (InTargetRange(PatrolTarget, PatrolRadius))
		{
			TArray<AActor*> ValidTargets;
			for (AActor* Target : PatrolTargets)
			{
				if (Target != PatrolTarget)
				{
					ValidTargets.AddUnique(Target);
				}
			}
			const int32 NumPatrolTargets = ValidTargets.Num();
			if (NumPatrolTargets > 0)
			{
				const int32 TargetSelection = FMath::RandRange(0, NumPatrolTargets - 1);
				AActor* Target = ValidTargets[TargetSelection];
				PatrolTarget = Target;

				FAIMoveRequest MoveRequest;
				MoveRequest.SetGoalActor(PatrolTarget);
				MoveRequest.SetAcceptanceRadius(15.f);
				FNavPathSharedPtr NavPath;
				EnemyController->MoveTo(MoveRequest);

			}
		}
	}

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(true);
	}
	if (AttributesComponent && AttributesComponent->IsAlive())
	{
		DirectionalHitReaction(ImpactPoint);
	}
		else
		{
		  PlayDeathMontage();
		}

}

void AEnemy::DirectionalHitReaction(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector LowerImpactPoint = FVector(ImpactPoint.X, ImpactPoint.Y, GetActorLocation().Z);
	const FVector ToHit = (LowerImpactPoint - GetActorLocation()).GetSafeNormal();
	const double CosTheTa = FVector::DotProduct(Forward, ToHit);
	double Theta = FMath::Acos(CosTheTa);
	Theta = FMath::RadiansToDegrees(Theta);

	FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}
	if (HitReactMontage)
	{

		FName Section = FName("Section");

		if (Theta >= -45.f && Theta < 45.f)
		{
			Section = FName("FromFront");
		}
		if (Theta >= -135.f && Theta < -45.f)
		{
			Section = FName("FromLeft");
		}
		if (Theta < 135.f && Theta >= 45.f)
		{
			Section = FName("FromRight");
		}
		PlayHitReactMontage(Section);
	}
}

void AEnemy::PlayHitReactMontage(FName SectionName)
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (Instance)
	{
		Instance->Montage_Play(HitReactMontage);
		Instance->Montage_JumpToSection(SectionName, HitReactMontage);
	}

}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (AttributesComponent)
	{
		AttributesComponent->ReceivedDamage(DamageAmount);
		if (HealthBarComponent)
		{
			HealthBarComponent->SetHealthPercent(AttributesComponent->GetHealthPercent());
		}

	}

	CombatTarget = EventInstigator->GetPawn();

	return DamageAmount;
}

void AEnemy::PlayDeathMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(DeathMontage);
		int32 Selection = FMath::RandRange(0, 2);
		FName Section = FName();
		switch (Selection)
		{
		case 0:
			Section = FName("Death1");
			DeathPose = EDeathPose::EDP_DeathPose1;
			break;
		case 1:
			Section = FName("Death2");
			DeathPose = EDeathPose::EDP_DeathPose2;
			break;
		case 2:
			Section = FName("Death3");
			DeathPose = EDeathPose::EDP_DeathPose3;
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(Section, DeathMontage);
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetLifeSpan(6.f);
	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(false);
	}
}

void AEnemy::OnSeePawn(APawn* SeePawn)
{
}

