// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Health.generated.h"


UENUM(Blueprintable, BlueprintType)
enum class ELoyalty : uint8
{
	Friendly UMETA(DisplayName = "Friendly"),
	Neutral UMETA(DisplayName = "Neutral"),
	Hostile UMETA(DisplayName = "Hostile")
};

UINTERFACE(MinimalAPI, NotBlueprintable)
class UHealth : public UInterface
{
	GENERATED_BODY()
};

class GOINGACTION_API IHealth
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void GetHit(float Damage, FVector HitLocation) = 0;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual ELoyalty GetLoyalty() = 0;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual FVector GetInterfaceLocation() = 0;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual bool TakeTokens(int Tokens) = 0;

	UFUNCTION(BlueprintCallable, Category = "Health")
	virtual void ReturnTokens(int Tokens) = 0;

	static bool EnemiesCompare(IHealth* Main, IHealth* Other)
	{
		if (!Main || !Other) return false;
		return Main->GetLoyalty() != Other->GetLoyalty();
	}
};
