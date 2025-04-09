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

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void OnAttackStart();
	void OnAttackFinish();

	UFUNCTION()
	virtual void Sheathe();

	UFUNCTION()
	virtual void UnSheathe();

	void UpdateLocationAndRotation();

	UFUNCTION()
	void SetData(UWeaponAsset* NewData);

	void SetWielder(AActor* NewWielder) { Wielder = NewWielder; }

	UWeaponAsset* GetData() { return Data; }
	//TArray<FAttackMontageData> GetAttackAnimations() { return AttackAnimations; }
protected:

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

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
	
	AActor* Wielder = nullptr;
	TArray<AActor*> ActorsHit;

	// needed?
	UPROPERTY(BlueprintReadWrite, Category = "Weapon")
	float LastAttackTime = 0.f;

	bool bSheathed = false;
};
