// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "BaseInteractableActor.generated.h"

class UBoxComponent;
class AGoingActionCharacter;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API ABaseInteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	ABaseInteractableActor();

	virtual void Interact(AGoingActionCharacter* Character) override;

	virtual FVector GetInterfaceLocation() override;
	virtual bool IsAbleToInteract() override;
	virtual FText GetInteractionName() override;
	virtual FText GetInteractionText() override;
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Interactable Actor")
	UBoxComponent* InteractionBox = nullptr;

	UPROPERTY(EditAnywhere, Category = "Interactable Actor")
	UStaticMeshComponent* Mesh = nullptr;
};
