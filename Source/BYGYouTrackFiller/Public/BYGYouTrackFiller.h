// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BYGYouTrackFillerSettings.h"
#include "BYGYouTrackFiller.generated.h"

// Subclass me to customize behaviour
UCLASS()
class BYGYOUTRACKFILLER_API UBYGYouTrackFiller : public UObject
{
	GENERATED_BODY()
public:
	virtual bool FillAndShowTicket(const FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen = TArray<FString>());
	
protected:
	virtual FBYGYouTrackTicketData Merge(const FBYGYouTrackTicketData& DefaultsData, const FBYGYouTrackTicketData& CustomData);
};
