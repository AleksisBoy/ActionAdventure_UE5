// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldLocation.generated.h"

class UBoxComponent;
class ULocationData;

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API AWorldLocation : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorldLocation();

	static AWorldLocation* Get(ULocationData* Data);
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type Reason) override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, Category = "Interactable Actor")
	UBoxComponent* BoundsBox = nullptr;
private:
	static TArray<AWorldLocation*> Active;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "World Location", meta = (AllowPrivateAccess = "true"))
	ULocationData* LocationData = nullptr;
};
