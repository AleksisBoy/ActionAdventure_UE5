// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Interfaces/Health.h"
#include "GameplayTagContainer.h"
#include "NPCData.generated.h"

class ULocationData;
class UBehaviorTree;
class UAnimMontage;

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
	float StartTime = 0.f;  

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EndTime = 0.f;    
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ENPCActivityType Activity = ENPCActivityType::Eat; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ActivityWaitTime = 0.f;

	// change to data asset of location, place that can be chosen from editor and will point to the place on the 
	// map where this activity can be done
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ULocationData* Location = nullptr;  // Where to perform the activity

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* ActivityAnimation = nullptr;
};

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UNPCData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC Data")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC Data")
	float BaseHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC Data")
	ELoyalty Loyalty;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "NPC Data")
	TArray<FNPCScheduleEvent> Schedule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Combat Data")
	UBehaviorTree* CombatSubTree;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "NPC Combat Data")
	FGameplayTag CombatSubTreeTag;
};
