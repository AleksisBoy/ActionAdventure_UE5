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

	UFUNCTION(BlueprintCallable, Category = "Item Pickup")
	bool Loot(UItemAsset* Item, int& OutAmount);

	virtual void Interact(AGoingActionCharacter* Character) override;
	virtual bool IsAbleToInteract() override;
	virtual FText GetInteractionName() override;
	virtual FText GetInteractionText() override;
protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult) override;

	void ItemsEmptied();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Pickup")
	FText PickupActorName = FText::FromString(TEXT("DEFAULT"));

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Pickup")
	bool Looted = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Pickup")
	float LifetimeOnLooted = 0.08f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pickup")
	bool DestroyOnLooted = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pickup")
	TMap<UItemAsset*, int> Items;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item Pickup")
	bool OpenPickupStashWidget = true;
};
