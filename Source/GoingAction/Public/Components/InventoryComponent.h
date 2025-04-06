// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/ItemAsset.h"
#include "Data/ArmorAsset.h"
#include "Data/WeaponAsset.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEquipmentChanged);

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


	void EquipArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket);
	void EquipWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance);

	void DequipArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket);
	void DequipWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance);

	UItem* GetSteelWeaponAsset() { return SteelWeaponItem; }
	UItem* GetSilverWeaponAsset() { return SilverWeaponItem; }

	UPROPERTY(BlueprintAssignable)
	FEquipmentChanged OnEquipmentChanged;

	void Load(TArray<UItem*> LoadedItems);


	UFUNCTION(BlueprintCallable, Category = "Inventory")
	float GetEquippedArmorDefense();

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
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UItem* ChestItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UItem* GlovesItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UItem* TrousersItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UItem* BootsItem;

	// Weapon Sockets
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UItem* SteelWeaponItem;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	UItem* SilverWeaponItem;

	// Consumable Sockets
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
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
