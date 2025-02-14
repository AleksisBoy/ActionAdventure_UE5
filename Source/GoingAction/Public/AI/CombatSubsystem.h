// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "Interfaces/Health.h"
#include "CombatSubsystem.generated.h"

UCLASS(Blueprintable)
class GOINGACTION_API UCombatSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	UCombatSubsystem();

	TArray<IHealth*> Members;

	void StartCombat(IHealth* Initiator);

	IHealth* GetClosestTargetFor(IHealth* HealthInterface, int AttackTokens);
	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}
protected:
	virtual void Tick(float DeltaTime) override;
};
