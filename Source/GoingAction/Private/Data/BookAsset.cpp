// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/BookAsset.h"
#include "GoingAction/GoingActionCharacter.h"

void UBookAsset::UseItem_Implementation(AGoingActionCharacter* Character, UItem* ItemInstance)
{
    // Read Book
    UE_LOG(LogTemp, Warning, TEXT("Read: %s"), *ItemName.ToString());
}
