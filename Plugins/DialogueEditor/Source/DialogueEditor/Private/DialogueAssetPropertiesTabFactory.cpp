


#include "DialogueAssetPropertiesTabFactory.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAsset.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "DialogueNodeInfo.h"


DialogueAssetPropertiesTabFactory::DialogueAssetPropertiesTabFactory(TSharedPtr<class DialogueAssetEditorApp> App) : FWorkflowTabFactory(FName("DialogueAssetPropertiesTab"), App)
{
	this->App = App;
	TabLabel = FText::FromString(TEXT("Properties"));
	ViewMenuDescription = FText::FromString(TEXT("Displays the properties view for the current asset."));
	ViewMenuTooltip = FText::FromString(TEXT("Show the properties tab"));
}

TSharedRef<SWidget> DialogueAssetPropertiesTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<DialogueAssetEditorApp> app = App.Pin();
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	FDetailsViewArgs DetailsViewArgs;
	{
		DetailsViewArgs.bAllowSearch = false;
		DetailsViewArgs.bHideSelectionTip = true;
		DetailsViewArgs.bLockable = false;
		DetailsViewArgs.bSearchInitialKeyFocus = true;
		DetailsViewArgs.bUpdatesFromSelection = false;
		DetailsViewArgs.NotifyHook = nullptr;
		DetailsViewArgs.bShowOptions = true;
		DetailsViewArgs.bShowModifiedPropertiesOption = false;
		DetailsViewArgs.bShowScrollBar = false;
	}

	TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(app->GetWorkingAsset());

	TSharedPtr<IDetailsView> SelectedNodeDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	SelectedNodeDetailsView->SetObject(nullptr);
	app->SetSelectedNodeDetailView(SelectedNodeDetailsView);

	return SNew(SVerticalBox) + 
		SVerticalBox::Slot().FillHeight(1.0f).HAlign(HAlign_Fill)[DetailsView.ToSharedRef()] +
		SVerticalBox::Slot().FillHeight(1.0f).HAlign(HAlign_Fill)[SelectedNodeDetailsView.ToSharedRef()];
}

FText DialogueAssetPropertiesTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString(TEXT("A properties view"));
}
