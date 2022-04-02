// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class EndOfEverfall : ModuleRules
{
	public EndOfEverfall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
