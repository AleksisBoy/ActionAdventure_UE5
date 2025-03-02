// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/FactSystem.h"
#include "Game/ActionGameInstance.h"
#include "Utility/SaveInstance.h"


void UFactSystem::SaveState(USaveInstance* SaveInstance)
{
	UE_LOG(LogTemp, Warning, TEXT("SAVING INSIDE FACT SYSTEM"));

	TMap<uint8, bool> SavedFacts;
	for (TPair<EFact, bool> Pair : Facts)
	{
		SavedFacts.Add((uint8)Pair.Key, Pair.Value);
	}
	SaveInstance->Facts = SavedFacts;
}

void UFactSystem::LoadState(USaveInstance* SaveInstance)
{
	if (SaveInstance == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("LOADING STATE FACT SYSTEM"));
	TMap<EFact, bool> LoadedFacts;
	for (TPair<uint8, bool> Pair : SaveInstance->Facts)
	{
		LoadedFacts.Add((EFact)Pair.Key, Pair.Value);
	}
	Facts = LoadedFacts;
}

void UFactSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	UE_LOG(LogTemp, Warning, TEXT("TRYING TO ASSIGN SAVE FACT SYSTEM"));
	if (UActionGameInstance* ActionGameInstance = (UActionGameInstance*)GetGameInstance())
	{
		UE_LOG(LogTemp, Warning, TEXT("ASSIGNING TO SAVE FACT SYSTEM"));
		ActionGameInstance->AssignToSaving(this, true);
	}
	UE_LOG(LogTemp, Warning, TEXT("CONTINUE FACT SYSTEM"));

	UpdateFact(EFact::DEFAULT_TRUE, true);
}

bool UFactSystem::CheckFact(EFact Fact)
{
	for (TPair<EFact, bool> Pair : Facts)
	{
		if (Pair.Key == Fact)
		{
			return Pair.Value;
		}
	}
	return false;
}

void UFactSystem::UpdateFact(EFact Fact, bool NewValue)
{
	for (TPair<EFact, bool> Pair : Facts)
	{
		if (Pair.Key == Fact)
		{
			Pair.Value = NewValue;
			return;
		}
	}
	Facts.Add(Fact, NewValue);
}

