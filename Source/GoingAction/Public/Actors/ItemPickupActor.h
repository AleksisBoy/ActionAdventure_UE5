// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/BaseInteractableActor.h"
#include "ItemPickupActor.generated.h"

class AGoingActionCharacter;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API AItemPickupActor : public ABaseInteractableActor
{
	GENERATED_BODY()

public:
	AItemPickupActor();

	virtual void Interact_Implementation(AGoingActionCharacter* Character) override;

protected:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Item Pickup")
	bool Looted = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Pickup")
	float LifetimeOnLooted = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pickup")
	class UItemAsset* Item = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Pickup")
	int Amount = 0;
};
