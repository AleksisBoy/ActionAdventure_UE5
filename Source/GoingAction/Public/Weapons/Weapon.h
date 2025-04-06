// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Utility/Prerequisites.h"
#include "Weapon.generated.h"

class UBoxComponent;
class UWeaponAsset;

UCLASS()
class GOINGACTION_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	

	AWeapon();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void Sheathe();

	UFUNCTION()
	virtual void UnSheathe();

	void UpdateLocationAndRotation();

	UFUNCTION()
	void SetData(UWeaponAsset* NewData);

	UWeaponAsset* GetData() { return Data; }
	//TArray<FAttackMontageData> GetAttackAnimations() { return AttackAnimations; }
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	UWeaponAsset* Data = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	USceneComponent* HandleComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	UStaticMeshComponent* Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UBoxComponent* BoxComp = nullptr;


	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	//TArray<FAttackMontageData> AttackAnimations;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	//float Damage = 10.f;

	//// cooldown will be measured by animmontage
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	//float AttackCooldown = 0.25f;
	
	// needed?
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	float LastAttackTime = 0.f;

	bool bSheathed = false;
};
