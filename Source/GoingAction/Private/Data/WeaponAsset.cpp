// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/WeaponAsset.h"
#include "GoingAction/GoingActionCharacter.h"

void UWeaponAsset::UseItem_Implementation(AGoingActionCharacter* Character, UItem* ItemInstance)
{
    // Equip the weapon
    UE_LOG(LogTemp, Warning, TEXT("Weapon Equipped: %s"), *ItemName.ToString());
    Character->EquipWeapon(this, ItemInstance);
}