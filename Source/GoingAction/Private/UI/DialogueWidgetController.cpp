// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueWidgetController.h"
#include "Components/TextBlock.h"
#include "DialogueNodeInfo.h"
#include "UI/DialogueResponseButtonController.h"
#include "Components/VerticalBox.h"
#include "Utility/FactSystem.h"
#include "Actors/DialogueManager.h"

void UDialogueWidgetController::SetDialogue(FText Text, ADialogueManager* Manager)
{
	DialogueText->SetText(Text);
	DialogueManager = Manager;
}

void UDialogueWidgetController::SelectResponseIndex(int Index)
{
	DialogueManager->ChooseResponseIndex(Index);
}

void UDialogueWidgetController::UpdateResponses(TArray<FDialogueResponse> Responses)
{
	UFactSystem* FactSystem = GetGameInstance()->GetSubsystem<UFactSystem>();
	if (!FactSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("FACT SYSTEM DOES NOT EXIST FOR DIALOGUE WIDGET"));
		return;
	}

	ClearResponses();
	for (int i = 0; i < Responses.Num(); i++)
	{
		if (!FactSystem->CheckFact(Responses[i].Fact)) continue;
		//bool ResponseAlreadyHeard = StoredResponsesMap.Contains(i) ? StoredResponsesMap[i] : false;
		//if (!Responses[i].Repetative && ResponseAlreadyHeard) continue;


		UDialogueResponseButtonController* ResponseButton = CreateWidget<UDialogueResponseButtonController>(this, ResponseButtonClass);
		ResponseButton->SetResponse(this, Responses[i].Text, i);
		ResponsesBox->AddChild(ResponseButton);
	}
}

void UDialogueWidgetController::ClearResponses()
{
	ResponsesBox->ClearChildren();
	CollectGarbage(EObjectFlags::RF_NoFlags);
}

bool UDialogueWidgetController::TrySkipDialogue()
{
	if (!DialogueManager) return false;

	DialogueManager->SkipDialogue();
	return true;
}
