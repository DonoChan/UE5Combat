// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Item/Weapon.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimMontage.h"
#include "Character/SecCharacter.h"

ASecCharacter::ASecCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	

}
void ASecCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

void ASecCharacter::EquipEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASecCharacter::AttachToBack()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToMesh(GetMesh(), FName("SpineSocket"));
	}
}

void ASecCharacter::AttachToHand()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachToMesh(GetMesh(), FName("WeaponSocket"));
	}
}

void ASecCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;

}

void ASecCharacter::SetWeaponCollision(ECollisionEnabled::Type CollisionEnable)
{
	if (EquippedWeapon)
	{
		EquippedWeapon->GetBoxComponent()->SetCollisionEnabled(CollisionEnable);
		EquippedWeapon->IgnoreActor.Empty();

	}
}

void ASecCharacter::MoveForWard(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller && Value != 0)
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void ASecCharacter::MoveRight(float Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller && Value != 0)
	{
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, Value);
	}
}

void ASecCharacter::Turn(float Value)
{

	if (Controller && Value != 0)
	{
		AddControllerYawInput(Value);

	}
}

void ASecCharacter::LookUp(float Value)
{
	if (Controller && Value != 0)
	{
		AddControllerPitchInput(Value);

	}
}

void ASecCharacter::Equip()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	
	if (OverlappingWeapon)
	{
		OverlappingWeapon->AttachToHand(GetMesh(), FName("WeaponSocket"), this, this);

		CharacterState = ECharacterState::EST_EquippedOneHandWeapon;
		EquippedWeapon = OverlappingWeapon;
	}
	
	else
	{
			if (CharacterState != ECharacterState::EST_Unequipped && ActionState == EActionState::EAS_Unoccupied)
			{
				PlayMontage(FName("Disarm"), EquipMontage);
				CharacterState = ECharacterState::EST_Unequipped;
				ActionState = EActionState::EAS_Equipping;
				
			}
			else if (CharacterState == ECharacterState::EST_Unequipped && ActionState == EActionState::EAS_Unoccupied && EquippedWeapon)
			{
				PlayMontage(FName("Arm"), EquipMontage);
				CharacterState = ECharacterState::EST_EquippedOneHandWeapon;
				ActionState = EActionState::EAS_Equipping;
				
			}
	}

	
}

void ASecCharacter::Jump()
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	Super::Jump();
}

void ASecCharacter::Attack()
{
	if (CharacterState != ECharacterState::EST_Unequipped && ActionState == EActionState::EAS_Unoccupied)
	{
		ActionState = EActionState::EAS_Attacking;
	    PlayAttackMontage();
	}
	
}

void ASecCharacter::PlayMontage(FName SectionName, UAnimMontage* Montage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance)
	{
		AnimInstance->Montage_Play(Montage);
		AnimInstance->Montage_JumpToSection(SectionName, Montage);
	}
}

void ASecCharacter::PlayAttackMontage()
{
	const int32 Selection = FMath::RandRange(0, 1);
	FName SectionName = FName();
	switch (Selection)
	{
	case 0:
		SectionName = FName("Attack1");
		break;
	case 1:
		SectionName = FName("Attack2");
		break;
	default:
		break;
	}
	PlayMontage(SectionName, AttackMontage);
}


void ASecCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ASecCharacter::MoveForWard);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ASecCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ASecCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ASecCharacter::LookUp);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ASecCharacter::Jump);
	PlayerInputComponent->BindAction(FName("Equip"), IE_Pressed, this, &ASecCharacter::Equip);
	PlayerInputComponent->BindAction(FName("Attack"), IE_Pressed, this, &ASecCharacter::Attack);
}

