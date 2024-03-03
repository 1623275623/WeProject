// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WeProject : ModuleRules
{
	public WeProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput",
			"GameplayAbilities","SlateCore","GameplayTasks","GameplayTags","AIModule",
			"UMG"
		});
	}
}
