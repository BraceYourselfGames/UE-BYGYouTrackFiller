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
				"InputCore",
				"Projects",
				"ToolMenus",
				"BYGYouTrackFiller"
			}
		);

#if UE_5_0_OR_LATER
		PrivateDependencyModuleNames.Add("DeveloperToolSettings");
#else
		PrivateDependencyModuleNames.Add("UnrealEd");
#endif
	}
}