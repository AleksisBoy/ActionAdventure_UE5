


#include "DialogueGraphNodeImpact.h"

FText UDialogueGraphNodeImpact::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	// in title show, Add/Remove Item (if any), Update Quest (if any), Update Fact (if any)
	FText Title = FText::FromString(TEXT("No Impact"));
	if (NodeInfo->ItemImpacts.Num() > 0)
	{
		Title = FText::FromString(TEXT("Add Item(s)"));
	}
	if (NodeInfo->FactImpacts.Num() > 0)
	{
		Title = FText::Join(FText::FromString(TEXT(" | ")), Title, FText::FromString(TEXT("Update Fact(s)")));
	}
	return Title;
}

void UDialogueGraphNodeImpact::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Impact Node Actions")));

	UDialogueGraphNodeImpact* Node = (UDialogueGraphNodeImpact*)this;
	Section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes the node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"), TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node]()
			{
				Node->GetGraph()->RemoveNode(Node);
			}
		))
	);
}

UEdGraphPin* UDialogueGraphNodeImpact::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = Direction == EEdGraphPinDirection::EGPD_Input ? TEXT("Inputs") : TEXT("Outputs");
	FName SubCategory = TEXT("ImpactPin");

	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name
	);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}

UEdGraphPin* UDialogueGraphNodeImpact::CreateDefaultInputPin()
{
	return CreateDialoguePin(EEdGraphPinDirection::EGPD_Input, FName(TEXT("Impact")));
}

void UDialogueGraphNodeImpact::CreateDefaultOutputPins()
{
	CreateDialoguePin(EEdGraphPinDirection::EGPD_Output, FName(TEXT("Continue")));
}
