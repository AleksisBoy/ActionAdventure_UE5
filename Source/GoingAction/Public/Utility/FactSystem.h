// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Fact.h"
#include "Interfaces/SaveLoad.h"
#include "FactSystem.generated.h"

class USaveInstance;

UCLASS(BlueprintType)
class GOINGACTION_API UFactSystem : public UGameInstanceSubsystem, public ISaveLoad
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Facts")
	bool CheckFact(EFact Fact);

	UFUNCTION(BlueprintCallable, Category = "Facts")
	void UpdateFact(EFact Fact, bool NewValue);

	// ISaveLoad
	virtual void SaveState(USaveInstance* SaveInstance) override;
	virtual void LoadState(USaveInstance* SaveInstance) override;
protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

private:
	TMap<EFact, bool> Facts;
};
