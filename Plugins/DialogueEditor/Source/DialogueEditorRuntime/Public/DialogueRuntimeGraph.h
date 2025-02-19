

#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueNodeType.h"
#include "DialogueRuntimeGraph.generated.h"


UCLASS()
class DIALOGUEEDITORRUNTIME_API UDialogueRuntimePin : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FName PinName;

	UPROPERTY()
	FGuid PinID;
	
	UPROPERTY()
	UDialogueRuntimePin* Connection = nullptr;

};

UCLASS()
class DIALOGUEEDITORRUNTIME_API UDialogueRuntimeNode : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	EDialogueNodeType NodeType = EDialogueNodeType::Dialogue;

	UPROPERTY()
	UDialogueRuntimePin* InputPin;

	UPROPERTY()
	TArray<UDialogueRuntimePin*> OutputPins;
	
	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	UDialogueNodeInfoBase* NodeInfo = nullptr;
};

UCLASS()
class DIALOGUEEDITORRUNTIME_API UDialogueRuntimeGraph : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<UDialogueRuntimeNode*> Nodes;

};
