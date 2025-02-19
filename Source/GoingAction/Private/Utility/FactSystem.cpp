// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/FactSystem.h"


void UFactSystem::Initialize(FSubsystemCollectionBase& Collection)
{
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

