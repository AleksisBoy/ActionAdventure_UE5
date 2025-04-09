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


	void StartCombat(IHealth* Initiator);
	void AddMember(IHealth* Member);
	void RemoveMember(IHealth* Member);
	TArray<IHealth*> GetMembers() { return Members; }

	bool CallForCombat(FVector Location, float Radius, AActor* Initiator);

	IHealth* GetClosestTargetFor(IHealth* HealthInterface, int AttackTokens);

	FVector GetCombatLocation();

	// Method used to enable Tick for this class
	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}
protected:
	virtual void Tick(float DeltaTime) override;

	TArray<IHealth*> Members;
	// entity is not in combat ->
	// entity encounters (sees, gets triggered/alerted) other entity that has different loyalty ->
	// entity gets into combat ->
	// entity behaves accordingly their combat behaviour;

	// Player combat behaviour
	// base speed changed
	// in battle stance
	// each weapon has their own animation montages in blueprint which will get called accordingly on demand
	// Input mode changes to combat ->
	// Space key becomes a long dash;
	// Alt key becomes a short dash;
	// Enable targeting option
	// Enjoy the fight
};
