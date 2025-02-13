// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Actors/NonPlayableCharacter.h" 

void ANPCController::BeginPlay()
{
    Super::BeginPlay();

    if (BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
}

void ANPCController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(InPawn))
    {

        if (BehaviorTree)
        {
            RunBehaviorTree(BehaviorTree);
        }
    }
}
