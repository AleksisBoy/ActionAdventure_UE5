#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "DialogueGraphSchema.generated.h"

UCLASS()
class UDialogueGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()
public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;
};

USTRUCT()
struct FNewNodeAction : public FEdGraphSchemaAction
{
	GENERATED_BODY()
public:
	FNewNodeAction() {}
	FNewNodeAction(UClass* classTemplate, FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping) 
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), ClassTemplate(classTemplate) {}

	virtual UEdGraphNode* PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode);

protected:
	UClass* ClassTemplate = nullptr;
};