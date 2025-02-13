// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/NonPlayableCharacter.h"
#include "NPCController.h"
#include "Data/NPCData.h"
#include "WorldInfo.h"

ANonPlayableCharacter::ANonPlayableCharacter()
{
	AIControllerClass = ANPCController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ANonPlayableCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
void ANonPlayableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool ANonPlayableCharacter::GetCurrentSchedule(FNPCScheduleEvent& Schedule)
{
	if (!NPCData) return false;

	if (UWorldInfo* WorldInfo = GetWorld()->GetSubsystem<UWorldInfo>())
	{
		float Time = WorldInfo->GetTime();
		for (FNPCScheduleEvent& NPCSchedule : NPCData->Schedule)
		{
			if (NPCSchedule.StartTime > Time || NPCSchedule.EndTime < Time) continue;
			Schedule = NPCSchedule;
			return true;
		}
	}
	Schedule = NPCData->Schedule[0];
	return false;
}



