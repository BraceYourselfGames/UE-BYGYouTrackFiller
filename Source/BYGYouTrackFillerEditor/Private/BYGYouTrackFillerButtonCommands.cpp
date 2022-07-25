// Copyright Epic Games, Inc. All Rights Reserved.

#include "BYGYouTrackFillerButtonCommands.h"

#include "BYGYouTrackFillerSettings.h"

#define LOCTEXT_NAMESPACE "FExampleButtonModule"

void FBYGYouTrackFillerButtonCommands::RegisterCommands()
{
	const UBYGYouTrackFillerSettings* Settings = GetDefault<UBYGYouTrackFillerSettings>();
	FInputChord InputChord;
	if (Settings)
	{
		InputChord = Settings->EditorKeyboardShortcut;
	}
	UI_COMMAND(PluginAction, "Open YouTrack", "Open YouTrack with prefilled values.", EUserInterfaceActionType::Button, InputChord);
}

#undef LOCTEXT_NAMESPACE
