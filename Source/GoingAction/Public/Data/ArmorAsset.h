// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemAsset.h"
#include "ArmorAsset.generated.h"

UENUM(Blueprintable, BlueprintType)
enum class EArmorSocket : uint8
{
    Head UMETA(DisplayName = "Head"),
    Gloves UMETA(DisplayName = "Gloves"),
    Chest UMETA(DisplayName = "Chest"),
    Legs UMETA(DisplayName = "Legs"),
    Boots UMETA(DisplayName = "Boots")
};

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UArmorAsset : public UItemAsset
{
	GENERATED_BODY()
public:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Armor Stats")
    EArmorSocket ArmorSocket;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Armor Stats")
    float ArmorStrength = 1.f;


    virtual void UseItem_Implementation(AGoingActionCharacter* Character, FItem& ItemInstance) override;
};
