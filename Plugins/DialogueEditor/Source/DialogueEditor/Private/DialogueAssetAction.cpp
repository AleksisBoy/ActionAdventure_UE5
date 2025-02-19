


#include "DialogueAssetAction.h"
#include "DialogueAsset.h"
#include "DialogueAssetEditorApp.h"

DialogueAssetAction::DialogueAssetAction(EAssetTypeCategories::Type Category)
{
	AssetCategory = Category;
}

FText DialogueAssetAction::GetName() const
{
	return FText::FromString(TEXT("Dialogue Asset"));
}

FColor DialogueAssetAction::GetTypeColor() const
{
	return FColor::Yellow;
}

UClass* DialogueAssetAction::GetSupportedClass() const
{
	return UDialogueAsset::StaticClass();
}

void DialogueAssetAction::OpenAssetEditor(const TArray<UObject*>& inObjects, TSharedPtr<class IToolkitHost> editWithinLevelEditor)
{
	EToolkitMode::Type Mode = editWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* obj : inObjects)
	{
		UDialogueAsset* DialogueAsset = Cast<UDialogueAsset>(obj);
		if (DialogueAsset)
		{
			TSharedRef<DialogueAssetEditorApp> Editor(new DialogueAssetEditorApp());
			Editor->InitEditor(Mode, editWithinLevelEditor, DialogueAsset);
		}
	}
}

uint32 DialogueAssetAction::GetCategories()
{
	return AssetCategory;
}
