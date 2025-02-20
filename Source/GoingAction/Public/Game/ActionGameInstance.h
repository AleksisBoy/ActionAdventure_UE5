// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/SaveLoad.h"
#include "ActionGameInstance.generated.h"

class ADialogueManager;
class USaveInstance;

UCLASS()
class GOINGACTION_API UActionGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	ADialogueManager* GetDialogueManager();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDialogueWidgetController> DialogueWidgetClass;


	void AssignToSaving(ISaveLoad* Instance, bool LoadStateOnAssign);

	UPROPERTY(EditDefaultsOnly)
	FString SaveSlot = TEXT("TestSlot01");

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

protected:
	virtual void Init() override;

private:

	USaveInstance* CreateSaveInstance();

	ADialogueManager* DialogueManagerInstance = nullptr;

	UPROPERTY()
	USaveInstance* CurrentSave = nullptr;
	
	UPROPERTY()
	TArray<ISaveLoad*> InstancesToSave;

public:
	FORCEINLINE USaveInstance* GetCurrentSave() const { return CurrentSave; }
};
