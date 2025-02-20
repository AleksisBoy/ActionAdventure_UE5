// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DialogueManager.h"
#include "Camera/CameraComponent.h"
#include "DialogueNodeInfo.h"
#include "DialogueImpactNodeInfo.h"
#include "DialogueReturnNodeInfo.h"
#include "Game/ActionGameInstance.h"	
#include "UI/DialogueWidgetController.h"
#include "Blueprint/UserWidget.h"
#include "Components/AudioComponent.h"
#include "Actors/NonPlayableCharacter.h"
#include "Utility/SaveInstance.h"
#include "GoingAction/GoingActionCharacter.h"
#include "Components/InventoryComponent.h"
#include "Utility/FactSystem.h"

ADialogueManager::ADialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DialogueCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DialogueCamera"));
	DialogueCamera->SetupAttachment(RootComponent); 
	DialogueCamera->bUsePawnControlRotation = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = false;
}

void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogueManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsSpeaking) return;

	SpeakingTime += DeltaTime;
	if (SpeakingTime >= CurrentDialogueDuration)
	{
		OnFinishedSpeaking();
	}
}

void ADialogueManager::PlayDialogue(UDialogueAsset* DialogueAsset, AGoingActionCharacter* PlayerCharacter, ANonPlayableCharacter* TalkingNPC)
{
	UActionGameInstance* GameInstance = Cast<UActionGameInstance>(GetGameInstance());
	if (!GameInstance) return;
	if (DialogueAsset == nullptr) return;

	SpeakingTime = 0.f;
	CurrentDialogue = DialogueAsset;
	CachedPlayerCharacter = PlayerCharacter;
	CachedTalkingNPC = TalkingNPC;
	for (UDialogueRuntimeNode* Node : CurrentDialogue->Graph->Nodes)
	{
		if (Node->NodeType == EDialogueNodeType::Start)
		{
			CurrentNode = Node;
			break;
		}
	}
	if (CurrentNode == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NO START NODE IN DIALOGUE ASSET"));
		return;
	}
	AudioComponent->SetWorldLocation(PlayerCharacter->GetActorLocation());

	APlayerController* PlayerController = (APlayerController*)PlayerCharacter->GetController();

	// Create and display dialogue ui
	if (CurrentDialogueUI == nullptr)
	{
		CurrentDialogueUI = CreateWidget<UDialogueWidgetController>(PlayerController, GameInstance->DialogueWidgetClass);
	}
	CurrentDialogueUI->AddToViewport();

	// Set player input mode UI
	FInputModeUIOnly InputMode;
	InputMode.SetWidgetToFocus(CurrentDialogueUI->GetCachedWidget());

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;

	// Choose first response by default beginning from start node
	ChooseResponseIndex(0);
}

