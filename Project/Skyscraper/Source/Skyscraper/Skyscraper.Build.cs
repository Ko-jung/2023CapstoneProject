// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Skyscraper : ModuleRules
{
	public Skyscraper(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "GeometryCollectionEngine", "EnhancedInput", "MotionWarping" });
	}
}
