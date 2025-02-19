

#pragma once

#include "CoreMinimal.h"
#include <functional>
#include "DialogueRuntimeGraph.h"
#include "DialogueAsset.generated.h"

UCLASS(BlueprintType)
class DIALOGUEEDITORRUNTIME_API UDialogueAsset : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	FString DialogueName = TEXT("Dialogue Name");

	UPROPERTY()
	UDialogueRuntimeGraph* Graph = nullptr;

public:
	void SetPreSaveListener(std::function<void()> onPreSaveListener) { OnPreSaveListener = onPreSaveListener; }

public:
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;

private:
	std::function<void()> OnPreSaveListener = nullptr;
};
