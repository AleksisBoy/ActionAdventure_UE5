

#pragma once

#include "CoreMinimal.h"
#include "SGraphPanel.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class DialogueAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
public:
	virtual void RegisterTabSpawners(const TSharedRef<class FTabManager>& tabManager) override;
	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject);

	class UDialogueAsset* GetWorkingAsset() { return WorkingAsset; }
	class UEdGraph* GetWorkingGraph() { return WorkingGraph; }

	void SetWorkingGraphUI(TSharedPtr<SGraphEditor> workingGraphUI) { WorkingGraphUI = workingGraphUI; }
	void SetSelectedNodeDetailView(TSharedPtr<class IDetailsView> detailsView);
	void OnGraphSelectionChanged(const FGraphPanelSelectionSet& Selection);

public: // FAssetEditorToolkit
	virtual FName GetToolkitFName() const override { return FName(TEXT("DialogueAssetEditorApp")); }
	virtual FText GetBaseToolkitName() const override { return FText::FromString(TEXT("DialogueAssetEditorApp")); }
	virtual FString GetWorldCentricTabPrefix() const override { return TEXT("DialogueAssetEditorApp"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f); }
	virtual FString GetDocumentationLink() const override { return TEXT("https://github.com/aleksisboy"); }
	virtual void OnToolkitHostingStarted(const TSharedRef<class IToolkit>& Toolkit) override {}
	virtual void OnToolkitHostingFinished(const TSharedRef<class IToolkit>& Toolkit) override {}

	virtual void OnClose() override;
	void OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& Event);
	void OnWorkingAssetPreSave();

protected:
	void UpdateWorkingAssetFromGraph();
	void UpdateEditorGraphFromWorkingAsset();

	class UDialogueGraphNodeBase* GetSelectedNode(const FGraphPanelSelectionSet& Selection);
private:
	UPROPERTY()
	UDialogueAsset* WorkingAsset = nullptr;

	UPROPERTY()
	class UEdGraph* WorkingGraph = nullptr;

	TSharedPtr<SGraphEditor> WorkingGraphUI = nullptr;

	TSharedPtr <class IDetailsView> SelectedNodeDetailView = nullptr;
};
