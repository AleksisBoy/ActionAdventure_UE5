// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemAsset.h"
#include "BookAsset.generated.h"

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UBookAsset : public UItemAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Book")
	FText Title;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Book")
	FText Body;

	virtual void UseItem_Implementation(AGoingActionCharacter* Character, FItem& ItemInstance) override;
};
