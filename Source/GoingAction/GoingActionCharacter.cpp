// Copyright Epic Games, Inc. All Rights Reserved.

#include "GoingActionCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Enemy.h"
#include "Components/InventoryComponent.h"
#include "Utility/SaveInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/BaseInteractableActor.h"
#include "Blueprint/UserWidget.h"
#include "Framework/Application/SlateApplication.h"
#include "Framework/Application/NavigationConfig.h"
#include <Data/FoodAsset.h>
#include "Interfaces/Interactable.h"
#include "AI/CombatSubsystem.h"
#include "Game/ActionGameInstance.h"
#include "Weapons/Weapon.h"
#include "Data/WeaponAsset.h"


DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGoingActionCharacter

AGoingActionCharacter::AGoingActionCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
}

void AGoingActionCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Save/Load Interface
	UE_LOG(LogTemp, Warning, TEXT("TRYING TO ASSIGN SAVE CHARACTER"));
	if (UActionGameInstance* GameInstance = GetGameInstance<UActionGameInstance>())
	{
		UE_LOG(LogTemp, Warning, TEXT("ASSIGNING TO SAVE CHARACTER"));
		GameInstance->AssignToSaving(this, true);
	}
	UE_LOG(LogTemp, Warning, TEXT("CONTINUE CHARACTER"));

	// DEBUG Combat 
	if (UCombatSubsystem* CombatSub = GetWorld()->GetSubsystem<UCombatSubsystem>())
	{
		CombatSub->StartCombat(this);
	}

	// Movement Speed
	CharacterMovement = GetComponentByClass<UCharacterMovementComponent>();
	if (CharacterMovement)
	{
		UpdateSpeed();
	}

	// Combat
	if (UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance())
	{
		AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this, &AGoingActionCharacter::OnMontageNotifyBegin);
	}

	// Turn off UI Tab and Key navigation
	FNavigationConfig& NavigationConfig = *FSlateApplication::Get().GetNavigationConfig();

	NavigationConfig.bTabNavigation = false;
	NavigationConfig.bKeyNavigation = false;

	// Health
	Health = MaxHealth;

	// Inventory 
	Inventory->OnEquipmentChanged.AddDynamic(this, &AGoingActionCharacter::UpdateStats);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AGoingActionCharacter::OnOverlapBegin);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &AGoingActionCharacter::OnOverlapEnd);
}
void AGoingActionCharacter::OnMontageNotifyBegin(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName == "AllowAttackCombo")
	{
		AllowAttackCombo();
	}
}
void AGoingActionCharacter::GetHit(float Damage, FVector HitLocation)
{
	Health -= Damage;
	if (Health <= 0.f)
	{
		Die();
	}
	OnPlayerHealthChanged.Broadcast(Health, MaxHealth);
}
void AGoingActionCharacter::HealPrecise(float HealHealth)
{
	Health = FMath::Clamp(Health + HealHealth, 0, MaxHealth);
	OnPlayerHealthChanged.Broadcast(Health, MaxHealth);
}
void AGoingActionCharacter::HealPerc(float Perc)
{
	Health = FMath::Clamp(Health + MaxHealth * Perc, 0, MaxHealth);
	OnPlayerHealthChanged.Broadcast(Health, MaxHealth);
}
bool AGoingActionCharacter::TakeTokens(int Tokens)
{
	if (AttackTokens < Tokens) return false;

	AttackTokens -= Tokens;
	return true;
}

void AGoingActionCharacter::ReturnTokens(int Tokens)
{
	AttackTokens += Tokens;
}

// Save/Load Interface ->
void AGoingActionCharacter::SaveState(USaveInstance* SaveInstance)
{
	UE_LOG(LogTemp, Warning, TEXT("SAVING INSIDE CHARACTER"));
	SaveInstance->AssignInventory(Inventory->GetItems());
	SaveInstance->Health = Health;
}

void AGoingActionCharacter::LoadState(USaveInstance* SaveInstance)
{
	if (SaveInstance == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("LOADING STATE CHARACTER"));
	Inventory->Load(SaveInstance->LoadInventory());
	Health = SaveInstance->Health;
}
// Save/Load Interface <-

void AGoingActionCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("PLAYER DIED"));
}

void AGoingActionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGoingActionCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IInteractable* InteractableOverlapped = Cast<IInteractable>(OtherActor))
	{
		OverlappingInteractables.AddUnique(InteractableOverlapped);
	}
}

void AGoingActionCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IInteractable* InteractableOverlapped = Cast<IInteractable>(OtherActor))
	{
		OverlappingInteractables.Remove(InteractableOverlapped);
	}
}

void AGoingActionCharacter::UpdateStats()
{
	Defense = Inventory->GetEquippedArmorDefense();
}

void AGoingActionCharacter::UpdateSpeed()
{
	if (IsSprinting) CurrentSpeed = SprintSpeed;
	else CurrentSpeed = IsWalking ? WalkSpeed : JogSpeed;

	CharacterMovement->MaxWalkSpeed = CurrentSpeed;
}

void AGoingActionCharacter::ToggleSheatheWeapon(FWeaponType WeaponType)
{
	if (bIsSheathing) return;

	CurrentAttackCombo = 0;

	if (SheathedWeapon)
	{
		// play unsheathe animation first and continue it with sheating
		UE_LOG(LogTemp, Warning, TEXT("UnSheathed weapon"));
		SheathedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("scabbard")));
		SheathedWeapon->Dequip();

		if (SheathedWeapon->GetData()->WeaponType == WeaponType)
		{
			PlayAnimMontage(UnSheatheWeaponMontage);
			SheathedWeapon = nullptr;
			return;
		}
		SheathedWeapon = nullptr;
	}
	
	// play sheathe animation
	SheathedWeapon = WeaponType == FWeaponType::Steel ? CurrentSteelWeapon : CurrentSilverWeapon;
	if (!SheathedWeapon) return;

	PlayAnimMontage(SheatheWeaponMontage);
	SheathedWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("weapon_r")));
	SheathedWeapon->Equip();
	UE_LOG(LogTemp, Warning, TEXT("Sheathed weapon"));
}

void AGoingActionCharacter::AllowAttackCombo()
{
	UE_LOG(LogTemp, Warning, TEXT("Allowed combo"));
	bIsComboAllowed = true;
}

void AGoingActionCharacter::FindInteractableInFront()
{
	float MaximumDot = -1.f;
	IInteractable* NewInteractableInFront = nullptr;

	for (IInteractable* Interactable : OverlappingInteractables)
	{
		if (!Interactable->IsAbleToInteract()) continue;

		//FVector Direction = Actor->GetActorLocation() - FollowCamera->GetComponentLocation();
		FVector Direction = Interactable->GetInterfaceLocation() - GetActorLocation();
		
		// Check if Actor is in range of Interaction Distance
		float Distance = Direction.Length();
		if (Distance > InteractionDistance) continue;

		Direction.Normalize();
		//float Dot = FVector::DotProduct(FollowCamera->GetForwardVector(), Direction); 
		float Dot = FVector::DotProduct(this->GetActorForwardVector(), Direction); 
		if (Dot < MinInteractionDot) continue;

		if (Dot > MaximumDot)
		{
			MaximumDot = Dot;
			NewInteractableInFront = Interactable;
		}
	}
	if (InteractableInFront != NewInteractableInFront)
	{
		InteractableInFront = NewInteractableInFront;
		if (InteractableInFront)
		{
			OnInteractableChanged.Broadcast(InteractableInFront->_getUObject());
		}
		else
		{
			OnInteractableChanged.Broadcast(nullptr);
		}
	}
}

void AGoingActionCharacter::EquipWeapon(UWeaponAsset* WeaponAsset, UItem* ItemInstance)
{
	if (WeaponAsset == nullptr) return;

	if (WeaponAsset->WeaponType == FWeaponType::Steel)
	{
		if (CurrentSteelWeapon)
		{
			// Dont destroy but change its mesh, etc?
			if (!CurrentSteelWeapon->TrySetData(WeaponAsset)) CurrentSteelWeapon->Destroy();
			else
			{
				CurrentSteelWeapon = (AWeapon*)GetWorld()->SpawnActor(WeaponAsset->WeaponActorClass);
				CurrentSteelWeapon->TrySetData(WeaponAsset);
				CurrentSteelWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("scabbard")));
				CurrentSteelWeapon->Dequip();
			}
		}
		else
		{
			CurrentSteelWeapon = (AWeapon*)GetWorld()->SpawnActor(WeaponAsset->WeaponActorClass);
			CurrentSteelWeapon->TrySetData(WeaponAsset); 
			CurrentSteelWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("scabbard")));
			CurrentSteelWeapon->Dequip();
		}
	}
	Inventory->EquipWeapon(WeaponAsset, ItemInstance);
}