void ADialogueManager::ChooseResponseIndex(int Index)
{
	if (Index >= CurrentNode->OutputPins.Num() || Index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid response at index %d"), Index);
		return;
	}

	// Store chosen Dialogue response as already heard
	// ...

	UDialogueRuntimePin* OutputPin = CurrentNode->OutputPins[Index];
	if (OutputPin->Connection != nullptr)
	{
		CurrentNode = OutputPin->Connection->Parent;
	}
	else
	{
		CurrentNode = nullptr;
	}

	if (CurrentNode == nullptr) return; // end?

	// Next Node is Dialogue (set text, and play audio)
	if (CurrentNode->NodeType == EDialogueNodeType::Dialogue)
	{
		CurrentDialogueInfo = Cast<UDialogueNodeInfo>(CurrentNode->NodeInfo);
		CurrentDialogueUI->SetDialogue(CurrentDialogueInfo->GetSpeakerDialogue(), this);
		CurrentDialogueDuration = CurrentDialogueInfo->GetRealDuration();
		if (CurrentDialogueInfo->DialogueAudio)
		{
			AudioComponent->Sound = CurrentDialogueInfo->DialogueAudio;
			AudioComponent->Play();
		}
		// Set dialogue ui text to dialogue text
		IsSpeaking = true;
		CurrentDialogueUI->ClearResponses();
	}
	// Next node is Return (Circle back to previous Dialogue Nodes)
	else if (CurrentNode->NodeType == EDialogueNodeType::Return)
	{
		UDialogueReturnNodeInfo* ReturnInfo = Cast<UDialogueReturnNodeInfo>(CurrentNode->NodeInfo);
		UDialogueRuntimeNode* ReturnalNode = CurrentNode;
		int StepsBack = 0;

		// Find previous dialogue node by StepsBack
		while (StepsBack < ReturnInfo->StepsBack)
		{
			ReturnalNode = ReturnalNode->InputPin->Connection->Parent;
			if (!ReturnalNode)
			{
				UE_LOG(LogTemp, Error, TEXT("RETURN NODE DOES NOT POINT BACK CORRECTLY IN %s"), *CurrentDialogue->GetName());
				return;
			}
			if (ReturnalNode->NodeType != EDialogueNodeType::Dialogue) continue;

			if (ReturnalNode->OutputPins.Num() > 1)
			{
				StepsBack++;
			}
		}
		CurrentDialogueInfo = Cast<UDialogueNodeInfo>(ReturnalNode->NodeInfo);
		CurrentNode = ReturnalNode;
		CurrentDialogueUI->UpdateResponses(CurrentDialogueInfo->DialogueResponses);
		//CurrentDialogueInfo = nullptr; //???
	}
	// Next Node is Impact (Give player items, update facts, update quests, and continue instantly)
	else if (CurrentNode->NodeType == EDialogueNodeType::Impact)
	{
		// Add items
		UDialogueImpactNodeInfo* ImpactInfo = Cast<UDialogueImpactNodeInfo>(CurrentNode->NodeInfo);
		for (FItemImpact& ItemImpact : ImpactInfo->ItemImpacts)
		{
			CachedPlayerCharacter->Inventory->TryAddItem(ItemImpact.Item, ItemImpact.Amount);
			// item added ui popup? or have it made in inventory events
		}

		// Update facts
		UFactSystem* FactSystem = GetGameInstance()->GetSubsystem<UFactSystem>();
		if (FactSystem)
		{
			for (FFactImpact& FactImpact : ImpactInfo->FactImpacts)
			{
				FactSystem->UpdateFact(FactImpact.Fact, FactImpact.Value);
			}
		}
		
		// Update Quests
		// ...

		// Continue
		ChooseResponseIndex(0);
	}
	// Next Node is End (Quit Dialogue)
	else if (CurrentNode->NodeType == EDialogueNodeType::End)
	{
		CurrentDialogueUI->ClearResponses();
		CurrentDialogueUI->RemoveFromParent();
		CurrentDialogue = nullptr;
		CurrentDialogueInfo = nullptr;

		CachedTalkingNPC->QuitDialogue();

		// Set player input mode game
		FInputModeGameOnly InputMode;

		APlayerController* PlayerController = (APlayerController*)CachedPlayerCharacter->GetController();
		PlayerController->SetInputMode(InputMode);
		PlayerController->bShowMouseCursor = false;
	}
}

void ADialogueManager::SkipDialogue()
{
	// Skip only when speaking
	if (!IsSpeaking) return;

	OnFinishedSpeaking();
}

void ADialogueManager::OnFinishedSpeaking()
{
	AudioComponent->Stop();
	IsSpeaking = false;
	SpeakingTime = 0.f;
	// Set UI responses boxes if current node is dialogue

	// If one response -> continue speaking
	if (CurrentDialogueInfo->DialogueResponses.Num() == 1)
	{
		ChooseResponseIndex(0);
		return;
	}
	CurrentDialogueUI->UpdateResponses(CurrentDialogueInfo->DialogueResponses);
}
