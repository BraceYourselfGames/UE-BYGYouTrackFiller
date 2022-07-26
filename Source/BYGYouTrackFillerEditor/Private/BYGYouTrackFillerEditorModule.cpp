// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerEditorModule.h"

#include "BYGYouTrackFiller.h"
#include "BYGYouTrackFillerSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "BYGYouTrackFillerButtonStyle.h"
#include "BYGYouTrackFillerButtonCommands.h"
#include "BYGYouTrackFillerStatics.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName ExampleButtonTabName("ExampleButton");

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
	bool ResaveSettings = false;

	
	FBYGYouTrackFillerButtonCommands::Register();
	FBYGYouTrackFillerButtonCommands::Unregister();
	// You can put any validation code in here and resave the settings in case an invalid
	// value has been entered

	if ( ResaveSettings )
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

IMPLEMENT_MODULE(FBYGYouTrackFillerEditorModule, BYGYouTrackFiller)
