// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NonPlayableCharacter.h"
#include "NPCController.h"
#include "Data/NPCData.h"
#include "WorldInfo.h"
#include "Components/BoxComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AI/CombatSubsystem.h"

ANonPlayableCharacter::ANonPlayableCharacter() : Super()
{
	AIControllerClass = ANPCController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Interaction Box
	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Interaction Box"));
	InteractionBox->SetupAttachment(RootComponent);

	InteractionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	InteractionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ANonPlayableCharacter::Interact(AGoingActionCharacter* Character)
{
}

FVector ANonPlayableCharacter::GetInterfaceLocation()
{
	return GetActorLocation();
}

bool ANonPlayableCharacter::IsAbleToInteract()
{
	// Add logic
	return true;
}

FText ANonPlayableCharacter::GetInteractionName()
{
	return FText::FromString(GetName());
}

void ANonPlayableCharacter::GetHit(float Damage, FVector HitLocation)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		Die();
	}
}

ELoyalty ANonPlayableCharacter::GetLoyalty()
{
	if (!NPCData) return ELoyalty::Friendly;
	return NPCData->Loyalty;
}

bool ANonPlayableCharacter::TakeTokens(int Tokens)
{
	if (AttackTokens < Tokens) return false;

	AttackTokens -= Tokens;
	return true;
}

void ANonPlayableCharacter::ReturnTokens(int Tokens)
{
	AttackTokens += Tokens;
}


void ANonPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (!NPCData) { UE_LOG(LogTemp, Error, TEXT("NO DATA FOR %s"), *GetName()); return; }

	Controller = Cast<ANPCController>(GetController());

	InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &ANonPlayableCharacter::OnInteractionOverlapBegin);
	InteractionBox->OnComponentEndOverlap.AddDynamic(this, &ANonPlayableCharacter::OnInteractionOverlapEnd);

	Health = NPCData->BaseHealth;
}
void ANonPlayableCharacter::EndPlay(const EEndPlayReason::Type Reason)
{
	/*if (Overlapping.Contains(this))
	{
		Overlapping.Remove(this);
	}*/
}
void ANonPlayableCharacter::OnInteractionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// check if it is a player 
	if (OtherActor == this) return;

	Controller->GetBlackboardComponent()->SetValueAsBool("InCombat", true);

	if (UCombatSubsystem* CombatSub = GetWorld()->GetSubsystem<UCombatSubsystem>())
	{
		CombatSub->StartCombat(this);
	}
	UE_LOG(LogTemp, Warning, TEXT("ADDED"));
	//Overlapping.AddUnique(this);
}
void ANonPlayableCharacter::OnInteractionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//if (Overlapping.Contains(this)) Overlapping.Remove(this);
}
void ANonPlayableCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("%s DIED"), *GetName());
}
void ANonPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool ANonPlayableCharacter::GetCurrentSchedule(FNPCScheduleEvent& Schedule, int& Index)
{
	if (!NPCData) return false;
	if (NPCData->Schedule.Num() == 1) { Schedule = NPCData->Schedule[0]; Index = 0; return true; }

	if (UWorldInfo* WorldInfo = GetWorld()->GetSubsystem<UWorldInfo>())
	{
		float Time = WorldInfo->GetTime();
		Index = 0;
		for (FNPCScheduleEvent& NPCSchedule : NPCData->Schedule)
		{
			if (NPCSchedule.StartTime > Time || NPCSchedule.EndTime < Time) { Index++; continue; }
			Schedule = NPCSchedule;
			return true;
		}
	}
	return false;
}

FNPCScheduleEvent& ANonPlayableCharacter::GetSchedule(int Index)
{
	return NPCData->Schedule[Index];
}



