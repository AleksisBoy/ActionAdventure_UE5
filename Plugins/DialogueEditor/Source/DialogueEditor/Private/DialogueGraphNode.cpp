#include "DialogueGraphNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"
#include "DialogueNodeInfo.h"

FText UDialogueGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeInfo->Title.IsEmpty())
	{
		FString DialogueTextStr = NodeInfo->DialogueText.ToString();
		if (DialogueTextStr.Len() > 15)
		{
			DialogueTextStr = DialogueTextStr.Left(15) + TEXT("...");
		}
		return FText::FromString(DialogueTextStr);
	}
	return NodeInfo->Title;
}

void UDialogueGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString(TEXT("Custom Node Actions")));

	UDialogueGraphNode* Node = (UDialogueGraphNode*)this;
	Section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString(TEXT("Add Response")),
		FText::FromString(TEXT("Creates a new Response")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"), TEXT("DialogueAssetEditor.NodeAddPinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node]() 
			{
				Node->GetDialogueNodeInfo()->DialogueResponses.Add(FDialogueResponse(FText::FromString(TEXT("Response"))));
				Node->SyncPinsWithResponses();

				Node->GetGraph()->NotifyGraphChanged();
				Node->GetGraph()->Modify();
			}
		))
	);
	Section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString(TEXT("Delete Response")),
		FText::FromString(TEXT("Deletes the last response")),
		FSlateIcon(TEXT("DialogueAssetEditorStyle"), TEXT("DialogueAssetEditor.NodeDeletePinIcon")),
		FUIAction(FExecuteAction::CreateLambda(
			[Node]() 
			{
				UEdGraphPin* Pin = Node->GetPinAt(Node->Pins.Num() - 1);
				if (Pin->Direction != EEdGraphPinDirection::EGPD_Input)
				{
					UDialogueNodeInfo* Info = Node->GetDialogueNodeInfo();
					Info->DialogueResponses.RemoveAt(Info->DialogueResponses.Num() - 1);
					Node->SyncPinsWithResponses();

					Node->GetGraph()->NotifyGraphChanged();
					Node->GetGraph()->Modify();
				}
			}
		))
	);
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

UEdGraphPin* UDialogueGraphNode::CreateDialoguePin(EEdGraphPinDirection Direction, FName Name)
{
	FName Category = Direction == EEdGraphPinDirection::EGPD_Input ? TEXT("Inputs") : TEXT("Outputs");
	FName SubCategory = TEXT("DialoguePin");

	UEdGraphPin* Pin = CreatePin(
		Direction, Category, Name
	);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}

UEdGraphPin* UDialogueGraphNode::CreateDefaultInputPin()
{
	return CreateDialoguePin(EEdGraphPinDirection::EGPD_Input, TEXT("Display"));
}

void UDialogueGraphNode::CreateDefaultOutputPins()
{
	FDialogueResponse DefaultResponse;
	CreateDialoguePin(EEdGraphPinDirection::EGPD_Output, FName(DefaultResponse.Text.ToString()));
	GetDialogueNodeInfo()->DialogueResponses.Add(DefaultResponse);
}
void UDialogueGraphNode::SyncPinsWithResponses()
{
	UDialogueNodeInfo* nodeInfo = GetDialogueNodeInfo();
	int NumGraphNodePins = Pins.Num() - 1;
	int NumInfoPins = nodeInfo->DialogueResponses.Num();

	while (NumGraphNodePins > NumInfoPins)
	{
		RemovePinAt(NumGraphNodePins - 1, EEdGraphPinDirection::EGPD_Output);
		NumGraphNodePins--;
	}
	while (NumInfoPins > NumGraphNodePins)
	{
		CreateDialoguePin(EEdGraphPinDirection::EGPD_Output,
			FName(nodeInfo->DialogueResponses[NumGraphNodePins].Text.ToString())
		);
		NumGraphNodePins++;
	}

	int Index = 1;
	for (const FDialogueResponse& Option : nodeInfo->DialogueResponses)
	{
		GetPinAt(Index)->PinName = FName(Option.Text.ToString());
		Index++;
	}
}

