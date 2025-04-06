// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldInfoSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHourPassed);

UCLASS()
class GOINGACTION_API UWorldInfoSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	UWorldInfoSubsystem();

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
