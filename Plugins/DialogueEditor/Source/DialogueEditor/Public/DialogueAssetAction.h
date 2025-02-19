

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class DialogueAssetAction : public FAssetTypeActions_Base
{
public:
	DialogueAssetAction(EAssetTypeCategories::Type Category);

public: // FAssetTypeActions_Base
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& inObjects, TSharedPtr<class IToolkitHost> editWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type AssetCategory;
};
