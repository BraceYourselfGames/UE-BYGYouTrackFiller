// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerEditorModule.h"

#include "BYGYouTrackFiller.h"
#include "BYGYouTrackFillerSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "BYGYouTrackFillerButtonStyle.h"
#include "BYGYouTrackFillerButtonCommands.h"
#include "BYGYouTrackFillerModule.h"
#include "BYGYouTrackFillerStatics.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Settings/ProjectPackagingSettings.h"

#define LOCTEXT_NAMESPACE "FBYGYouTrackFillerEditorModule"

static const FName ContainerName = "Project";
static const FName CategoryName = "Plugins";
static const FName SectionName = "BYG YouTrack Filler";

void FBYGYouTrackFillerEditorModule::StartupModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		ISettingsContainerPtr SettingsContainer = SettingsModule->GetContainer("Project");
		ISettingsSectionPtr SettingsSection = SettingsModule->RegisterSettings(ContainerName, CategoryName, SectionName,
		                                                                       LOCTEXT("RuntimeGeneralSettingsName", "BYG YouTrack Filler"),
		                                                                       LOCTEXT("RuntimeGeneralSettingsDescription", "Create filled YouTrack tickets"),
		                                                                       GetMutableDefault<UBYGYouTrackFillerSettings>()
			);

		if (SettingsSection.IsValid())
		{
			SettingsSection->OnModified().BindRaw( this, &FBYGYouTrackFillerEditorModule::HandleSettingsSaved );
		}
	}
	
	FBYGYouTrackFillerButtonStyle::Initialize();
	FBYGYouTrackFillerButtonStyle::ReloadTextures();

	FBYGYouTrackFillerButtonCommands::Register();
	
	const FBYGYouTrackFillerButtonCommands& Commands = FBYGYouTrackFillerButtonCommands::Get();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction( Commands.PluginAction, FExecuteAction::CreateRaw(this, &FBYGYouTrackFillerEditorModule::PluginButtonClicked));
		//FCanExecuteAction());

	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	if (Settings.bShowEditorButton)
	{
		UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBYGYouTrackFillerEditorModule::RegisterMenus));
	}

	if (Settings.bAddYouTrackInfoToIniBlacklist)
	{
		UProjectPackagingSettings* PackagingSettings = GetMutableDefault<UProjectPackagingSettings>();
		const FString Section = "/Script/BYGYouTrackFiller.BYGYouTrackFillerSettings";
		if (!PackagingSettings->IniSectionBlacklist.Contains(Section))
		{
			PackagingSettings->IniSectionBlacklist.Add(Section);
			if (!PackagingSettings->TryUpdateDefaultConfigFile())
			{
				UE_LOG(LogBYGYouTrackFiller, Warning, TEXT("Failed to update config file to add '%s' to IniSectionBlacklist"), *Section);
			}
		}
	}
}

void FBYGYouTrackFillerEditorModule::ShutdownModule()
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings(ContainerName, CategoryName, SectionName);
	}
	
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBYGYouTrackFillerButtonStyle::Shutdown();

	FBYGYouTrackFillerButtonCommands::Unregister();
}

bool FBYGYouTrackFillerEditorModule::HandleSettingsSaved()
{
	UBYGYouTrackFillerSettings* Settings = GetMutableDefault<UBYGYouTrackFillerSettings>();
	bool bResaveSettings = false;

	FBYGYouTrackFillerButtonCommands::Register();
	FBYGYouTrackFillerButtonCommands::Unregister();

	FBYGYouTrackFillerModule::Get().RefreshCheats();

	// Do not allow empty cheat string if enabled
	if (Settings->bEnableCheatConsoleCommand && Settings->CheatCommand.IsEmpty())
	{
		Settings->CheatCommand = "youtrack";
		bResaveSettings = true;
	}

	if ( bResaveSettings )
	{
		Settings->SaveConfig();
	}

	return true;
}

void FBYGYouTrackFillerEditorModule::PluginButtonClicked()
{
	FBYGYouTrackTicketData Data;
	UBYGYouTrackFillerStatics::FillAndShowTicket(Data);
}

void FBYGYouTrackFillerEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBYGYouTrackFillerButtonCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBYGYouTrackFillerButtonCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBYGYouTrackFillerEditorModule, BYGYouTrackFillerEditor)
