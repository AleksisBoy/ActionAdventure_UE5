// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Data/ItemAsset.h"
#include "SaveInstance.generated.h"

UCLASS()
class GOINGACTION_API USaveInstance : public USaveGame
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
    int32 PlayerLevel;

    UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
    float Health;

    UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
    TArray<FItem> Inventory;
};
