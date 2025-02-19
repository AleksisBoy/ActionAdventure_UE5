// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ActionGameInstance.h"
#include "Actors/DialogueManager.h"

ADialogueManager* UActionGameInstance::GetDialogueManager()
{
	if (DialogueManagerInstance != nullptr) return DialogueManagerInstance;
	if (!GetWorld()) return nullptr;

	DialogueManagerInstance = GetWorld()->SpawnActor<ADialogueManager>();
	return DialogueManagerInstance;
}
