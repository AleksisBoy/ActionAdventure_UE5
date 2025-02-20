
#include "DialogueAssetEditorApp.h"
#include "DialogueAssetAppMode.h"
#include "DialogueAsset.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "DialogueGraphSchema.h"
#include "DialogueGraphNode.h"
#include "DialogueGraphNodeStart.h"
#include "DialogueGraphNodeEnd.h"
#include "DialogueGraphNodeReturn.h"
#include "DialogueGraphNodeImpact.h"
#include "DialogueNodeInfo.h"

DEFINE_LOG_CATEGORY_STATIC(DialogueAppSub, Log, All);

void DialogueAssetEditorApp::RegisterTabSpawners(const TSharedRef<class FTabManager>& tabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(tabManager);
}

void DialogueAssetEditorApp::InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);

	WorkingAsset = Cast<UDialogueAsset>(InObject);
	WorkingAsset->SetPreSaveListener([this] () { OnWorkingAssetPreSave(); });

	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(
		WorkingAsset,
		NAME_None,
		UEdGraph::StaticClass(),
		UDialogueGraphSchema::StaticClass()
	);

	InitAssetEditor(
		Mode,
		InitToolkitHost,
		TEXT("DialogueAssetEditor"),
		FTabManager::FLayout::NullLayout,
		true,
		true,
		ObjectsToEdit
		);

	AddApplicationMode(TEXT("DialogueAssetAppMode"), MakeShareable(new DialogueAssetAppMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogueAssetAppMode"));

	UpdateEditorGraphFromWorkingAsset();
}

UDialogueGraphNodeBase* DialogueAssetEditorApp::GetSelectedNode(const FGraphPanelSelectionSet& Selection)
{
	for (UObject* obj : Selection)
	{
		UDialogueGraphNodeBase* Node = Cast<UDialogueGraphNodeBase>(obj);
		if (Node != nullptr)
		{
			return Node;
		}
	}
	return nullptr;
}
void DialogueAssetEditorApp::SetSelectedNodeDetailView(TSharedPtr<class IDetailsView> detailsView)
{
	SelectedNodeDetailView = detailsView;
	SelectedNodeDetailView->OnFinishedChangingProperties().AddRaw(this, &DialogueAssetEditorApp::OnNodeDetailViewPropertiesUpdated);
}

void DialogueAssetEditorApp::OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selection)
{
	UDialogueGraphNodeBase* SelectedNode = GetSelectedNode(Selection);
	if (SelectedNode != nullptr)
	{
		SelectedNodeDetailView->SetObject(SelectedNode->GetNodeInfo());
	}
	else
	{
		SelectedNodeDetailView->SetObject(nullptr);
	}
}

void DialogueAssetEditorApp::OnClose()
{
	UpdateWorkingAssetFromGraph();
	WorkingAsset->SetPreSaveListener(nullptr);
	FAssetEditorToolkit::OnClose();
}

void DialogueAssetEditorApp::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event)
{
	if (WorkingGraphUI != nullptr)
	{
		UDialogueGraphNodeBase* DialogueNode = GetSelectedNode(WorkingGraphUI->GetSelectedNodes());
		if (DialogueNode != nullptr)
		{
			DialogueNode->OnPropertiesChanged();
		}
		WorkingGraphUI->NotifyGraphChanged();
	}
}

void DialogueAssetEditorApp::OnWorkingAssetPreSave()
{
	UpdateWorkingAssetFromGraph();
}

