


#include "DialogueAssetFactory.h"
#include "DialogueAsset.h"

UDialogueAssetFactory::UDialogueAssetFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SupportedClass = UDialogueAsset::StaticClass();
}

UObject* UDialogueAssetFactory::FactoryCreateNew(UClass* uclass, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	UDialogueAsset* Asset = NewObject<UDialogueAsset>(InParent, Name, Flags);
	return Asset;
}

bool UDialogueAssetFactory::CanCreateNew() const
{
	return true;
}
