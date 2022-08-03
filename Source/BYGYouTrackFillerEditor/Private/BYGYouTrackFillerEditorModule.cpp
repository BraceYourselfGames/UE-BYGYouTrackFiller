// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerEditorModule.h"

#include "BYGYouTrackFillerSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "BYGYouTrackFillerStyle.h"
#include "BYGYouTrackFillerCommands.h"
#include "BYGYouTrackFillerModule.h"
#include "BYGYouTrackFillerStatics.h"
#include "LevelEditor.h"
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
			SettingsSection->OnModified().BindRaw(this, &FBYGYouTrackFillerEditorModule::HandleSettingsSaved);
		}
	}

	FBYGYouTrackFillerStyle::Initialize();
	FBYGYouTrackFillerStyle::ReloadTextures();

	FBYGYouTrackFillerCommands::Register();

	const FBYGYouTrackFillerCommands& Commands = FBYGYouTrackFillerCommands::Get();

	// Register level editor hooks and commands
	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedRef<FUICommandList> CommandList = LevelEditorModule.GetGlobalLevelEditorActions();

	CommandList->MapAction(Commands.FillAndShowYouTrack,
	                          FExecuteAction::CreateRaw(this, &FBYGYouTrackFillerEditorModule::HandlePluginButtonExecute),
	                          FCanExecuteAction::CreateRaw(this, &FBYGYouTrackFillerEditorModule::HandlerPluginButtonCanExecute));

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBYGYouTrackFillerEditorModule::RegisterMenus));

	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	if (Settings.bAddYouTrackInfoToIniBlacklist)
	{
		UProjectPackagingSettings* PackagingSettings = GetMutableDefault<UProjectPackagingSettings>();
		const FString Section = "/Script/BYGYouTrackFiller.BYGYouTrackFillerSettings";
		if (!PackagingSettings->IniSectionBlacklist.Contains(Section))
		{
			PackagingSettings->IniSectionBlacklist.Add(Section);
			PackagingSettings->UpdateDefaultConfigFile();
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

	FBYGYouTrackFillerStyle::Shutdown();

	FBYGYouTrackFillerCommands::Unregister();
}

bool FBYGYouTrackFillerEditorModule::HandleSettingsSaved()
{
	UBYGYouTrackFillerSettings* Settings = GetMutableDefault<UBYGYouTrackFillerSettings>();
	bool bResaveSettings = false;

	FBYGYouTrackFillerCommands::Register();
	FBYGYouTrackFillerCommands::Unregister();

	FBYGYouTrackFillerModule::Get().RefreshCheats();

	// Do not allow empty cheat string if enabled
	if (ensure(Settings) && Settings->bEnableCheatConsoleCommand && Settings->CheatCommand.IsEmpty())
	{
		Settings->CheatCommand = "youtrack";
		bResaveSettings = true;
	}

	if (bResaveSettings)
	{
		Settings->SaveConfig();
	}

	return true;
}

void FBYGYouTrackFillerEditorModule::HandlePluginButtonExecute()
{
	FBYGYouTrackTicketData Data;
	UBYGYouTrackFillerStatics::FillAndShowTicket(Data);
}

bool FBYGYouTrackFillerEditorModule::HandlerPluginButtonCanExecute()
{
	return true;
}

void FBYGYouTrackFillerEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	FLevelEditorModule& LevelEditorModule = FModuleManager::Get().LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedRef<FUICommandList> CommandList = LevelEditorModule.GetGlobalLevelEditorActions();
	
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBYGYouTrackFillerCommands::Get().FillAndShowYouTrack, CommandList);
		}
	}

	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	if (Settings.bShowEditorButton)
	{
#if ENGINE_MAJOR_VERSION >= 5
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
#else
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
#endif
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBYGYouTrackFillerCommands::Get().FillAndShowYouTrack));
				Entry.SetCommandList(CommandList);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBYGYouTrackFillerEditorModule, BYGYouTrackFillerEditor)
