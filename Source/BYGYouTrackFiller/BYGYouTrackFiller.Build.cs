// Copyright Brace Yourself Games. All Rights Reserved.

using UnrealBuildTool;

public class BYGYouTrackFiller : ModuleRules
{
	public BYGYouTrackFiller(ReadOnlyTargetRules Target) : base(Target)
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
				"HTTP",
			}
		);
	}
}