// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerModule.h"

#include "BYGYouTrackFiller.h"
//#include "BYGYouTrackFillerSettings.h"
//#include "ISettingsModule.h"
//#include "ISettingsSection.h"
//#include "ISettingsContainer.h"

#define LOCTEXT_NAMESPACE "FBYGYouTrackFillerModule"

//static const FName ContainerName = "Project";
//static const FName CategoryName = "Plugins";
//static const FName SectionName = "BYG YouTrack Filler";

void FBYGYouTrackFillerModule::StartupModule()
{
	/*
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(ContainerName, CategoryName, SectionName,
		                                                                       LOCTEXT("RuntimeGeneralSettingsName", "BYG YouTrack Filler"),
		                                                                       LOCTEXT("RuntimeGeneralSettingsDescription", "Create filled YouTrack tickets"),
		                                                                       GetMutableDefault<UBYGYouTrackFillerSettings>()
			);
	}
	*/
}

void FBYGYouTrackFillerModule::ShutdownModule()
{
	//if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	//{
	//SettingsModule->UnregisterSettings(ContainerName, CategoryName, SectionName);
	//}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBYGYouTrackFillerModule, BYGYouTrackFiller)
