// Copyright Brace Yourself Games. All Rights Reserved.


#include "BYGYouTrackFillerStatics.h"

#include "BYGYouTrackFiller.h"
#include "BYGYouTrackFillerSettings.h"

bool UBYGYouTrackFillerStatics::FillAndShowTicket(const FBYGYouTrackTicketData& Data)
{
	return FillAndShowTicketWithCustomPaths(Data, TArray<FString>());
}


bool UBYGYouTrackFillerStatics::FillAndShowTicketWithCustomPaths(const FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen)
{
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	UBYGYouTrackFiller* Filler = NewObject<UBYGYouTrackFiller>(Settings.DefaultFillerClass);
	return Filler->FillAndShowTicket(Data, OtherPathsToOpen);
}
