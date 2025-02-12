// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include <Data/ArmorAsset.h>
#include <Data/WeaponAsset.h>

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

}
bool UInventoryComponent::TryAddItem(UItemAsset* NewItem, int Amount)
{
	if (NewItem->MaxStack < Amount) Amount = NewItem->MaxStack;

	// if unique should have only one such item
	for (FItem& Item : Items)
	{
		if (Item.Asset == NewItem &&
			Item.Stack + Amount <= Item.Asset->MaxStack)
		{
			Item.Stack += Amount;
			UpdateWeight();
			return true;
		}
	}
	if (HasFreeSlot())
	{
		AddItem(NewItem, Amount);
		return true;
	}

	return false;
}

void UInventoryComponent::AddItem(UItemAsset* NewItem, int Amount)
{
	FItem CreatedItem = FItem();
	CreatedItem.Asset = NewItem;
	CreatedItem.Stack = Amount;

	Items.Add(CreatedItem);
	UpdateWeight();
}
bool UInventoryComponent::TryRemoveItemAsset(const UItemAsset* Item, int Amount)
{
	int FoundItem;
	if (HasItem(Item, FoundItem))
	{
		FItem& FFItem = Items[FoundItem];
		FFItem.Stack -= Amount;
		if (FFItem.Stack <= 0)
		{
			RemoveItem(FoundItem);
		}
		else
		{
			UpdateWeight();
		}
		return true;
	}
	return false;
}

bool UInventoryComponent::TryRemoveItem(FItem& Item, int Amount)
{
	if (Items.Contains(Item))
	{
		Item.Stack -= Amount;
		if (Item.Stack <= 0)
		{
			RemoveItem(Item);
		}
		else
		{
			UpdateWeight();
		}
		return true;
	}
	return false;
}
void UInventoryComponent::RemoveItem(int ItemIndex)
{
	Items.RemoveAt(ItemIndex);
	UpdateWeight();
}

void UInventoryComponent::RemoveItem(FItem& Item)
{
	Items.Remove(Item);
	UpdateWeight();
}

bool UInventoryComponent::HasItemStack(FItem& Item)
{
	return false;
}

bool UInventoryComponent::HasFreeSlot()
{
	return Items.Num() < Slots;
}

bool UInventoryComponent::HasItem(const UItemAsset* CheckItem, int& OutItem)
{
	for (int i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Asset == CheckItem)
		{
			OutItem = i;
			return true;
		}
	}
	return false;
}
bool UInventoryComponent::HasItemNoUnique(const UItemAsset* CheckItem, FItem& OutItem)
{
	for (FItem Item : Items)
	{
		if (Item.Asset->Unique) continue;

		if (Item.Asset == CheckItem)
		{
			OutItem = Item;
			return true;
		}
	}
	return false;
}

void UInventoryComponent::AssignArmor(UArmorAsset* ArmorAsset, FItem& ItemInstance, EArmorSocket ArmorSocket)
{
	switch (ArmorSocket)
	{
	case EArmorSocket::Head:
	{
		HeadItem = &ItemInstance;
		break;
	}
	case EArmorSocket::Chest:
	{
		ChestItem = &ItemInstance;
		break;
	}
	case EArmorSocket::Gloves:
	{
		GlovesItem = &ItemInstance;
		break;
	}
	case EArmorSocket::Legs:
	{
		LegsItem = &ItemInstance;
		break;
	}
	case EArmorSocket::Boots:
	{
		BootsItem = &ItemInstance;
		break;
	}
	}
}

void UInventoryComponent::AssignWeapon(UWeaponAsset* WeaponAsset, FItem& ItemInstance)
{
	WeaponItem = &ItemInstance;
}

void UInventoryComponent::Load(TArray<FItem> LoadedItems)
{
	this->Items = LoadedItems;
}

TArray<FItem>& UInventoryComponent::GetItems()
{
	return Items;
}


void UInventoryComponent::UpdateWeight()
{
	for (FItem Item : Items)
	{
		Weight += Item.Asset->Weight * Item.Stack;
	}
	if (Weight > MaxWeight)
	{
		bOverweight = true;
	}
}

