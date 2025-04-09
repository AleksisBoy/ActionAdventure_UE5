// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CombatSubsystem.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"

UCombatSubsystem::UCombatSubsystem()
{
}

void UCombatSubsystem::StartCombat(IHealth* Initiator)
{
	AddMember(Initiator);
}

void UCombatSubsystem::AddMember(IHealth* Member)
{
	Members.AddUnique(Member);
}

void UCombatSubsystem::RemoveMember(IHealth* Member)
{
	if (Members.Contains(Member))
	{
		Members.Remove(Member);
	}
}

bool UCombatSubsystem::CallForCombat(FVector Location, float Radius, AActor* Initiator)
{
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	TArray<AActor*> ActorsToIgnore; 
	ActorsToIgnore.Add(Initiator);
	TArray<AActor*> OutActors;

	UKismetSystemLibrary::SphereOverlapActors(
		GetWorld(),
		Location,
		Radius,
		ObjectTypes,
		ACharacter::StaticClass(),
		ActorsToIgnore,
		OutActors
	);
	
	TArray<IHealth*> LivingEntities;
	for (AActor* Character : OutActors)
	{
		UE_LOG(LogTemp, Warning, TEXT("found: %s"), *Character->GetName());

		if (IHealth* LivingEntity = Cast<IHealth>(Character))
		{
			if (!LivingEntity->IsAbleToCombat() || Members.Contains(LivingEntity)) continue; 
			
			LivingEntities.Add(LivingEntity);
			LivingEntity->EnterCombat();
			AddMember(LivingEntity);
		}
	}
	return Members.Num() != 0;
}

IHealth* UCombatSubsystem::GetClosestTargetFor(IHealth* HealthInterface, int AttackTokens)
{
	if (Members.Num() == 0) return nullptr;

	TArray<IHealth*> Enemies;
	for (IHealth* Member : Members)
	{
		if (IHealth::EnemiesCompare(HealthInterface, Member))
		{
			Enemies.AddUnique(Member);
		}
	}
	for (IHealth* Enemy : Enemies)
	{
		if (Enemy->TakeTokens(AttackTokens))
		{
			UE_LOG(LogTemp, Warning, TEXT("FOUND Enemy"));
			return Enemy;
		}
	}
	return nullptr;
}

FVector UCombatSubsystem::GetCombatLocation()
{
	if (Members.Num() == 0) return FVector();

	FVector CombatLocation;
	for (IHealth* Member : Members)
	{
		CombatLocation += Member->GetInterfaceLocation();
	}
	return CombatLocation / Members.Num();
}

void UCombatSubsystem::Tick(float DeltaTime)
{
}
