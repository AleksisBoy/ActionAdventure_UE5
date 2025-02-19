#include "DialogueGraphNodeEnd.h"

FText UDialogueGraphNodeEnd::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo != nullptr && NodeInfo->Action != EDialogueNodeAction::None)
	{
		FString Result = UEnum::GetDisplayValueAsText(NodeInfo->Action).ToString();
		if (!NodeInfo->ActionData.IsEmpty())
		{
			FString ActionData = NodeInfo->ActionData;
			if (ActionData.Len() > 15)
			{
				ActionData = ActionData.Left(15) + TEXT("...");
			}
			Result += TEXT(" - ") + ActionData;
		}
		return FText::FromString(Result);
	}
	return FText::FromString(TEXT("End"));
}

void UDialogueGraphNodeEnd::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("End Node Actions")));

	UDialogueGraphNodeEnd* Node = (UDialogueGraphNodeEnd*)this;
	Section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString(TEXT("Delete Node")),
		FText::FromString(TEXT("Deletes tehe node")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"), TEXT("DialogueAssetEditor.NodeDeleteNodeIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node]()
			{
				Node->GetGraph()->RemoveNode(Node);
			}
		))
	);
}

UEdGraphPin* UDialogueGraphNodeEnd::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = TEXT("Inputs");
	FName SubCategory = TEXT("EndPin");

	UEdGraphPin* Pin = CreatePin(
		Direction,
		Category,
		Name
	);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}

UEdGraphPin* UDialogueGraphNodeEnd::CreateDefaultInputPin()
{
	return CreateDialoguePin(EEdGraphPinDirection::EGPD_Input, FName(TEXT("Finish")));
}