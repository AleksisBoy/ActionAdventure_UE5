// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Fact.h"
#include "FactSystem.generated.h"

UCLASS(BlueprintType)
class GOINGACTION_API UFactSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Facts")
	bool CheckFact(EFact Fact);

	UFUNCTION(BlueprintCallable, Category = "Facts")
	void UpdateFact(EFact Fact, bool NewValue);

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	TMap<EFact, bool> Facts;
};
