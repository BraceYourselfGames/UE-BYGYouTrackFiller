#pragma once

#include "BYGYouTrackFillerSettings.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogBYGYouTrackFiller, Log, All );

USTRUCT(BlueprintType)
struct FBYGYouTrackTicketData
{
	GENERATED_BODY()
public:
	// https://mycompany.myjetbrains.com/youtrack/newIssue?project=MT&summary=boobee&description=bah&c=State%20Open&c=Type%20Bug&c=Discipline%20Programming&c=Priority%20Major&c=Planned%20Version%203%20-%20Tactical%20View&c=Assignee%20ben
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeSummary;
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIncludeSummary"))
	FString Summary;

	// Search and replace {Description}
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeDescription;
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, meta=(EditCondition="bIncludeDescription"))
	FString Description;
	
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> CustomFields;

	bool IsValid() const
	{
		return !Summary.IsEmpty();
	}
};

// TODO You really don't want this shit included in your shipping builds
UCLASS(config = Game, defaultconfig) //, AutoExpandCategories = "Validation" )
class UBYGYouTrackFillerSettings : public UObject
{
	GENERATED_BODY()

public:
	UBYGYouTrackFillerSettings(const FObjectInitializer& ObjectInitializer);

	// The URL of your company's YouTrack instance. Should end in "newIssue".
	UPROPERTY(config, EditAnywhere, Category = "Settings")
	FString YouTrackBaseURL = "https://yourcompany.myjetbrains.com/youtrack/newIssue";

	// Take a screenshot when the submit command is executed.
	UPROPERTY(config, EditAnywhere, Category = "Settings")
	bool bTakeScreenshotOnSubmit;

	UPROPERTY(config, EditAnywhere, Category = "Settings")
	bool bOpenScreenshotFolderOnSubmit;

	UPROPERTY(config, EditAnywhere, Category = "Settings")
	bool bOpenLogDirectoryOnSubmit;

	UPROPERTY(config, EditAnywhere, Category = "Settings")
	bool bOpenSavesDirectoryOnSubmit;

	UPROPERTY(config, EditAnywhere, Category = "Settings")
	bool bOpenVisualLogDirectoryOnSubmit;

	UPROPERTY(config, EditAnywhere, meta=(InlineEditConditionToggle))
	bool bEnableCheatConsoleCommand = true;
	// Entering this into the cheat console to open a browser with your settings
	UPROPERTY(config, EditAnywhere, Category = "Settings", meta=(EditCondition="bEnableCheatConsoleCommand"))
	FString CheatCommand = "youtrack";

	// Unless overridden, these values will be added as defaults to all tickets
	UPROPERTY(config, EditAnywhere, Category = "Tickets", meta = ( ShowOnlyInnerProperties ))
	FBYGYouTrackTicketData DefaultTicketValues;
};
