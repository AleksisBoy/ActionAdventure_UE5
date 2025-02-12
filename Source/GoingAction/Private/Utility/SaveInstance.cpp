// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SaveInstance.h"

void USaveInstance::AssignInventory(TArray<UItem*> ItemInstances)
{
	for (UItem* ItemInstance : ItemInstances)
	{
		FItemSaved Item = FItemSaved();
		Item.Asset = ItemInstance->Asset;
		Item.Stack = ItemInstance->Stack;

		Inventory.Add(Item);
	}
}

TArray<UItem*> USaveInstance::LoadInventory()
{
	TArray<UItem*> ItemInstances;
	for (FItemSaved Item : Inventory)
	{
		UItem* ItemInstance = NewObject<UItem>();
		ItemInstance->Asset = Item.Asset;
		ItemInstance->Stack = Item.Stack;

		ItemInstances.Add(ItemInstance);
	}
	return ItemInstances;
}
