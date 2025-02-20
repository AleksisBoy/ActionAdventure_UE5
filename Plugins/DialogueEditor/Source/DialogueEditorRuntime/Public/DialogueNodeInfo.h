#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include <GoingAction/Public/Utility/Fact.h>
#include "DialogueNodeInfo.generated.h"

USTRUCT(BlueprintType)
struct FDialogueResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText Text = FText::FromString(TEXT("Continue"));

	UPROPERTY(EditAnywhere)
	EFact Fact = EFact::DEFAULT_TRUE;

	UPROPERTY(EditAnywhere)
	bool FactIsTrue = true;

	UPROPERTY(EditAnywhere)
	bool Repetative = false;

	FDialogueResponse()
	{
		Text = FText::FromString(TEXT("Continue"));
		Fact = EFact::DEFAULT_TRUE;
	}
	FDialogueResponse(const FText& InText)
	{
		Text = InText;
		Fact = EFact::DEFAULT_TRUE;
	}
	FDialogueResponse(EFact InFact, const FText& InText)
	{
		Fact = InFact;
		Text = InText;
	}
};

UCLASS(BlueprintType)
class DIALOGUEEDITORRUNTIME_API UDialogueNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FText Title;

	UPROPERTY(EditAnywhere)
	FText Speaker;

	UPROPERTY(EditAnywhere, meta = (MultiLine = "true"))
	FText DialogueText;

	UPROPERTY(EditAnywhere)
	USoundBase* DialogueAudio;
	
	UPROPERTY(EditAnywhere)
	float Duration;

	UPROPERTY(EditAnywhere)
	TArray<FDialogueResponse> DialogueResponses;

	FText GetSpeakerDialogue()
	{
		return FText::Join(FText::FromString(": "), Speaker, DialogueText);
	}

	// Get the duration of the node, picks audio duration as top priority
	float GetRealDuration()
	{
		if (DialogueAudio)
		{
			return DialogueAudio->Duration;
		}
		return Duration;
	}
};
