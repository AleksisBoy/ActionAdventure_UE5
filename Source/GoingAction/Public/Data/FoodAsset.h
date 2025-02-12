// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemAsset.h"
#include "FoodAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UFoodAsset : public UItemAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Food Stats")
	float HealingPerSec = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Food Stats")
	float HealDuration = 12.f;


	virtual void UseItem_Implementation(AGoingActionCharacter* Character, FItem& ItemInstance) override;
};
