// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LocationData.generated.h"

class AWorldLocation;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API ULocationData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Location Data")
	FText Name;

	UFUNCTION(BlueprintCallable, Category = "Location Data")
	AWorldLocation* GetWorldLocation();
};
