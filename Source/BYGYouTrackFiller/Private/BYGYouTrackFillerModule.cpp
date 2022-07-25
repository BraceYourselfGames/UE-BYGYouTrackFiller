// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerModule.h"

#include "BYGYouTrackFiller.h"
#include "BYGYouTrackFillerSettings.h"
#include "ISettingsModule.h"
#include "ISettingsSection.h"
#include "ISettingsContainer.h"
#include "BYGYouTrackFillerButtonStyle.h"
#include "BYGYouTrackFillerButtonCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName ExampleButtonTabName("ExampleButton");

#define LOCTEXT_NAMESPACE "FBYGYouTrackFillerModule"

static const FName ContainerName = "Project";
static const FName CategoryName = "Plugins";
static const FName SectionName = "BYG YouTrack Filler";

void FBYGYouTrackFillerModule::StartupModule()
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
			SettingsSection->OnModified().BindRaw( this, &FBYGYouTrackFillerModule::HandleSettingsSaved );
		}
	}
	
	FBYGYouTrackFillerButtonStyle::Initialize();
	FBYGYouTrackFillerButtonStyle::ReloadTextures();

	FBYGYouTrackFillerButtonCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FBYGYouTrackFillerButtonCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FBYGYouTrackFillerModule::PluginButtonClicked),
		FCanExecuteAction());

	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	if (Settings.bShowEditorButton)
	{
		UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBYGYouTrackFillerModule::RegisterMenus));
	}
}

void FBYGYouTrackFillerModule::ShutdownModule()
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

bool FBYGYouTrackFillerModule::HandleSettingsSaved()
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

void FBYGYouTrackFillerModule::PluginButtonClicked()
{
	FBYGYouTrackTicketData Data;
	UBYGYouTrackFiller::CreateTicket(Data);
	/*
	FText DialogText = FText::Format(
							LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
							FText::FromString(TEXT("FBYGYouTrackFillerButtonModule::PluginButtonClicked()")),
							FText::FromString(TEXT("BYGYouTrackFillerButton.cpp"))
					   );
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
	*/
}

void FBYGYouTrackFillerModule::RegisterMenus()
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

IMPLEMENT_MODULE(FBYGYouTrackFillerModule, BYGYouTrackFiller)
