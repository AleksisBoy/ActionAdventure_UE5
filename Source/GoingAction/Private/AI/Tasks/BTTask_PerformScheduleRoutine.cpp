// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_PerformScheduleRoutine.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/NonPlayableCharacter.h"
#include "Data/NPCData.h"
#include "Actors/WorldLocation.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_PerformScheduleRoutine::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check for time?
	// play according animation

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(Controller->GetPawn()))
	{
		int CurrentScheduleIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt("CurrentScheduleIndex");

		FNPCScheduleEvent& ScheduleEvent = NPC->GetSchedule(CurrentScheduleIndex);
		OwnerComp.GetBlackboardComponent()->SetValueAsFloat("ScheduleInteractionWaitTime", ScheduleEvent.ActivityWaitTime);
		NPC->PlayAnimMontage(ScheduleEvent.ActivityAnimation);
		// Launch animation
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
