// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

class AGoingActionCharacter;

UINTERFACE(MinimalAPI, NotBlueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class GOINGACTION_API IInteractable
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Interactable")
	virtual void Interact(AGoingActionCharacter* Character) = 0;

	UFUNCTION(BlueprintCallable,  Category = "Interactable")
	virtual bool IsAbleToInteract() = 0;

	UFUNCTION(BlueprintCallable,  Category = "Interactable")
	virtual FVector GetInterfaceLocation() = 0;

	UFUNCTION(BlueprintCallable,  Category = "Interactable")
	virtual FText GetInteractionName() = 0;

	UFUNCTION(BlueprintCallable,  Category = "Interactable")
	virtual FText GetInteractionText() = 0;
};
