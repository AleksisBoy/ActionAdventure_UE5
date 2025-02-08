// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Health.h"
#include "Enemy.generated.h"

UCLASS()
class GOINGACTION_API AEnemy : public ACharacter, public IHealth
{
	GENERATED_BODY()

public:
	AEnemy();

	// IHealth
	virtual void GetHit_Implementation(float Damage, FVector HitLocation) override;

	virtual void Tick(float DeltaTime) override;

	static TArray<AEnemy*> Active;
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type Reason) override;
};
