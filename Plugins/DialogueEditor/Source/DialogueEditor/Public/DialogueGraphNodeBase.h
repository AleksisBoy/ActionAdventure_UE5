#pragma once

#include "EdGraph/EdGraphNode.h"
#include "DialogueNodeInfoBase.h"
#include "DialogueNodeType.h"
#include "DialogueGraphNodeBase.generated.h"

UCLASS()
class UDialogueGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()
public:
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) { return nullptr; }
	virtual UEdGraphPin* CreateDefaultInputPin() { return nullptr; }
	virtual void CreateDefaultOutputPins() {}

	virtual void InitNodeInfo(UObject* Outer) {}
	virtual void SetNodeInfo(UDialogueNodeInfoBase* nodeInfo) {}
	virtual UDialogueNodeInfoBase* GetNodeInfo() { return nullptr; }

	virtual EDialogueNodeType GetDialogueNodeType() const { return EDialogueNodeType::Unknown; }
	virtual void OnPropertiesChanged() {}
};
