// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ItemAsset.generated.h"

//UENUM(Blueprintable, BlueprintType)
//enum class EItemType : uint8
//{
//    Consumable UMETA(DisplayName = "Consumable"),
//    Weapon UMETA(DisplayName = "Weapon"),
//    Armor UMETA(DisplayName = "Armor"),
//    Quest UMETA(DisplayName = "Quest"),
//    Miscellaneous UMETA(DisplayName = "Miscellaneous")
//};

class AGoingActionCharacter;


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
        return Asset == Other.Asset && Stack == Other.Stack;
    }
};

UCLASS(Abstract, Blueprintable, BlueprintType)
class GOINGACTION_API UItemAsset : public UDataAsset
{
	GENERATED_BODY()
public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    FText ItemName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    UTexture2D* Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    bool Unique;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    int MaxStack = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Asset")
    float Weight = 0.05f;


    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void UseItem(AGoingActionCharacter* Character, UPARAM(ref)FItem& ItemInstance);

    virtual void UseItem_Implementation(AGoingActionCharacter* Character, FItem& ItemInstance) {};
};


