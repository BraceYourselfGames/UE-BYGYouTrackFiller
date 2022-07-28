// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerModule.h"
#include "BYGYouTrackFillerSettings.h"
#include "BYGYouTrackFillerStatics.h"

#define LOCTEXT_NAMESPACE "FBYGYouTrackFillerModule"

void FBYGYouTrackFillerModule::StartupModule()
{
	RegisterCheats();
}

void FBYGYouTrackFillerModule::ShutdownModule()
{
	UnregisterCheats();
}

void FBYGYouTrackFillerModule::RefreshCheats()
{
	UnregisterCheats();
	RegisterCheats();
}

void FBYGYouTrackFillerModule::RegisterCheats()
{
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	if (Settings.bEnableCheatConsoleCommand)
	{
		ConsoleCommands.Add(IConsoleManager::Get().RegisterConsoleCommand(
			*Settings.CheatCommand,
			TEXT("Fill and show a new draft ticket in YouTrack."),
			FConsoleCommandWithArgsDelegate::CreateRaw(this, &FBYGYouTrackFillerModule::FillAndShowYouTrack)));
	}
}

void FBYGYouTrackFillerModule::UnregisterCheats()
{
	for (IConsoleObject* ConsoleCommand : ConsoleCommands)
	{
		IConsoleManager::Get().UnregisterConsoleObject(ConsoleCommand);
	}
}

void FBYGYouTrackFillerModule::FillAndShowYouTrack(const TArray<FString>& Args)
{
	FBYGYouTrackTicketData Data;
	UBYGYouTrackFillerStatics::FillAndShowTicket(Data);
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FBYGYouTrackFillerModule, BYGYouTrackFiller)
