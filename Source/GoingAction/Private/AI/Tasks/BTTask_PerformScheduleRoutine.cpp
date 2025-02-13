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

	return EBTNodeResult::InProgress;
	if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(OwnerComp.GetOwner()))
	{
		FNPCScheduleEvent Schedule = {};
		if (NPC->GetCurrentSchedule(Schedule))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", AWorldLocation::Get(Schedule.Location)->GetActorLocation());
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Type();
}
