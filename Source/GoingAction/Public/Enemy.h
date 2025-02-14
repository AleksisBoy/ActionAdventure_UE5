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
	virtual void GetHit(float Damage, FVector HitLocation) override;
	virtual ELoyalty GetLoyalty() override;
	virtual FVector GetInterfaceLocation() override;
	virtual bool TakeTokens(int Tokens) override;
	virtual void ReturnTokens(int Tokens) override;

	virtual void Tick(float DeltaTime) override;

	static TArray<AEnemy*> Active;
protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type Reason) override;
};
