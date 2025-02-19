// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_LookAtTargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"

EBTNodeResult::Type UBTTask_LookAtTargetLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//UE_LOG(LogTemp, Warning, TEXT("LOOK AT"));
	FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(FName("TargetLocation"));
	AActor* Self = OwnerComp.GetOwner();
	if (!Self) return EBTNodeResult::Failed;

	FVector DirectionToTarget = TargetLocation - Self->GetActorLocation();
	//DirectionToTarget.Z = 0.f;
	DirectionToTarget.Normalize();

	FVector DirectionForward = Self->GetActorForwardVector();
	//DirectionForward.Z = 0.f;
	DirectionForward.Normalize();

	float Dot = FVector::DotProduct(DirectionForward, DirectionToTarget);
	//UE_LOG(LogTemp, Warning, TEXT("DOT: %f"), Dot);
	//UE_LOG(LogTemp, Warning, TEXT("Delta: %f"), OwnerComp.GetAccumulatedTickDeltaTime());
	if (Dot < MinDot)
	{
		//FQuat LookAtRotation = FRotationMatrix::MakeFromXY(DirectionToTarget, ).ToQuat();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(Self->GetActorLocation(), TargetLocation);
		FQuat LerpedQuat = FQuat::Slerp(Self->GetActorRotation().Quaternion(), LookAtRotation.Quaternion(), OwnerComp.GetAccumulatedTickDeltaTime() * RotationSpeed);
		Self->SetActorRotation(LerpedQuat);
		return EBTNodeResult::InProgress;
	}
	else
	{
		return EBTNodeResult::Succeeded;
	}
}
