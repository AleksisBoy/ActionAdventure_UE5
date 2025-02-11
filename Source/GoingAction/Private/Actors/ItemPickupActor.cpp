// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ItemPickupActor.h"
#include "GoingAction/GoingActionCharacter.h"
#include "Components/InventoryComponent.h"

AItemPickupActor::AItemPickupActor() : Super()
{
}
void AItemPickupActor::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(false);
}
void AItemPickupActor::Interact_Implementation(AGoingActionCharacter* Character)
{
	Super::Interact_Implementation(Character);

	if (!Character || Looted) return;

	if (OpenPickupStashWidget)
	{
		Character->OpenPickupStashWidget(Items, this);
	}
	else
	{
		for (TPair<UItemAsset*, int> ItemPair : Items)
		{
			Character->Inventory->TryAddItem(ItemPair.Key, ItemPair.Value);
		}
		Items.Reset();
		ItemsEmptied();
		Character->FindInteractableInFront();
	}
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

void AItemPickupActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Looted) return;

	Super::OnOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}

void AItemPickupActor::ItemsEmptied()
{
	Looted = true;
	if (DestroyOnLooted) SetActorTickEnabled(true);
	if (Overlapping.Contains(this)) Overlapping.Remove(this);
}
