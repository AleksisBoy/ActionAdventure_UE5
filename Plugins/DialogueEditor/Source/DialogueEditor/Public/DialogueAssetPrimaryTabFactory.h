

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class DialogueAssetPrimaryTabFactory : public FWorkflowTabFactory
{
public:
	DialogueAssetPrimaryTabFactory(TSharedPtr<class DialogueAssetEditorApp> App);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;

private:
	TWeakPtr<class DialogueAssetEditorApp> App;
};
