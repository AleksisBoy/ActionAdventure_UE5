// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CombatSubsystem.h"

UCombatSubsystem::UCombatSubsystem()
{
}

void UCombatSubsystem::StartCombat(IHealth* Initiator)
{
	Members.AddUnique(Initiator);
}

IHealth* UCombatSubsystem::GetClosestTargetFor(IHealth* HealthInterface, int AttackTokens)
{
	if (Members.Num() == 0) return nullptr;

	TArray<IHealth*> Enemies;
	for (IHealth* Member : Members)
	{
		if (IHealth::EnemiesCompare(HealthInterface, Member))
		{
			Enemies.AddUnique(Member);
		}
	}
	for (IHealth* Enemy : Enemies)
	{
		if (Enemy->TakeTokens(AttackTokens))
		{
			UE_LOG(LogTemp, Warning, TEXT("FOUND Enemy"));
			return Enemy;
		}
	}
	return nullptr;
}

void UCombatSubsystem::Tick(float DeltaTime)
{
}
