// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ActionGameInstance.generated.h"

class ADialogueManager;

UCLASS()
class GOINGACTION_API UActionGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	ADialogueManager* GetDialogueManager();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDialogueWidgetController> DialogueWidgetClass;
private:
	ADialogueManager* DialogueManagerInstance = nullptr;
};
