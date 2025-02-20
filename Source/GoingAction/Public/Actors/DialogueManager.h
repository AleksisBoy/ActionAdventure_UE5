// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogueAsset.h"
#include "DialogueManager.generated.h"

class UCameraComponent;
class UDialogueWidgetController;
class UDialogueNodeInfo;
class UAudioComponent;
class ANonPlayableCharacter;

UCLASS()
class GOINGACTION_API ADialogueManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ADialogueManager();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void PlayDialogue(UDialogueAsset* DialogueAsset, APlayerController* PlayerController, ANonPlayableCharacter* talkingNPC);
	void ChooseResponseIndex(int Index);

	void SkipDialogue();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* DialogueCamera = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Audio")
	UAudioComponent* AudioComponent;

	void OnFinishedSpeaking();
private:
	UPROPERTY()
	UDialogueAsset* CurrentDialogue = nullptr;

	UPROPERTY()
	UDialogueRuntimeNode* CurrentNode = nullptr;

	UPROPERTY()
	UDialogueWidgetController* CurrentDialogueUI = nullptr;

	UPROPERTY()
	bool IsSpeaking = false;

	float SpeakingTime = 0.f;
	float CurrentDialogueDuration = 0.f;

	ANonPlayableCharacter* TalkingNPC = nullptr;
	UDialogueNodeInfo* CurrentDialogueInfo = nullptr;
	APlayerController* CachedPlayerController = nullptr;
};
