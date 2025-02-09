// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemAsset.generated.h"

UENUM(Blueprintable, BlueprintType)
enum class EItemType : uint8
{
    Consumable UMETA(DisplayName = "Consumable"),
    Weapon UMETA(DisplayName = "Weapon"),
    Armor UMETA(DisplayName = "Armor"),
    Quest UMETA(DisplayName = "Quest"),
    Miscellaneous UMETA(DisplayName = "Miscellaneous")
};

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UItemAsset : public UDataAsset
{
	GENERATED_BODY()
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    EItemType Type;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    FName ItemName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    UTexture2D* Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    bool Unique;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    int MaxStack;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    float Weight;
};


USTRUCT(Blueprintable, BlueprintType)
struct FItem
{
    GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UItemAsset* Asset;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Stack = 0;


    bool operator==(const FItem& Other) const
    {
        return Asset == Other.Asset  && Stack == Other.Stack;  
    }
};
