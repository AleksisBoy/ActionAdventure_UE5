// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_FindCombatTarget.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/NonPlayableCharacter.h"
#include "Data/NPCData.h"
#include "Interfaces/Health.h"
#include "Actors/WorldLocation.h"
#include "AIController.h"
#include "AI/CombatSubsystem.h"

EBTNodeResult::Type UBTTask_FindCombatTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check for surroundings, find out how is the closest (and available in terms of tokens)
	// should only fight those who oppose them in type (Friendly, Neutral, Hostile) 
	// (if neutral then fight friendly and hostile

	// get everyone in the battle (through battle manager?)
	// check the closest one if they are enemies or not
	// Attack the closest one which has a free token and enemy

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(Controller->GetPawn()))
	{
		if (UCombatSubsystem* CombatSub = GetWorld()->GetSubsystem<UCombatSubsystem>())
		{
			CombatSub->GetClosestTargetFor(NPC, 1);
			return EBTNodeResult::Succeeded;
		}
	}
	/*if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(Controller->GetPawn()))
	{
		FNPCScheduleEvent Schedule = {};
		int Index = 0;
		if (NPC->GetCurrentSchedule(Schedule, Index))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", AWorldLocation::Get(Schedule.Location)->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsInt("CurrentScheduleIndex", Index);
			return EBTNodeResult::Succeeded;
		}
	}*/
	return EBTNodeResult::Failed;
}

