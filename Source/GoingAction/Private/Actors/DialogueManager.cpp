// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/DialogueManager.h"
#include "Camera/CameraComponent.h"
#include "DialogueNodeInfo.h"
#include "Game/ActionGameInstance.h"	
#include "UI/DialogueWidgetController.h"
#include "Blueprint/UserWidget.h"

ADialogueManager::ADialogueManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DialogueCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("DialogueCamera"));
	DialogueCamera->SetupAttachment(RootComponent); 
	DialogueCamera->bUsePawnControlRotation = false;
}

void ADialogueManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADialogueManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADialogueManager::PlayDialogue(UDialogueAsset* DialogueAsset, APlayerController* PlayerController)
{
	UActionGameInstance* GameInstance = Cast<UActionGameInstance>(GetGameInstance());
	if (!GameInstance) return;
	if (DialogueAsset == nullptr) return;
	FInputModeUIOnly InputMode;
	// set dialogue ui
	//InputMode.SetWidgetToFocus()

	PlayerController->SetInputMode(InputMode);
	PlayerController->bShowMouseCursor = true;

	CurrentDialogue = DialogueAsset;
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
	// create and display dialogue ui
	CurrentDialogueUI = CreateWidget<UDialogueWidgetController>(PlayerController, GameInstance->DialogueWidgetClass);
	CurrentDialogueUI->AddToViewport();

	ChooseResponseIndex(0);
}

void ADialogueManager::ChooseResponseIndex(int Index)
{
	if (Index >= CurrentNode->OutputPins.Num() || Index < 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid response at index %d"), Index);
		return;
	}

	UDialogueRuntimePin* OutputPin = CurrentNode->OutputPins[Index];
	if (OutputPin->Connection != nullptr)
	{
		CurrentNode = OutputPin->Connection->Parent;
	}
	else
	{
		CurrentNode = nullptr;
	}

	if (CurrentNode != nullptr && CurrentNode->NodeType == EDialogueNodeType::Dialogue)
	{
		UDialogueNodeInfo* NodeInfo = Cast<UDialogueNodeInfo>(CurrentNode->NodeInfo);
		CurrentDialogueUI->SetDialogue(NodeInfo->GetSpeakerDialogue());
		// Set dialogue ui text to dialogue text

		// Set UI responses boxes
		CurrentDialogueUI->UpdateResponses(NodeInfo->DialogueResponses);
	}
}

void ADialogueManager::SkipDialogue()
{
}

