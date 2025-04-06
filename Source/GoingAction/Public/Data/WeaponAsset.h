// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemAsset.h"
#include "Utility/Prerequisites.h"
#include "WeaponAsset.generated.h"

class AWeapon;

UENUM(BlueprintType)
enum class FWeaponType : uint8
{
	Steel,
	Silver,
	Any
};

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UWeaponAsset : public UItemAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	UStaticMesh* StaticMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FWeaponType WeaponType = FWeaponType::Steel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FVector2D DamageRange = FVector2D();

	// Offset for weapon mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	FVector MeshOffset;

	// Offset for weapon while in hand
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	FVector HandOffset;

	// Offset for weapon while in scabbard
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	FVector ScabbardOffset;
	
	// Offset for weapon box component 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	FVector BoxCompOffset;
	
	// Extent of weapon box component 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	FVector BoxCompExtent;
	
	// Rotation for holding weapon in hand
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	FRotator HandRotation;

	// Rotation for weapon in scabbard position
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	FRotator ScabbardRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Visual")
	TArray<FAttackMontageData> AttackAnimations;

	virtual void UseItem_Implementation(AGoingActionCharacter* Character, UItem* ItemInstance) override;
};
