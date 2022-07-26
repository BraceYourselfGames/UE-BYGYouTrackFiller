#pragma once

#include "BYGYouTrackFillerSettings.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBYGYouTrackFiller, Log, All);

USTRUCT(BlueprintType)
struct FBYGYouTrackTicketData
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeProject = false;
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIncludeProject"))
	FString Project;
	
	// https://mycompany.myjetbrains.com/youtrack/newIssue?project=MT&summary=boobee&description=bah&c=State%20Open&c=Type%20Bug&c=Discipline%20Programming&c=Priority%20Major&c=Planned%20Version%203%20-%20Tactical%20View&c=Assignee%20ben
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeSummary = false;
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIncludeSummary"))
	FString Summary;

	// Search and replace {Description}
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeDescription = false;
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
	bool bOpenSavesDirectoryOnSubmit = true;

	UPROPERTY(config, EditAnywhere, Category = "On Submit")
	bool bOpenVisualLogDirectoryOnSubmit = false;

	// Take a screenshot when the submit command is executed.
	UPROPERTY(config, EditAnywhere, Category = "On Submit|Screenshots")
	bool bTakeScreenshotOnSubmit = false;

	UPROPERTY(config, EditAnywhere, Category = "On Submit|Screenshots")
	bool bOpenScreenshotFolderOnSubmit = false;

	// Enable the cheat command in the console
	UPROPERTY(config, EditAnywhere, meta=(InlineEditConditionToggle))
	bool bEnableCheatConsoleCommand = true;
	// Entering this into the cheat console to open a browser with your settings
	UPROPERTY(config, EditAnywhere, Category = "Activation", meta=(EditCondition="bEnableCheatConsoleCommand"))
	FString CheatCommand = "youtrack";
	
	// Enable the cheat command in the console
	UPROPERTY(config, EditAnywhere, Category="Activation", meta=(ConfigRestartRequired=true))
	bool bShowEditorButton = true;

	UPROPERTY(config, EditAnywhere, Category="Activation")
	FInputChord EditorKeyboardShortcut;

	// Unless overridden, these values will be added as defaults to all tickets
	UPROPERTY(config, EditAnywhere, Category = "Ticket Defaults", meta = ( ShowOnlyInnerProperties ))
	FBYGYouTrackTicketData DefaultTicketValues;

	// This class is used when clicking on the button in the editor. If you subclass it then change it to point to your subclass
	UPROPERTY(config, EditAnywhere, Category = "Advanced")
	TSubclassOf<class UBYGYouTrackFiller> DefaultFillerClass;
};
