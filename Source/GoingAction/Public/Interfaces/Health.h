// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Health.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UHealth : public UInterface
{
	GENERATED_BODY()
};

class GOINGACTION_API IHealth
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Health")
	void GetHit(float Damage, FVector HitLocation);
};
