// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "Data/NPCData.h"
#include "NonPlayableCharacter.generated.h"

struct FNPCScheduleEvent;
class UBoxComponent;
class ANPCController;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API ANonPlayableCharacter : public ACharacter, public IInteractable, public IHealth
{
	GENERATED_BODY()

public:
	ANonPlayableCharacter();

	// IInteractable
	virtual void Interact(AGoingActionCharacter* Character) override;
	virtual FVector GetInterfaceLocation() override;
	virtual bool IsAbleToInteract() override;
	virtual FText GetInteractionName() override;

	// IHealth
	virtual void GetHit(float Damage, FVector HitLocation) override;
	virtual ELoyalty GetLoyalty() override;
	virtual bool TakeTokens(int Tokens) override;
	virtual void ReturnTokens(int Tokens) override;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	UFUNCTION()
	virtual void OnInteractionOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractionOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Interactable Actor")
	UBoxComponent* InteractionBox = nullptr;

	UFUNCTION()
	virtual void Die();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int AttackTokens = 1;
public:	
	virtual void Tick(float DeltaTime) override;

	bool GetCurrentSchedule(FNPCScheduleEvent& Schedule, int& Index);
	FNPCScheduleEvent& GetSchedule(int Index);
private:

	ANPCController* Controller = nullptr;
	float Health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	UNPCData* NPCData = nullptr;
};
