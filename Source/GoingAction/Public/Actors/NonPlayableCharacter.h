// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NonPlayableCharacter.generated.h"

class UNPCData;
struct FNPCScheduleEvent;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API ANonPlayableCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ANonPlayableCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	bool GetCurrentSchedule(FNPCScheduleEvent& Schedule);
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	UNPCData* NPCData = nullptr;
};
