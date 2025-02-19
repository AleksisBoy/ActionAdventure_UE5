

#pragma once

#include "CoreMinimal.h"
#include "DialogueAssetFactory.generated.h"

UCLASS()
class DIALOGUEEDITOR_API UDialogueAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UDialogueAssetFactory(const FObjectInitializer& ObjectInitializer);

public:
	virtual UObject* FactoryCreateNew(UClass* uclass, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);
	virtual bool CanCreateNew() const override;
};
