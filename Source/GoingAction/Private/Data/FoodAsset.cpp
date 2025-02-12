// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/FoodAsset.h"
#include "GoingAction/GoingActionCharacter.h"

void UFoodAsset::UseItem_Implementation(AGoingActionCharacter* Character, UItem* ItemInstance)
{
    // Heal Player
    UE_LOG(LogTemp, Warning, TEXT("Eating: %s"), *ItemName.ToString());
    Character->EatFood(this, ItemInstance);
}