void DialogueAssetEditorApp::UpdateWorkingAssetFromGraph()
{
	if (WorkingAsset == nullptr || WorkingGraph == nullptr)
	{
		return;
	}
	UDialogueRuntimeGraph* RuntimeGraph = NewObject<UDialogueRuntimeGraph>(WorkingAsset);
	WorkingAsset->Graph = RuntimeGraph;

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UDialogueRuntimePin*> IdToPinMap;

	for (UEdGraphNode* UINode : WorkingGraph->Nodes)
	{
		UDialogueRuntimeNode* RuntimeNode = NewObject<UDialogueRuntimeNode>(RuntimeGraph);
		RuntimeNode->Position = FVector2D(UINode->NodePosX, UINode->NodePosY);

		for (UEdGraphPin* Pin : UINode->Pins)
		{
			UDialogueRuntimePin* RuntimePin = NewObject<UDialogueRuntimePin>(RuntimeNode);
			RuntimePin->PinName = Pin->PinName;
			RuntimePin->PinID = Pin->PinId;
			RuntimePin->Parent = RuntimeNode;

			if (Pin->HasAnyConnections())
			//if (Pin->HasAnyConnections() && Pin->Direction == EEdGraphPinDirection::EGPD_Output)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->PinId, Pin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}
			
			IdToPinMap.Add(Pin->PinId, RuntimePin);
			if (Pin->Direction == EEdGraphPinDirection::EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			}
			else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}

		UDialogueGraphNodeBase* UIDialogueNode = Cast<UDialogueGraphNodeBase>(UINode);
		RuntimeNode->NodeInfo = DuplicateObject(UIDialogueNode->GetNodeInfo(), RuntimeNode);
		RuntimeNode->NodeType = UIDialogueNode->GetDialogueNodeType();

		RuntimeGraph->Nodes.Add(RuntimeNode);
	}

	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UDialogueRuntimePin* Pin1 = IdToPinMap[Connection.first];
		UDialogueRuntimePin* Pin2 = IdToPinMap[Connection.second];
		Pin1->Connection = Pin2;
	}
}

void DialogueAssetEditorApp::UpdateEditorGraphFromWorkingAsset()
{
	if (WorkingAsset->Graph == nullptr)
	{
		WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);
		return;
	}

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;

	for (UDialogueRuntimeNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		UDialogueGraphNodeBase* NewNode = nullptr;
		if (RuntimeNode->NodeType == EDialogueNodeType::Start)
		{
			NewNode = NewObject<UDialogueGraphNodeStart>(WorkingGraph);
		}
		else if (RuntimeNode->NodeType == EDialogueNodeType::Dialogue)
		{
			NewNode = NewObject<UDialogueGraphNode>(WorkingGraph);
		}
		else if (RuntimeNode->NodeType == EDialogueNodeType::End)
		{
			NewNode = NewObject<UDialogueGraphNodeEnd>(WorkingGraph);
		}
		else if (RuntimeNode->NodeType == EDialogueNodeType::Return)
		{
			NewNode = NewObject<UDialogueGraphNodeReturn>(WorkingGraph);
		}
		else if (RuntimeNode->NodeType == EDialogueNodeType::Impact)
		{
			NewNode = NewObject<UDialogueGraphNodeImpact>(WorkingGraph);
		}
		else
		{
			UE_LOG(DialogueAppSub, Error, TEXT("DialogueAssetEditorApp::UpdateEditorGraphFromWorkingAsset: Unknown node type"));
			continue;
		}
		NewNode->CreateNewGuid();
		NewNode->NodePosX = RuntimeNode->Position.X;
		NewNode->NodePosY = RuntimeNode->Position.Y;
		
		if (RuntimeNode->NodeInfo != nullptr)
		{
			NewNode->SetNodeInfo(DuplicateObject(RuntimeNode->NodeInfo, RuntimeNode));
		}
		else 
		{
			NewNode->InitNodeInfo(NewNode);
		}

		if (RuntimeNode->InputPin != nullptr)
		{
			UDialogueRuntimePin* InputPin = RuntimeNode->InputPin;
			UEdGraphPin* UIPin = NewNode->CreateDialoguePin(EEdGraphPinDirection::EGPD_Input, InputPin->PinName);
			UIPin->PinId = InputPin->PinID;

			if (InputPin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(InputPin->PinID, InputPin->Connection->PinID));
			}
			IdToPinMap.Add(InputPin->PinID, UIPin);
		}
		for (UDialogueRuntimePin* OutputPin : RuntimeNode->OutputPins)
		{
			UEdGraphPin* UIPin = NewNode->CreateDialoguePin(EEdGraphPinDirection::EGPD_Output, OutputPin->PinName);
			UIPin->PinId = OutputPin->PinID;

			if (OutputPin->Connection != nullptr)
			{
				Connections.Add(std::make_pair(OutputPin->PinID, OutputPin->Connection->PinID));
			}
			IdToPinMap.Add(OutputPin->PinID, UIPin);
		}

		WorkingGraph->AddNode(NewNode, true, true);
	}
	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UEdGraphPin* FromPin = IdToPinMap[Connection.first];
		UEdGraphPin* ToPin = IdToPinMap[Connection.second];

		FromPin->LinkedTo.Add(ToPin);
		ToPin->LinkedTo.Add(FromPin);
	}
}
