// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BYGYouTrackFillerSettings.h"
#include "BYGYouTrackFiller.generated.h"

UCLASS()
class UBYGYouTrackFiller : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="BYG YouTrack Filler")
	static void CreateTicket(const FBYGYouTrackTicketData& Data);
	
protected:
	static FBYGYouTrackTicketData Merge(const FBYGYouTrackTicketData& DefaultsData, const FBYGYouTrackTicketData& CustomData);
};
