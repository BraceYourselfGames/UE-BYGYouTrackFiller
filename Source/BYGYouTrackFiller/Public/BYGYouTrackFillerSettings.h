// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Templates/SubclassOf.h"
#include "Framework/Commands/InputChord.h"
#include "BYGYouTrackFiller.h"
#include "BYGYouTrackTicketData.h"
#include "BYGYouTrackFillerSettings.generated.h"

BYGYOUTRACKFILLER_API DECLARE_LOG_CATEGORY_EXTERN(LogBYGYouTrackFiller, Log, All);

UCLASS(config = "BYGYouTrackFiller", defaultconfig)
class BYGYOUTRACKFILLER_API UBYGYouTrackFillerSettings : public UObject
{
	GENERATED_BODY()

public:
	UBYGYouTrackFillerSettings(const FObjectInitializer& ObjectInitializer);

	// The URL of your company's YouTrack instance. Should end in "newIssue".
	UPROPERTY(config, EditAnywhere, Category = "Settings", DisplayName="YouTrack Base URL")
	FString YouTrackBaseURL = "https://yourcompany.myjetbrains.com/youtrack/newIssue";

	UPROPERTY(config, EditAnywhere, Category = "On Submit")
	bool bOpenLogDirectoryOnSubmit = true;

	UPROPERTY(config, EditAnywhere, Category = "On Submit")
	bool bOpenUserSettingsDirectoryOnSubmit = true;

	UPROPERTY(config, EditAnywhere, Category = "On Submit")
	bool bOpenVisualLogDirectoryOnSubmit = false;

	// Take a screenshot when the submit command is executed.
	UPROPERTY(config, EditAnywhere, Category = "On Submit|Screenshots")
	bool bTakeScreenshotOnSubmit = false;

	// When opening YouTrack, also open the screenshot directory.
	UPROPERTY(config, EditAnywhere, Category = "On Submit|Screenshots")
	bool bOpenScreenshotDirectoryOnSubmit = false;

	// Enable the cheat command in the console.
	UPROPERTY(config, EditAnywhere, Category="Activation", meta=(InlineEditConditionToggle))
	bool bEnableCheatConsoleCommand = true;
	// Entering this into the cheat console to open a browser with your settings.
	UPROPERTY(config, EditAnywhere, Category = "Activation", meta=(EditCondition="bEnableCheatConsoleCommand"))
	FString CheatCommand = "youtrack";
	
	// Show the YouTrack button at the top of the editor window.
	UPROPERTY(config, EditAnywhere, Category="Activation", meta=(ConfigRestartRequired=true))
	bool bShowEditorButton = true;

	// Global keyboard shortcut to activate the YouTrack button.
	UPROPERTY(config, EditAnywhere, Category="Activation", meta=(ConfigRestartRequired=true))
	FInputChord EditorKeyboardShortcut;

	// Unless overridden, these values will be added as defaults to all tickets
	UPROPERTY(config, EditAnywhere, Category = "Ticket Defaults", meta = ( ShowOnlyInnerProperties ))
	FBYGYouTrackTicketData DefaultTicketValues;

	// This class is used when clicking on the button in the editor. If you subclass it then change it to point to your subclass
	UPROPERTY(config, EditAnywhere, Category = "Advanced")
	TSubclassOf<UBYGYouTrackFiller> DefaultFillerClass;

	// It is very likely that you do not want your YouTrack server data to appear in ini files
	// with your shipping game. Checking this will make sure that it is stripped from shipping builds.
	// For more information see BYGYouTrackFillerEditorModule.cpp
	UPROPERTY(config, EditAnywhere, Category="Advanced")
	bool bAddYouTrackInfoToIniBlacklist = true;

};
