// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_PerformScheduleRoutine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/NonPlayableCharacter.h"
#include "Data/NPCData.h"
#include "Actors/WorldLocation.h"

EBTNodeResult::Type UBTTask_PerformScheduleRoutine::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check for time?
	// play according animation

	if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(OwnerComp.GetOwner()))
	{
		int CurrentScheduleIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt("CurrentScheduleIndex");

		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("ScheduleInteractionWaitTime", NPC->GetSchedule(CurrentScheduleIndex).ActivityWaitTime);
		
		// Launch animation
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
