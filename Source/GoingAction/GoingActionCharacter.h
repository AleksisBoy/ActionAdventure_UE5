// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/Health.h"
#include "GoingActionCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInventoryComponent;
class ABaseInteractableActor;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableChanged, ABaseInteractableActor*, Interactable);

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGoingActionCharacter : public ACharacter, public IHealth
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* UIMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraLockAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* OpenPlayerMenuAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

public:
	AGoingActionCharacter();

	UFUNCTION(BlueprintCallable)
	void SaveGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable)
	void LoadGameData(const FString& SlotName);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UInventoryComponent* Inventory = nullptr;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void OpenPickupStashWidget(const TMap<UItemAsset*, int>& Items);

	// Dynamic Event
	UPROPERTY(BlueprintAssignable)
	FInteractableChanged OnInteractableChanged;

	// IHealth
	virtual void GetHit_Implementation(float Damage, FVector HitLocation) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHealth = 100.f;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	float Health = 100.f;

	UFUNCTION()
	void Die();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void TryLockCamera(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	ABaseInteractableActor* InteractableInFront = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float InteractionDistance = 320.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
	float MinInteractionDot = 0.2f;

	void FindInteractableInFront();
private:
	UPROPERTY(BlueprintReadWrite, Category = "Camera Lock", meta = (AllowPrivateAccess = "true"))
	AActor* CurrentlyLocked = nullptr;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