void AGoingActionCharacter::EquipArmor(UArmorAsset* ArmorAsset, UItem* ItemInstance, EArmorSocket ArmorSocket)
{
	Inventory->EquipArmor(ArmorAsset, ItemInstance, ArmorSocket);
}

void AGoingActionCharacter::EatFood(UFoodAsset* FoodAsset, UItem* ItemInstance)
{
	if (Inventory->TryRemoveItem(ItemInstance, 1))
	{
		HealPrecise(FoodAsset->HealDuration * FoodAsset->HealingPerSec);
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGoingActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	UE_LOG(LogTemp, Warning, TEXT("SETUP PLAYER INPUT"));

	PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		/*EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);*/

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::Look);

		EnhancedInputComponent->BindAction(CameraLockAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::TryLockCamera);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::Interact);
	
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::Sprint);
		EnhancedInputComponent->BindAction(ToggleWalkAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::ToggleWalk);
	
		// Combat
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::Attack);
		EnhancedInputComponent->BindAction(ToggleSteelWeaponAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::ToggleSteelSheatheWeapon);
		EnhancedInputComponent->BindAction(ToggleSilverWeaponAction, ETriggerEvent::Triggered, this, &AGoingActionCharacter::ToggleSilverSheatheWeapon);
		
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AGoingActionCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);

		FindInteractableInFront();
	}
}

void AGoingActionCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGoingActionCharacter::Attack(const FInputActionValue& Value)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (!AnimInstance) return;

	if (SheathedWeapon && SheathedWeapon->GetAttackAnimations().Num() != 0)
	{
		FAttackMontageData AttackMontageData = SheathedWeapon->GetAttackAnimations()[0];
		AttackComboMontage(AnimInstance, AttackMontageData.Montage, AttackMontageData.Amount);

		/*if (!GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage))
		{
			CurrentAttackCombo = 0;
			bIsComboAllowed = false;

			AnimInstance->Montage_Play(AttackMontage);
			AnimInstance->Montage_JumpToSection(FName("Attack0"), AttackMontage);
			//PlayAnimMontage(AttackMontage, 1.f, FName(TEXT("Attack0")));
		}
		else if (bIsComboAllowed)
		{
			bIsComboAllowed = false;
			CurrentAttackCombo++;

			if (CurrentAttackCombo == 1)
			{
				AnimInstance->Montage_SetNextSection(FName("Attack0"), FName("Attack1"), AttackMontage);
				//PlayAnimMontage(AttackMontage, 1.f, FName(TEXT("Attack1")));
			}
			else if (CurrentAttackCombo == 2)
			{
				AnimInstance->Montage_SetNextSection(FName("Attack1"), FName("Attack2"), AttackMontage);
				//PlayAnimMontage(AttackMontage, 1.f, FName(TEXT("Attack2")));
			}
			else
			{
				AnimInstance->Montage_Play(AttackMontage);
				//PlayAnimMontage(AttackMontage, 1.f, FName(TEXT("Attack0")));
				CurrentAttackCombo = 0;
			}

		}
		*/
		//PlayAnimMontage(SheathedWeapon->GetAttackAnimations()[0]);
		UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentAttackCombo);
	}
	// fistfight
	else
	{
		AttackComboMontage(AnimInstance, FistAttackMontage.Montage, FistAttackMontage.Amount);
		UE_LOG(LogTemp, Warning, TEXT("Player Attacked with fists"));
	}
}

