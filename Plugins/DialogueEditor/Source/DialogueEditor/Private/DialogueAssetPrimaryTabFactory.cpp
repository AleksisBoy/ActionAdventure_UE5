


#include "DialogueAssetPrimaryTabFactory.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "Editor/UnrealEd/Public/Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"


DialogueAssetPrimaryTabFactory::DialogueAssetPrimaryTabFactory(TSharedPtr<class DialogueAssetEditorApp> App) : FWorkflowTabFactory(FName("DialogueAssetPrimaryTab"), App)
{
	this->App = App;
	TabLabel = FText::FromString(TEXT("Primary"));
	ViewMenuDescription = FText::FromString(TEXT("Display primary dialogue tab"));
	ViewMenuTooltip = FText::FromString(TEXT("Show the dialogue tab"));
}

TSharedRef<SWidget> DialogueAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<DialogueAssetEditorApp> app = App.Pin();

	SGraphEditor::FGraphEditorEvents GraphEvents;
	GraphEvents.OnSelectionChanged.BindRaw(app.Get(), &DialogueAssetEditorApp::OnGraphSelectionChanged);

	TSharedPtr<SGraphEditor> GraphEditor =
		SNew(SGraphEditor)
		.IsEditable(true)
		.GraphEvents(GraphEvents)
		.GraphToEdit(app->GetWorkingGraph());

	app->SetWorkingGraphUI(GraphEditor);

	return SNew(SVerticalBox) 
		+ SVerticalBox::Slot().FillHeight(1.0f).HAlign(HAlign_Fill)
		[
			GraphEditor.ToSharedRef()
		];
}

FText DialogueAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A primary view"));
}
