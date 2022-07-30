// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BYGYouTrackTicketData.generated.h"

USTRUCT(BlueprintType)
struct FBYGYouTrackTicketData
{
	GENERATED_BODY()
public:
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="YouTrack Ticket Data", meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeProject = false;
	// If Project is left blank, the draft ticket should be created for the user's default project
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="YouTrack Ticket Data", meta=(EditCondition="bIncludeProject"))
	FString Project;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="YouTrack Ticket Data", meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeSummary = false;
	// The short title of the ticket 
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="YouTrack Ticket Data", meta=(EditCondition="bIncludeSummary"))
	FString Summary;

	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="YouTrack Ticket Data", meta=(InlineEditConditionToggle, PinHiddenByDefault))
	bool bIncludeDescription = false;
	// The long text explaining the bug or issue. Can contain text replacement entries like {Version},
	// see TextReplacements for more info.
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="YouTrack Ticket Data", meta=(EditCondition="bIncludeDescription", MultiLine=true))
	FString Description;

	// Per-project custom fields, e.g. "Assignee", "Priority"
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category="YouTrack Ticket Data")
	TMap<FString, FString> CustomFields;
	
	// Replace instances of {Key} in Summary/Description with these values
	// e.g. Your template Description could have "Version: {Version}", and you add an entry to TextReplacements
	// TextReplacements.Add("Version", "4.2 alpha");
	UPROPERTY(BlueprintReadWrite, Category="YouTrack Ticket Data")
	TMap<FString, FString> TextReplacements;

	bool IsValid() const
	{
		return !Summary.IsEmpty();
	}
};

