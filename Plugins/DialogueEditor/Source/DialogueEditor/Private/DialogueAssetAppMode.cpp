


#include "DialogueAssetAppMode.h"
#include "DialogueAssetEditorApp.h"
#include "DialogueAssetPrimaryTabFactory.h"
#include "DialogueAssetPropertiesTabFactory.h"


DialogueAssetAppMode::DialogueAssetAppMode(TSharedPtr<class DialogueAssetEditorApp> App) : FApplicationMode(TEXT("DialogueAssetAppMode"))
{
	this->App = App;
	Tabs.RegisterFactory(MakeShareable(new DialogueAssetPrimaryTabFactory(App)));
	Tabs.RegisterFactory(MakeShareable(new DialogueAssetPropertiesTabFactory(App)));

	TabLayout = FTabManager::NewLayout("DialogueAssetAppMode_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.75)
					->AddTab(FName(TEXT("DialogueAssetPrimaryTab")), ETabState::OpenedTab)
				)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.25)
					->AddTab(FName(TEXT("DialogueAssetPropertiesTab")), ETabState::OpenedTab)
				)
			)
		);
}

void DialogueAssetAppMode::RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) 
{
	TSharedPtr<DialogueAssetEditorApp> app = App.Pin();
	app->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void DialogueAssetAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void DialogueAssetAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
