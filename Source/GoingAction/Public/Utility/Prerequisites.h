#pragma once

#include "CoreMinimal.h"
#include "Prerequisites.generated.h"

USTRUCT(BlueprintType)
struct FAttackMontageData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Montage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int Amount = 0;
};
