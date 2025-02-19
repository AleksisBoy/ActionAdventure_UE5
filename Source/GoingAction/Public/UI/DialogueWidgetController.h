// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidgetController.generated.h"
 
class UDialogueResponseButtonController;
class UTextBlock;
struct FDialogueResponse;
class UVerticalBox;

UCLASS()
class GOINGACTION_API UDialogueWidgetController : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetDialogue(FText Text);
	void SelectResponseIndex(int Index);

	void UpdateResponses(TArray<FDialogueResponse> Responses);
	bool TrySkipDialogue();

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UVerticalBox* ResponsesBox;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDialogueResponseButtonController> ResponseButtonClass;
private:

	bool IsSpeaking = false;

	TArray<UDialogueResponseButtonController*> CurrentResponseButtons;
};
