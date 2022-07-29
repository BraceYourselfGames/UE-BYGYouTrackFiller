// Copyright Epic Games, Inc. All Rights Reserved.

#include "BYGYouTrackFillerCommands.h"

#include "BYGYouTrackFillerSettings.h"

#define LOCTEXT_NAMESPACE "FExampleButtonModule"

void FBYGYouTrackFillerCommands::RegisterCommands()
{
	const UBYGYouTrackFillerSettings* Settings = GetDefault<UBYGYouTrackFillerSettings>();
	FInputChord InputChord;
	if (Settings)
	{
		InputChord = Settings->EditorKeyboardShortcut;
	}
	UI_COMMAND(FillAndShowYouTrack, "YouTrack", "Open YouTrack with prefilled values.", EUserInterfaceActionType::Button, InputChord);
}

#undef LOCTEXT_NAMESPACE
