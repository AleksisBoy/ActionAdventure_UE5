// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NPCWidgetController.generated.h"
 
class UTextBlock;

UCLASS()
class GOINGACTION_API UNPCWidgetController : public UUserWidget
{
	GENERATED_BODY()
	
public:


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CharacterNameText = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* CharacterLevelText = nullptr;

	UFUNCTION(BlueprintImplementableEvent)
	void SetHealth(float Value, float MaxValue);

};
