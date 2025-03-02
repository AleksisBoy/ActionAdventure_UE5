// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ActionGameInstance.h"
#include "Actors/DialogueManager.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/SaveInstance.h"

ADialogueManager* UActionGameInstance::GetDialogueManager()
{
	if (DialogueManagerInstance != nullptr) return DialogueManagerInstance;
	if (!GetWorld()) return nullptr;

	DialogueManagerInstance = GetWorld()->SpawnActor<ADialogueManager>();
	return DialogueManagerInstance;
}

void UActionGameInstance::AssignToSaving(TScriptInterface<ISaveLoad> Instance, bool LoadStateOnAssign)
{
	if (Instance == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("INSTANCE IS NULL THE ONE U TRY TO SET WTF"));
		return;
	}
	InstancesToSave.AddUnique(Instance);
	if (LoadStateOnAssign && CurrentSave)
	{
		Instance->LoadState(CurrentSave);
	}
}

void UActionGameInstance::Init()
{
	Super::Init();

}

void UActionGameInstance::SaveGame()
{
	UE_LOG(LogTemp, Warning, TEXT("SAVING GAME"));
	if (!CurrentSave) CurrentSave = CreateSaveInstance();

	for (TScriptInterface<ISaveLoad> Instance : InstancesToSave)
	{
		UE_LOG(LogTemp, Warning, TEXT("SAVING INSTANCE %s"), *Instance->_getUObject()->GetName());
		if (Instance == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("NULL INSTANCE TO LOAD"));
			continue;
		}
		
		Instance->SaveState(CurrentSave);
	}
	UGameplayStatics::SaveGameToSlot(CurrentSave, SaveSlot, 0);
	UE_LOG(LogTemp, Warning, TEXT("SAVING GAME TO SLOT"));
}

void UActionGameInstance::LoadGame()
{
	UE_LOG(LogTemp, Warning, TEXT("LOAD GAME"));
	if (UGameplayStatics::DoesSaveGameExist(SaveSlot, 0))
	{
		UE_LOG(LogTemp, Warning, TEXT("FOUND SAVE GAME"));
		CurrentSave = Cast<USaveInstance>(UGameplayStatics::LoadGameFromSlot(SaveSlot, 0));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("CREATING SAVE GAME"));
		CurrentSave = CreateSaveInstance();
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("LOOPING THROUGH SAVE INSTANCES"));
	for (TScriptInterface<ISaveLoad> Instance : InstancesToSave)
	{
		Instance->LoadState(CurrentSave);
	}
}

USaveInstance* UActionGameInstance::CreateSaveInstance()
{
	return Cast<USaveInstance>(UGameplayStatics::CreateSaveGameObject(USaveInstance::StaticClass()));;
}
