

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueReturnNodeInfo.generated.h"

UCLASS(BlueprintType)
class DIALOGUEEDITORRUNTIME_API UDialogueReturnNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	int StepsBack = 1;
};
