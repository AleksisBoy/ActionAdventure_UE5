// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MapAsset.generated.h"

USTRUCT(Blueprintable, BlueprintType)
struct FMapPin
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector2D Position = FVector2D::ZeroVector;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Texture = nullptr;
};

UCLASS(Blueprintable, BlueprintType)
class GOINGACTION_API UMapAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapAsset)
	UTexture2D* MapImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapAsset)
	FVector2D MapImageResolution;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapAsset)
	FVector2D MapSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapAsset)
	float MinZoom = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapAsset)
	float MaxZoom = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MapAsset)
	TArray<FMapPin> MapPins;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = MapAsset)
	TArray<FMapPin> CustomPins;
};
