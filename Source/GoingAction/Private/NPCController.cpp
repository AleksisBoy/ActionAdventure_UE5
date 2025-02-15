// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Actors/NonPlayableCharacter.h" 

void ANPCController::BeginPlay()
{
    Super::BeginPlay();

    //bool bSuccess = false;
    //UBlackboardComponent* BlackboardComp = Blackboard;
    //if (BehaviorTree->BlackboardAsset && (Blackboard == nullptr || Blackboard->IsCompatibleWith(BehaviorTree->BlackboardAsset) == false))
    //{
    //    bSuccess = UseBlackboard(BehaviorTree->BlackboardAsset, BlackboardComp);
    //}
    
    if (BehaviorTree)
    {
        RunBehaviorTree(BehaviorTree);
    }
    BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (!BTComp) BTComp = GetComponentByClass<UBehaviorTreeComponent>();;
    
    if (BTComp)
    {
        UE_LOG(LogTemp, Warning, TEXT("FOund bt comp"));
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

void ANPCController::SetCombatSubTree(FGameplayTag GameplayTag, UBehaviorTree* CombatTree)
{
    if (BTComp && CombatTree)
    {
        BTComp->SetDynamicSubtree(GameplayTag, CombatTree);
        BTComp->GetBlackboardComponent()->SetValueAsBool("HasCombatBehavior", true);
        UE_LOG(LogTemp, Warning, TEXT("Assigned combat"));
    }
}

