// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/Health.h"
#include "Interfaces/SaveLoad.h"
#include "Utility/Prerequisites.h"
#include "GoingActionCharacter.generated.h"

//UENUM(Blueprintable, BlueprintType)
//enum class FInputMode : uint8
//{
//	Game = 0 UMETA(DisplayName = "Game Only"),
//	UI = 1 UMETA(DisplayName = "UI Only")
//};

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UInventoryComponent;
class ABaseInteractableActor;
class AItemPickupActor;
class UUserWidget;
class USaveInstance;
class AWeapon;

enum class FWeaponType : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableChanged, TScriptInterface<IInteractable>, Interactable);

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AGoingActionCharacter : public ACharacter, public IHealth, public ISaveLoad
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleWalkAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleSteelWeaponAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleSilverWeaponAction;


	// Anim Montages
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* SheatheWeaponMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Animations", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* UnSheatheWeaponMontage;

public:
	AGoingActionCharacter();

	UFUNCTION(BlueprintCallable)
	void SaveGame(const FString& SlotName);

	UFUNCTION(BlueprintCallable)
	void LoadGameData(const FString& SlotName);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UInventoryComponent* Inventory = nullptr;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Character")
	void OpenPickupStashWidget(const TMap<UItemAsset*, int>& Items, AItemPickupActor* PickupActor);

	UFUNCTION(BlueprintCallable, Category = "Character")
	void FindInteractableInFront();

	UFUNCTION(BlueprintCallable, Category = "Character Equipment")
	void EquipWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance);

	UFUNCTION(BlueprintCallable, Category = "Character Equipment")
	void EquipArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket);

	UFUNCTION(BlueprintCallable, Category = "Character Equipment")
	void EatFood(UFoodAsset* FoodAsset, UItem* ItemInstance);

	// Dynamic Event
	UPROPERTY(BlueprintAssignable)
	FInteractableChanged OnInteractableChanged;

	// IHealth
	virtual void GetHit(float Damage, FVector HitLocation) override;
	virtual ELoyalty GetLoyalty() { return ELoyalty::Friendly; }
	virtual FVector GetInterfaceLocation() { return GetActorLocation(); }
	virtual bool TakeTokens(int Tokens) override;
	virtual void ReturnTokens(int Tokens) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
	float MaxHealth = 100.f;

	// ISaveLoad
	virtual void SaveState(USaveInstance* SaveInstance) override;
	virtual void LoadState(USaveInstance* SaveInstance) override;
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character")
	float Health = 100.f;

	UFUNCTION()
	void Die();

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Attack(const FInputActionValue& Value);

	void TryLockCamera(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void Sprint(const FInputActionValue& Value);

	void ToggleWalk(const FInputActionValue& Value);

	void ToggleSteelSheatheWeapon(const FInputActionValue& Value);
	void ToggleSilverSheatheWeapon(const FInputActionValue& Value);

protected:
	UFUNCTION()
	void OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void BeginPlay();
	virtual void Tick(float DeltaTime);

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	TArray<IInteractable*> OverlappingInteractables;

	UFUNCTION()
	void UpdateStats();

	IInteractable* InteractableInFront = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character")
	float InteractionDistance = 320.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character", meta = (ClampMin = "-1.0", ClampMax = "1.0", UIMin = "-1.0", UIMax = "1.0"))
	float MinInteractionDot = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	int AttackTokens = 1;

	// Movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
	float WalkSpeed = 300.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
	float JogSpeed = 600.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement")
	float SprintSpeed = 800.f;
	
	UPROPERTY()
	float CurrentSpeed = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Movement")
	bool IsWalking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Character Movement")
	bool IsSprinting = false;

	void UpdateSpeed();

	// Combat
	UPROPERTY(BlueprintReadWrite, Category = "Character Combat")
	AWeapon* SheathedWeapon = nullptr;
	
	UPROPERTY(BlueprintReadWrite, Category = "Character Combat")
	AWeapon* CurrentSteelWeapon = nullptr;
	
	UPROPERTY(BlueprintReadWrite, Category = "Character Combat")
	AWeapon* CurrentSilverWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Combat")
	FAttackMontageData FistAttackMontage;

	UFUNCTION()
	void AttackComboMontage(UAnimInstance* AnimInstance, UAnimMontage* AttackMontage, int MaxCombo);

	UPROPERTY()
	bool bIsSheathing = false;

	bool bIsComboAllowed = false;
	int CurrentAttackCombo = 0;

	void ToggleSheatheWeapon(FWeaponType WeaponType);
	void AllowAttackCombo();
private:

	UPROPERTY(BlueprintReadWrite, Category = "Camera Lock", meta = (AllowPrivateAccess = "true"))
	AActor* CurrentlyLocked = nullptr;

	APlayerController* PlayerController = nullptr;
	UCharacterMovementComponent* CharacterMovement = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Character Stats", meta = (AllowPrivateAccess = "true"))
	float Defense = 0.f;
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

