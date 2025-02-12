// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemAsset.h"
#include "WeaponAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UWeaponAsset : public UItemAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon Stats")
	FVector2D DamageRange = FVector2D();


	virtual void UseItem_Implementation(AGoingActionCharacter* Character, UItem* ItemInstance) override;
};
