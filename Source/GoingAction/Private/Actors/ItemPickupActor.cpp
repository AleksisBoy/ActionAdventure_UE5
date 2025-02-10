// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemPickupActor.h"
#include "GoingAction/GoingActionCharacter.h"
#include "Components/InventoryComponent.h"

AItemPickupActor::AItemPickupActor() : Super()
{
	SetActorTickEnabled(false);
}
void AItemPickupActor::Interact_Implementation(AGoingActionCharacter* Character)
{
	Super::Interact_Implementation(Character);

	if (!Character || Looted) return;

	Character->OpenPickupStashWidget(Items);
}

bool AItemPickupActor::Loot(UItemAsset* Item, int& OutAmount)
{
	if (Items.Contains(Item))
	{
		OutAmount = Items[Item];
		Items.Remove(Item);

		if (Items.Num() == 0) ItemsEmptied();
		return true;
	}
	return false;
}

void AItemPickupActor::Tick(float DeltaTime)
{
	if (!Looted) return;

	LifetimeOnLooted -= DeltaTime;
	if (LifetimeOnLooted <= 0)
	{
		Destroy();
	}
}

void AItemPickupActor::ItemsEmptied()
{
	Looted = true;
	SetActorTickEnabled(true);
	if (Overlapping.Contains(this)) Overlapping.Remove(this);
}
