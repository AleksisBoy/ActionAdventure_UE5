// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseInteractableActor.h"
#include "ItemPickupActor.generated.h"

class AGoingActionCharacter;
class UItemAsset;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API AItemPickupActor : public ABaseInteractableActor
{
	GENERATED_BODY()

public:
	AItemPickupActor();

	virtual void Interact_Implementation(AGoingActionCharacter* Character) override;

	UFUNCTION(BlueprintCallable, Category = "Item Pickup")
	bool Loot(UItemAsset* Item, int& OutAmount);
protected:

	virtual void Tick(float DeltaTime) override;

	void ItemsEmptied();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Pickup")
	bool Looted = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Pickup")
	float LifetimeOnLooted = 0.08f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Pickup")
	bool DestroyOnLooted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pickup")
	TMap<UItemAsset*, int> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Pickup")
	bool OpenPickupStashWidget = true;
};
