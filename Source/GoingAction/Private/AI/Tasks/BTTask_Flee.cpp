// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_Flee.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Actors/NonPlayableCharacter.h"
#include "Data/NPCData.h"
#include "Interfaces/Health.h"
#include "Actors/WorldLocation.h"
#include "AIController.h"
#include "AI/CombatSubsystem.h"
//#include "NavigationSystem.h"
//#include "AI/NavigationSystemBase.h"

EBTNodeResult::Type UBTTask_Flee::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Run away from attackers/combat
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (UCombatSubsystem* CombatSub = GetWorld()->GetSubsystem<UCombatSubsystem>())
	{
		FVector PawnLocation = Controller->GetPawn()->GetActorLocation();
		FVector DirectionToCombat = CombatSub->GetCombatLocation() - PawnLocation;
		float DistanceToCombat = DirectionToCombat.Length();

		if (DistanceToCombat > FleeDistance)
		{
			CombatSub->RemoveMember(Cast<IHealth>(Controller->GetPawn()));
			OwnerComp.GetBlackboardComponent()->SetValueAsBool("InCombat", false);
			return EBTNodeResult::Failed;
		}

		DirectionToCombat.Normalize();
		Controller->MoveToLocation(PawnLocation + -DirectionToCombat * FleeDistance);
		if (ANonPlayableCharacter* NPC = Cast<ANonPlayableCharacter>(Controller->GetPawn()))
		{
			NPC->SetWalkSpeed(FleeSpeed);
		}
		return EBTNodeResult::Succeeded;
		/*UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		if (!NavSystem)
		{
			return EBTNodeResult::Failed;
		}

		FNavLocation NavLocation;
		NavSystem->Get
		if (NavSystem->GetRandomReachablePointInRadius(Controller->GetPawn()->GetActorLocation(), 800.f, NavLocation))
		{
			Controller->MoveToLocation(NavLocation.Location);
			return EBTNodeResult::Succeeded;
		}*/
	}
	return EBTNodeResult::Failed;
}
