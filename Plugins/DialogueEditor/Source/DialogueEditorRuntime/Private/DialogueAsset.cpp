#include "DialogueAsset.h"
#include "UObject/ObjectSaveContext.h"

void UDialogueAsset::PreSave(FObjectPreSaveContext SaveContext)
{
	if (OnPreSaveListener)
	{
		OnPreSaveListener();
	}
}
