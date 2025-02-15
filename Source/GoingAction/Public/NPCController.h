// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameplayTagContainer.h"
#include "NPCController.generated.h"

class UBehaviourTree;
class UBlackboardComponent;
class UBehaviorTreeComponent;

UCLASS()
class GOINGACTION_API ANPCController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTree;

    void SetCombatSubTree(FGameplayTag GameplayTag, UBehaviorTree* CombatTree);

private:
    UBehaviorTreeComponent* BTComp;
};