void AGoingActionCharacter::AttackComboMontage(UAnimInstance* AnimInstance, UAnimMontage* AttackMontage, int MaxCombo)
{
	if (AttackMontage == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("NULL PTR"));
	}
	if (!AnimInstance->Montage_IsPlaying(AttackMontage))
	{
		CurrentAttackCombo = 0;
		bIsComboAllowed = false;

		AnimInstance->Montage_Play(AttackMontage);
		AnimInstance->Montage_JumpToSection(FName("Attack0"), AttackMontage);
	}
	else if (bIsComboAllowed)
	{
		bIsComboAllowed = false;
		CurrentAttackCombo++;

		if (CurrentAttackCombo >= MaxCombo)
		{
			AnimInstance->Montage_Play(AttackMontage);
			CurrentAttackCombo = 0;
			return;
		}

		FName CurrentSection = FName(*FString::Printf(TEXT("Attack%d"), CurrentAttackCombo - 1));
		FName NextSection = FName(*FString::Printf(TEXT("Attack%d"), CurrentAttackCombo));

		UE_LOG(LogTemp, Warning, TEXT("%d"), CurrentAttackCombo);

		AnimInstance->Montage_SetNextSection(CurrentSection, NextSection, AttackMontage);
	}
}

void AGoingActionCharacter::TryLockCamera(const FInputActionValue& Value)
{
	if (CurrentlyLocked)
	{
		CurrentlyLocked = nullptr;
		CameraBoom->bUsePawnControlRotation = true;
		return;
	}
	if (!GetWorld()) return;

	float MaximumDot = -1.f;
	AActor* EnemyInFront = nullptr;
	for (AEnemy* Enemy : AEnemy::Active)
	{
		FVector DirectionToEnemy = Enemy->GetActorLocation() - FollowCamera->GetComponentLocation();
		DirectionToEnemy.Normalize();
		float Dot = FVector::DotProduct(FollowCamera->GetForwardVector(), DirectionToEnemy);
		if (Dot > MaximumDot)
		{
			MaximumDot = Dot;
			EnemyInFront = Enemy;
		}
	}
	if (EnemyInFront)
	{
		CurrentlyLocked = EnemyInFront;
		UE_LOG(LogTemp, Warning, TEXT("LOcked on %s"), *EnemyInFront->GetName());
		CameraBoom->bUsePawnControlRotation = false;
	}
	return;

	TArray<AActor*> ActorsToIgnore;
	TArray <FHitResult> Hits;

	UKismetSystemLibrary::BoxTraceMultiByProfile(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + FollowCamera->GetForwardVector() * 200.f,
		FVector(1000, 1000, 100),
		FollowCamera->GetComponentRotation(),
		FName("Pawn"),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForDuration,
		Hits,
		true
	);

	for (FHitResult Hit : Hits)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit name: %s"), *Hit.GetActor()->GetName())
	}
}

void AGoingActionCharacter::Interact(const FInputActionValue& Value)
{
	if (InteractableInFront)
	{
		InteractableInFront->Interact(this);
		FindInteractableInFront();
	}
}

void AGoingActionCharacter::Sprint(const FInputActionValue& Value)
{
	IsSprinting = !IsSprinting;
	UpdateSpeed();
}

void AGoingActionCharacter::ToggleWalk(const FInputActionValue& Value)
{
	IsWalking = !IsWalking;
	UpdateSpeed();
}

void AGoingActionCharacter::ToggleSteelSheatheWeapon(const FInputActionValue& Value)
{
	ToggleSheatheWeapon(FWeaponType::Steel);
}

void AGoingActionCharacter::ToggleSilverSheatheWeapon(const FInputActionValue& Value)
{
	ToggleSheatheWeapon(FWeaponType::Silver);
}


// Deprecated
void AGoingActionCharacter::SaveGame(const FString& SlotName)
{
	USaveInstance* SaveInstance = Cast<USaveInstance>(UGameplayStatics::CreateSaveGameObject(USaveInstance::StaticClass()));

	if (SaveInstance)
	{
		SaveInstance->AssignInventory(Inventory->GetItems());
		SaveInstance->Health = Health;

		UGameplayStatics::SaveGameToSlot(SaveInstance, SlotName, 0);
	}
}

// Deprecated
void AGoingActionCharacter::LoadGameData(const FString& SlotName)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		USaveInstance* LoadedGame = Cast<USaveInstance>(UGameplayStatics::LoadGameFromSlot(SlotName, 0));

		if (LoadedGame)
		{
			Health = LoadedGame->Health;
			Inventory->Load(LoadedGame->LoadInventory());
		}
	}
}
