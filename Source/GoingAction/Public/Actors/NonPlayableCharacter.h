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
class UDialogueAsset;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API ANonPlayableCharacter : public ACharacter, public IInteractable, public IHealth
{
	GENERATED_BODY()

public:
	ANonPlayableCharacter();

	virtual void QuitDialogue();

	// IInteractable
	virtual void Interact(AGoingActionCharacter* Character) override;
	virtual FVector GetInteractionLocation() override;
	virtual bool IsAbleToInteract() override;
	virtual FText GetInteractionName() override;
	virtual FText GetInteractionText() override;

	// IHealth
	virtual void GetHit(float Damage, FVector HitLocation) override;
	virtual void HealPrecise(float HealHealth) override;
	virtual void HealPerc(float Perc) override;
	virtual ELoyalty GetLoyalty() override;
	virtual FVector GetInterfaceLocation() { return GetActorLocation(); }
	virtual bool TakeTokens(int Tokens) override;
	virtual void ReturnTokens(int Tokens) override;

	virtual bool TryFindCombatTarget();

	void SetWalkSpeed(float Speed);
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
	int MyAttackTokens = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Combat")
	TScriptInterface<IHealth> CurrentTarget = nullptr;

	UPROPERTY(EditAnywhere, Category = "NPC")
	UDialogueAsset* NPCDialogue = nullptr;

	UPROPERTY(EditAnywhere, Category = "NPC")
	FVector InteractionWidgetOffset = FVector();
public:	
	virtual void Tick(float DeltaTime) override;

	bool GetCurrentSchedule(FNPCScheduleEvent& Schedule, int& Index);
	FNPCScheduleEvent& GetSchedule(int Index);
private:

	ANPCController* Controller = nullptr;
	float Health = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC", meta = (AllowPrivateAccess = "true"))
	UNPCData* NPCData = nullptr;

	UPROPERTY()
	bool InDialogue = false;
};
