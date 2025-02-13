// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldInfo.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHourPassed);

UCLASS(Blueprintable)
class GOINGACTION_API UWorldInfo : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	UWorldInfo();

	UFUNCTION(BlueprintCallable)
	float GetTime();

	float TimePerSec = 0.02f; 

	UPROPERTY(BlueprintAssignable)
	FHourPassed OnHourPassed;
public:
	virtual TStatId GetStatId() const override
	{
		return GetStatID();
	}
protected:
	virtual void Tick(float DeltaTime) override;
private:
	float Time = 12.f;

	int LastHour = 0;
};
