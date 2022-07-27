// Copyright Brace Yourself Games. All Rights Reserved.

using UnrealBuildTool;

public class BYGYouTrackFillerEditor : ModuleRules
{
	public BYGYouTrackFillerEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				//"HTTP",
				"InputCore",
				//"EditorFramework",
				"Projects",
				"ToolMenus",
				"BYGYouTrackFiller",
				"DeveloperToolSettings",
			}
		);
	}
}