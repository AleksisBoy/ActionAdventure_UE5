// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/ArmorAsset.h"
#include "GoingAction/GoingActionCharacter.h"

void UArmorAsset::UseItem_Implementation(AGoingActionCharacter* Character, FItem& ItemInstance)
{
    // Equip Armor
    UE_LOG(LogTemp, Warning, TEXT("Equip: %s"), *ItemName.ToString());
    Character->EquipArmor(this, ItemInstance, ArmorSocket);
}
