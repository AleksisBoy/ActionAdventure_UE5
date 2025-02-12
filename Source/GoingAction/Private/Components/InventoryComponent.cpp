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
	for (UItem* Item : Items)
	{
		if (Item->Asset == NewItem &&
			Item->Stack + Amount <= Item->Asset->MaxStack)
		{
			Item->Stack += Amount;
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
	UItem* CreatedItem = NewObject<UItem>();
	CreatedItem->Asset = NewItem;
	CreatedItem->Stack = Amount;

	Items.Add(CreatedItem);
	UpdateWeight();
}
bool UInventoryComponent::TryRemoveItemAsset(const UItemAsset* Item, int Amount)
{
	int FoundItem;
	if (HasItem(Item, FoundItem))
	{
		UItem* FUItem = Items[FoundItem];
		FUItem->Stack -= Amount;
		if (FUItem->Stack <= 0)
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

bool UInventoryComponent::TryRemoveItem(UItem* Item, int Amount)
{
	if (Items.Contains(Item))
	{
		Item->Stack -= Amount;
		if (Item->Stack <= 0)
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

void UInventoryComponent::RemoveItem(UItem* Item)
{
	Items.Remove(Item);
	UpdateWeight();
}

bool UInventoryComponent::HasItemStack(UItem* Item)
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
		if (Items[i]->Asset == CheckItem)
		{
			OutItem = i;
			return true;
		}
	}
	return false;
}
bool UInventoryComponent::HasItemNoUnique(const UItemAsset* CheckItem, UItem*& OutItem)
{
	for (UItem* Item : Items)
	{
		if (Item->Asset->Unique) continue;

		if (Item->Asset == CheckItem)
		{
			OutItem = Item;
			return true;
		}
	}
	return false;
}

void UInventoryComponent::AssignArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket)
{
	switch (ArmorSocket)
	{
	case EArmorSocket::Head:
	{
		HeadItem = ItemInstance;
		break;
	}
	case EArmorSocket::Chest:
	{
		ChestItem = ItemInstance;
		break;
	}
	case EArmorSocket::Gloves:
	{
		GlovesItem = ItemInstance;
		break;
	}
	case EArmorSocket::Legs:
	{
		LegsItem = ItemInstance;
		break;
	}
	case EArmorSocket::Boots:
	{
		BootsItem = ItemInstance;
		break;
	}
	}
}

void UInventoryComponent::AssignWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance)
{
	WeaponItem = ItemInstance;
}

void UInventoryComponent::Load(TArray<UItem*> LoadedItems)
{
	this->Items = LoadedItems;
}

TArray<UItem*> UInventoryComponent::GetItems()
{
	return Items;
}


void UInventoryComponent::UpdateWeight()
{
	for (UItem* Item : Items)
	{
		Weight += Item->Asset->Weight * Item->Stack;
	}
	if (Weight > MaxWeight)
	{
		bOverweight = true;
	}
}

