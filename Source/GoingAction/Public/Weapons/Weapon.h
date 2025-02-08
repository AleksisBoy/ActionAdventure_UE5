// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class UBoxComponent;

UCLASS()
class GOINGACTION_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Equip();

	UFUNCTION()
	virtual void Dequip();
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UBoxComponent* BoxComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float Damage = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float AttackCooldown = 0.25f;
	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float AttackCooldown = 0.25f;*/
	
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	float LastAttackTime = 0.f;
};
