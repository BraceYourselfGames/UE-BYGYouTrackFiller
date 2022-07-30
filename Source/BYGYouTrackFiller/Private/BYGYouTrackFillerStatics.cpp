// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerStatics.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Package.h"
#include "BYGYouTrackFiller.h"

bool UBYGYouTrackFillerStatics::FillAndShowTicket(const FBYGYouTrackTicketData& Data)
{
	return FillAndShowTicketWithCustomPaths(Data, TArray<FString>());
}


bool UBYGYouTrackFillerStatics::FillAndShowTicketWithCustomPaths(const FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen)
{
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	UBYGYouTrackFiller* Filler = NewObject<UBYGYouTrackFiller>(GetTransientPackage(), Settings.DefaultFillerClass);
	return Filler->FillAndShowTicket(Data, OtherPathsToOpen);
}
