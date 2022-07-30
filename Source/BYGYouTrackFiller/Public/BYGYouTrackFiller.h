// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BYGYouTrackTicketData.h"
#include "BYGYouTrackFiller.generated.h"

UCLASS()
class BYGYOUTRACKFILLER_API UBYGYouTrackFiller : public UObject
{
	GENERATED_BODY()
public:
	virtual bool FillAndShowTicket(const FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen = TArray<FString>());
	
protected:
	// Get the list of paths to run through FPlatformMisc::OnExec
	// Override this to add other directories that you want to open and show when filling a new ticket
	virtual void GetPathsToOpen(const FBYGYouTrackTicketData& Data, TArray<FString>& Paths);
	
	// Customize how the URL is built
	virtual FString GetYouTrackURL(const FBYGYouTrackTicketData& Data);

	// Merge with defaults set in Project Settings
	virtual FBYGYouTrackTicketData Merge(const FBYGYouTrackTicketData& DefaultsData, const FBYGYouTrackTicketData& CustomData);
};
