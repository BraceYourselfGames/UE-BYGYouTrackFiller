#pragma once

#include "BYGYouTrackFillerSettings.generated.h"

BYGYOUTRACKFILLER_API DECLARE_LOG_CATEGORY_EXTERN(LogBYGYouTrackFiller, Log, All);

USTRUCT(BlueprintType)
struct FBYGYouTrackTicketData
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeProject = false;
	// If Project is left blank, the draft ticket should be created for the user's default project
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIncludeProject"))
	FString Project;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeSummary = false;
	// The short title of the ticket 
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIncludeSummary"))
	FString Summary;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeDescription = false;
	// The long text explaining the bug or issue. Can contain text replacement entries like {Version},
	// see TextReplacements for more info.
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIncludeDescription", MultiLine=true))
	FString Description;

	// Per-project custom fields, e.g. "Assignee", "Priority"
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> CustomFields;
	
	// Replace instances of {Key} in Summary/Description with these values
	// e.g. Your template Description could have "Version: {Version}", and you add an entry to TextReplacements
	// TextReplacements.Add("Version", "4.2 alpha");
	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> TextReplacements;

	bool IsValid() const
	{
		return !Summary.IsEmpty();
	}
};

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
	TSubclassOf<class UBYGYouTrackFiller> DefaultFillerClass;

	// It is very likely that you do not want your YouTrack server data to appear in ini files
	// with your shipping game. Checking this will make sure that it is stripped from shipping builds.
	// For more information see BYGYouTrackFillerEditorModule.cpp
	UPROPERTY(config, EditAnywhere, Category="Advanced")
	bool bAddYouTrackInfoToIniBlacklist = true;

};
