

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include <GoingAction/Public/Utility/Fact.h>
#include <GoingAction/Public/Data/ItemAsset.h>
#include "DialogueImpactNodeInfo.generated.h"

// Structs for every impact choice
USTRUCT(BlueprintType)
struct FFactImpact
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	EFact Fact;

	UPROPERTY(EditAnywhere)
	bool Value;
};

USTRUCT(BlueprintType)
struct FItemImpact
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UItemAsset* Item;
	
	UPROPERTY(EditAnywhere)
	int Amount;
};

/* for future implementations
USTRUCT(BlueprintType)
struct FQuestImpact
{
	UItemAsset* Item;
	int Amount;
};
*/
UCLASS(BlueprintType)
class DIALOGUEEDITORRUNTIME_API UDialogueImpactNodeInfo : public UDialogueNodeInfoBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
	TArray<FFactImpact> FactImpacts;

	UPROPERTY(EditAnywhere)
	TArray<FItemImpact> ItemImpacts;
};
