#pragma once

#include "CoreMinimal.h"
#include "DialogueGraphNodeBase.h"
#include "DialogueEndNodeInfo.h"
#include "DialogueGraphNodeEnd.generated.h"

UCLASS()
class UDialogueGraphNodeEnd : public UDialogueGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(FColor::Blue); }
	virtual bool CanUserDeleteNode() const override { return true; }
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

public:
	virtual UEdGraphPin* CreateDialoguePin(EEdGraphPinDirection Direction, FName Name) override;
	virtual UEdGraphPin* CreateDefaultInputPin() override;

	virtual void InitNodeInfo(UObject* Outer) override { NodeInfo = NewObject<UDialogueEndNodeInfo>(Outer); }
	virtual void SetNodeInfo(UDialogueNodeInfoBase* nodeInfo) override { NodeInfo = Cast<UDialogueEndNodeInfo>(nodeInfo); }
	virtual UDialogueNodeInfoBase* GetNodeInfo() override { return NodeInfo; }

	virtual EDialogueNodeType GetDialogueNodeType() const override { return EDialogueNodeType::End; }
	virtual void OnPropertiesChanged() override { Modify(); }

protected:
	UPROPERTY()
	class UDialogueEndNodeInfo* NodeInfo = nullptr;
};
