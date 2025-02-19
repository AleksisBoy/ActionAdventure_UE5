#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueNodeInfo.h"
#include "DialogueGraphNode.generated.h"

class UDialogueNodeInfo;

UCLASS()
class UDialogueGraphNode : public UDialogueGraphNodeBase
{
	GENERATED_BODY()
public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Green); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

public:
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;
	void SyncPinsWithResponses();

	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual void CreateDefaultOutputPins() override;

	virtual void InitNodeInfo(UObject* Outer) override { NodeInfo = NewObject<UDialogueNodeInfo>(Outer); }
	virtual void SetNodeInfo(UDialogueNodeInfoBase* nodeInfo) override { NodeInfo = Cast<UDialogueNodeInfo>(nodeInfo); }
	virtual UDialogueNodeInfoBase* GetNodeInfo() override { return NodeInfo; }
	virtual UDialogueNodeInfo* GetDialogueNodeInfo() { return NodeInfo; }

	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::Dialogue; }
	virtual void OnPropertiesChanged() override { SyncPinsWithResponses(); }

protected:
	UPROPERTY()
	class UDialogueNodeInfo* NodeInfo = nullptr;
};
