// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueResponseButtonController.generated.h"

class UButton;
class UTextBlock;
class UDialogueWidgetController;

UCLASS()
class GOINGACTION_API UDialogueResponseButtonController : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void SetResponse(UDialogueWidgetController* dialogueController, FText Text, int Index);

protected:
	virtual bool Initialize() override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* ResponseButton = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* ResponseText;

private:

	UPROPERTY()
	int ResponseIndex = -1;

	UFUNCTION()
	void OnResponseClicked();

	UDialogueWidgetController* DialogueController;
};
