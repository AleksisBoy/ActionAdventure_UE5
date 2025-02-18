// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_LookAtTargetLocation.generated.h"

UCLASS()
class GOINGACTION_API UBTTask_LookAtTargetLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Look At Target")
	float MinDot = 0.9f;

	UPROPERTY(EditAnywhere, Category = "Look At Target")
	float RotationSpeed = 1.f;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
