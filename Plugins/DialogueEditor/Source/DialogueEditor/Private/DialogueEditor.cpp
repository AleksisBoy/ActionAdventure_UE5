// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueEditor.h"
#include "DialogueAssetAction.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "EdGraphUtilities.h"
#include "KismetPins/SGraphPinColor.h"
#include "EdGraph/EdGraphPin.h"

#define LOCTEXT_NAMESPACE "FDialogueEditorModule"

// Dialogue
class SDialogueGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f));
	}
};

// Start
class SDialogueStartGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueStartGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(1.0f, 0.2f, 0.2f));
	}
};

// End
class SDialogueEndGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueEndGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(.2f, 0.2f, 1.f));
	}
};

// Return
class SDialogueReturnGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueReturnGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(0.949f, 0.788f, 0.122f));
	}
};

// Impact
class SDialogueImpactGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogueImpactGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPinObj);
	}
protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(0.4f, 0.4f, 0.4f));
	}
};

struct FDialoguePinFactory : public FGraphPanelPinFactory
{
public:
	virtual ~FDialoguePinFactory() {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override
	{
		if (FName(TEXT("DialoguePin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueGraphPin, Pin);
		}
		else if (FName(TEXT("StartPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueStartGraphPin, Pin);
		}
		else if (FName(TEXT("EndPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueEndGraphPin, Pin);
		}
		else if (FName(TEXT("ReturnPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueReturnGraphPin, Pin);
		}
		else if (FName(TEXT("ImpactPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogueImpactGraphPin, Pin);
		}
		return nullptr;
	}
};

void FDialogueEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetToolsModule = IAssetTools::Get();
	EAssetTypeCategories::Type AssetType = AssetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("CustomAssets")), FText::FromString("Custom Assets"));
	TSharedPtr<DialogueAssetAction> AssetAction = MakeShareable(new DialogueAssetAction(AssetType));
	AssetToolsModule.RegisterAssetTypeActions(AssetAction.ToSharedRef());

	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogueAssetEditorStyle")));
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("DialogueEditor");
	FString ContentDir = Plugin->GetContentDir();
	StyleSet->SetContentRoot(ContentDir);

	FSlateImageBrush* IconBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("DialogueAssetIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("DialogueAssetThumbnail"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* NodeAddBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeAddPinIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* NodeDeletePinBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeDeletePinIcon"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush* NodeDeleteNodeBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("NodeDeleteNodeIcon"), TEXT(".png")), FVector2D(128, 128));
	StyleSet->Set(TEXT("ClassThumbnail.DialogueAsset"), ThumbnailBrush);
	StyleSet->Set(TEXT("ClassIcon.DialogueAsset"), IconBrush);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodeAddPinIcon"), NodeAddBrush);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodeDeletePinIcon"), NodeDeletePinBrush);
	StyleSet->Set(TEXT("DialogueAssetEditor.NodeDeleteNodeIcon"), NodeDeleteNodeBrush);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);

	PinFactory = MakeShareable(new FDialoguePinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
}

void FDialogueEditorModule::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(PinFactory);
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueEditorModule, DialogueEditor)