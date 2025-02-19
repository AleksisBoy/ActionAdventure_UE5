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

	}
	FDialogueResponse(const FText& InText) : Text(InText)
	{
	}
	FDialogueResponse(EFact InFact, const FText& InText) : Fact(InFact), Text(Text)
	{
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
	TArray<FDialogueResponse> DialogueResponses;

	FText GetSpeakerDialogue()
	{
		return FText::Join(FText::FromString(": "), Speaker, DialogueText);
	}
};
