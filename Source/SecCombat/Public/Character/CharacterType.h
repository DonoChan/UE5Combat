#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	EST_Unequipped UMETA(DisplayName = "Unequipped"),
	EST_EquippedOneHandWeapon UMETA(DisplayName = "EquippedOneHandWeapon"),
	EST_EquippedTwoHandWeapon UMETA(DisplayName = "EquippedTwoHandWeapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Equipping UMETA(DisplayName = "Equipping"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
};

UENUM(BlueprintType)
enum class EDeathPose : uint8
{
	EDP_Alive UMETA(DisplayName = "Alive"),
	EDP_DeathPose1 UMETA(DisplayName = "DeathPose1"),
	EDP_DeathPose2 UMETA(DisplayName = "DeathPose2"),
	EDP_DeathPose3 UMETA(DisplayName = "DeathPose3"),

};