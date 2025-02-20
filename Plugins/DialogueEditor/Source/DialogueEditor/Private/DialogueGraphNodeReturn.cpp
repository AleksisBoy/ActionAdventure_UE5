


#include "DialogueGraphNodeReturn.h"
#include "DialogueReturnNodeInfo.h"

FText UDialogueGraphNodeReturn::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::Format(FText::FromString("Return {0}"), FText::AsNumber(NodeInfo->StepsBack));
}

void UDialogueGraphNodeReturn::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Return Node Actions")));

	UDialogueGraphNodeReturn* Node = (UDialogueGraphNodeReturn*)this;
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
UEdGraphPin* UDialogueGraphNodeReturn::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = TEXT("Inputs");
	FName SubCategory = TEXT("ReturnPin");

	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name
	);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}

UEdGraphPin* UDialogueGraphNodeReturn::CreateDefaultInputPin()
{
	return CreateDialoguePin(EEdGraphPinDirection::EGPD_Input, FName(TEXT("Return")));
}
