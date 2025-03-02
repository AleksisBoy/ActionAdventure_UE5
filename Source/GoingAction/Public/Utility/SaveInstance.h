// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Data/ItemAsset.h"
#include "Utility/Fact.h"
#include "SaveInstance.generated.h"


USTRUCT(Blueprintable, BlueprintType)
struct FItemSaved
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UItemAsset* Asset = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Stack = 0;


    bool operator==(const FItemSaved& Other) const
    {
        return Asset == Other.Asset && Stack == Other.Stack;
    }
}; 

UCLASS()
class GOINGACTION_API USaveInstance : public USaveGame
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
    int32 PlayerLevel;

    UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
    float Health;

    // Inventory
    UPROPERTY(BlueprintReadWrite, Category = "SaveGame")
    TArray<FItemSaved> Inventory;

    void AssignInventory(TArray<UItem*> ItemInstances);
    TArray<UItem*> LoadInventory();

    // Dialogue
    // ...
    
    // Facts
    UPROPERTY()
    TMap<uint8, bool> Facts;
};
