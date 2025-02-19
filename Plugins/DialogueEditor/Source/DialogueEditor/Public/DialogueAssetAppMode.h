

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class DialogueAssetAppMode : public FApplicationMode
{
public:
	DialogueAssetAppMode(TSharedPtr<class DialogueAssetEditorApp> App);

	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

private:
	TWeakPtr<class DialogueAssetEditorApp> App;
	FWorkflowAllowedTabSet Tabs;
};
