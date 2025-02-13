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

void UInventoryComponent::EquipArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket)
{
	switch (ArmorSocket)
	{
	case EArmorSocket::Chest:
	{
		if (ChestItem == ItemInstance) DequipArmor(ArmorAsset, ItemInstance, ArmorSocket);
		else ChestItem = ItemInstance;
		break;
	}
	case EArmorSocket::Gloves:
	{
		if (GlovesItem == ItemInstance) DequipArmor(ArmorAsset, ItemInstance, ArmorSocket);
		else GlovesItem = ItemInstance;
		break;
	}
	case EArmorSocket::Trousers:
	{
		if(TrousersItem == ItemInstance) DequipArmor(ArmorAsset, ItemInstance, ArmorSocket);
		else TrousersItem = ItemInstance;
		break;
	}
	case EArmorSocket::Boots:
	{
		if(BootsItem == ItemInstance) DequipArmor(ArmorAsset, ItemInstance, ArmorSocket);
		else BootsItem = ItemInstance;
		break;
	}
	}

	OnEquipmentChanged.Broadcast();
}

void UInventoryComponent::EquipWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance)
{
	if (WeaponItem == ItemInstance) DequipWeapon(WeaponAsset, ItemInstance);
	else WeaponItem = ItemInstance;

	OnEquipmentChanged.Broadcast();
}

void UInventoryComponent::DequipArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket)
{
	switch (ArmorSocket)
	{
	case EArmorSocket::Chest:
	{
		ChestItem = nullptr;
		break;
	}
	case EArmorSocket::Gloves:
	{
		GlovesItem = nullptr;
		break;
	}
	case EArmorSocket::Trousers:
	{
		TrousersItem = nullptr;
		break;
	}
	case EArmorSocket::Boots:
	{
		BootsItem = nullptr;
		break;
	}
	}
}

void UInventoryComponent::DequipWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance)
{
	WeaponItem = nullptr;
}

void UInventoryComponent::Load(TArray<UItem*> LoadedItems)
{
	this->Items = LoadedItems;
}

float UInventoryComponent::GetEquippedArmorDefense()
{
	float Defense = 0.f;
	if (ChestItem)
	{
		if (UArmorAsset* ArmorAsset = Cast<UArmorAsset>(ChestItem->Asset))
		{
			Defense += ArmorAsset->ArmorStrength;
		}
	}
	if (GlovesItem)
	{
		if (UArmorAsset* ArmorAsset = Cast<UArmorAsset>(GlovesItem->Asset))
		{
			Defense += ArmorAsset->ArmorStrength;
		}
	}
	if (TrousersItem)
	{
		if (UArmorAsset* ArmorAsset = Cast<UArmorAsset>(TrousersItem->Asset))
		{
			Defense += ArmorAsset->ArmorStrength;
		}
	}
	if (BootsItem)
	{
		if (UArmorAsset* ArmorAsset = Cast<UArmorAsset>(BootsItem->Asset))
		{
			Defense += ArmorAsset->ArmorStrength;
		}
	}
	return Defense;
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

