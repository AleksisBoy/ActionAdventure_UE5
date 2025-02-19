

#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueGraphNodeStart.generated.h"

UCLASS()
class UDialogueGraphNodeStart : public UDialogueGraphNodeBase
{
	GENERATED_BODY()
public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Start"); }
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Red); }
	virtual bool CanUserDeleteNode() const override { return false; }

public:
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;

	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::Start; }
};
