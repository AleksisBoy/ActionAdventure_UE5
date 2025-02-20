// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueResponseButtonController.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "UI/DialogueWidgetController.h"

void UDialogueResponseButtonController::SetResponse(UDialogueWidgetController* dialogueController, FText Text, int Index)
{
	this->DialogueController = dialogueController;
	ResponseText->SetText(Text);
	ResponseIndex = Index;
	//if (ResponseAlreadyHeard) ResponseText->SetColorAndOpacity(FLinearColor(0, 0, 0, 1));

	ResponseButton->OnClicked.AddDynamic(this, &UDialogueResponseButtonController::OnResponseClicked);
}

bool UDialogueResponseButtonController::Initialize()
{
	if (!Super::Initialize()) return false;

	if (!ResponseText || !ResponseButton) return false;

	return true;
}

void UDialogueResponseButtonController::OnResponseClicked()
{
	DialogueController->SelectResponseIndex(ResponseIndex);
}
