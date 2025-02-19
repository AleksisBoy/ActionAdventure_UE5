// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueWidgetController.h"
#include "Components/TextBlock.h"
#include "DialogueNodeInfo.h"
#include "UI/DialogueResponseButtonController.h"
#include "Components/VerticalBox.h"
#include "Utility/FactSystem.h"

void UDialogueWidgetController::SetDialogue(FText Text)
{
	UE_LOG(LogTemp, Warning, TEXT("SET DIALGOEU"));
	DialogueText->SetText(Text);
}

void UDialogueWidgetController::SelectResponseIndex(int Index)
{
}

void UDialogueWidgetController::UpdateResponses(TArray<FDialogueResponse> Responses)
{
	UFactSystem* FactSystem = GetGameInstance()->GetSubsystem<UFactSystem>();
	if (!FactSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("FACT SYSTEM DOES NOT EXIST FOR DIALOGUE WIDGET"));
		return;
	}

	ResponsesBox->ClearChildren();
	for (int i = 0; i < Responses.Num(); i++)
	{
		if (!FactSystem->CheckFact(Responses[i].Fact)) continue;

		UDialogueResponseButtonController* ResponseButton = CreateWidget<UDialogueResponseButtonController>(this, ResponseButtonClass);
		ResponseButton->SetResponse(this, Responses[i].Text, i);
		ResponsesBox->AddChild(ResponseButton);
	}
}
