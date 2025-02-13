// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NPCData.generated.h"

class ULocationData;

UENUM(Blueprintable, BlueprintType)
enum class ENPCActivityType : uint8
{
	Work UMETA(DisplayName = "Work"),
	Eat UMETA(DisplayName = "Eat"),
	Sleep UMETA(DisplayName = "Sleep")
};

USTRUCT(Blueprintable, BlueprintType)
struct FNPCScheduleEvent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StartTime;  

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EndTime;    

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ENPCActivityType Activity; 

	// change to data asset of location, place that can be chosen from editor and will point to the place on the 
	// map where this activity can be done
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ULocationData* Location;  // Where to perform the activity
};

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UNPCData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC Data")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC Data")
	TArray<FNPCScheduleEvent> Schedule;
};
