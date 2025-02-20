#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "SaveLoad.generated.h"

class USaveInstance;

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class USaveLoad : public UInterface
{
	GENERATED_BODY()
};


class GOINGACTION_API ISaveLoad
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Save/Load Interface")
	virtual void SaveState(USaveInstance* SaveInstance) = 0;
	
	UFUNCTION(BlueprintCallable, Category = "Save/Load Interface")
	virtual void LoadState(USaveInstance* SaveInstance) = 0;
	
};
