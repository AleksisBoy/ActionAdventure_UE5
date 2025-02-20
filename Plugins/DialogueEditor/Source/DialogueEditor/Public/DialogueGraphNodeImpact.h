

#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueImpactNodeInfo.h"
#include "DialogueGraphNodeImpact.generated.h"

UCLASS()
class UDialogueGraphNodeImpact : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Black); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

public:
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;
	virtual UEdGraphPin* CreateDefaultInputPin() override;
	virtual void CreateDefaultOutputPins() override;

	virtual void InitNodeInfo(UObject* Outer) override { NodeInfo = NewObject<UDialogueImpactNodeInfo>(Outer); }
	virtual void SetNodeInfo(UDialogueNodeInfoBase* nodeInfo) override { NodeInfo = Cast<UDialogueImpactNodeInfo>(nodeInfo); }
	virtual UDialogueNodeInfoBase* GetNodeInfo() override { return NodeInfo; }

	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::Impact; }
	virtual void OnPropertiesChanged() override { Modify(); }

protected:
	UPROPERTY()
	UDialogueImpactNodeInfo* NodeInfo = nullptr;
};
