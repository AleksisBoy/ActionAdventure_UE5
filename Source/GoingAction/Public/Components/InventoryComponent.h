// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemAsset.h"
#include "Data/ArmorAsset.h"
#include "Data/WeaponAsset.h"
#include "InventoryComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GOINGACTION_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryAddItem(UItemAsset* NewItem, int Amount);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryRemoveItemAsset(const UItemAsset* Item, int Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool TryRemoveItem(UItem* Item, int Amount);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItemStack(UItem* Item);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasFreeSlot();
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItem(const UItemAsset* CheckItem, int& OutItem);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool HasItemNoUnique(const UItemAsset* CheckItem, UItem*& OutItem);


	void AssignArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket);
	void AssignWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance);

	void Load(TArray<UItem*> LoadedItems);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	TArray<UItem*> GetItems();
protected:
	virtual void BeginPlay() override;

	void AddItem(UItemAsset* NewItem, int Amount);
	void RemoveItem(int ItemIndex);
	void RemoveItem(UItem* Item);

	void UpdateWeight();

	float Weight = 0.f;
	bool bOverweight = false;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	float MaxWeight = 100.f;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory")
	int Slots = 100;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TArray<UItem*> Items;

	// Inventory Sockets
	// Armor Sockets
	UItem* HeadItem;
	UItem* ChestItem;
	UItem* GlovesItem;
	UItem* LegsItem;
	UItem* BootsItem;

	// Weapon Sockets
	UItem* WeaponItem;

	// Consumable Sockets
	UItem* FoodItem;
};

//
//USTRUCT(Blueprintable, BlueprintType)
//struct FInventorySocket
//{
//	GENERATED_BODY()
//
//	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
//	UItem* Item;
//
//
//
//	//bool operator==(const FInventorySocket& Other) const
//	//{
//	//	return Item == Other.Item && Stack == Other.Stack;
//	//}
//};
