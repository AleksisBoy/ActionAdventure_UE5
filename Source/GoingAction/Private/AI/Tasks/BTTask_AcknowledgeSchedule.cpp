// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_AcknowledgeSchedule.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/NonPlayableCharacter.h"
#include "Data/NPCData.h"
#include "Actors/WorldLocation.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_AcknowledgeSchedule::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// check current time, depending on time do corresponding schedule, assign blackboard variables for it

	AAIController* Controller = OwnerComp.GetAIOwner();
	if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(Controller->GetPawn()))
	{
		FNPCScheduleEvent Schedule = {};
		int Index = 0;
		if (NPC->GetCurrentSchedule(Schedule, Index))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLocation", AWorldLocation::Get(Schedule.Location)->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsInt("CurrentScheduleIndex", Index);
			NPC->SetWalkSpeed(150.f);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
