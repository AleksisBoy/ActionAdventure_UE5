// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GoingAction : ModuleRules
{
	public GoingAction(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", 
			"InputCore", "EnhancedInput", "UMG", "Slate", "GameplayTags"});
	}
}
