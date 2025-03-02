

#pragma once

#include "CoreMinimal.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueImpactNodeInfo.generated.h"

class UItemAsset; 
enum class EFact : uint8;

// Structs for every impact choice
USTRUCT(BlueprintType)
struct FFactImpact
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	EFact Fact = static_cast<EFact>(0);

	UPROPERTY(EditAnywhere)
	bool Value = true;
};

USTRUCT(BlueprintType)
struct FItemImpact
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UItemAsset* Item = nullptr;
	
	UPROPERTY(EditAnywhere)
	int Amount = 1;
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
