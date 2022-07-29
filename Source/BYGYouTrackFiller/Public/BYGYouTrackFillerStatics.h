// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BYGYouTrackFillerSettings.h"
#include "BYGYouTrackFillerStatics.generated.h"

UCLASS()
class BYGYOUTRACKFILLER_API UBYGYouTrackFillerStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="BYG YouTrack Filler")
	static bool FillAndShowTicket(const FBYGYouTrackTicketData& Data);
	
	UFUNCTION(BlueprintCallable, Category="BYG YouTrack Filler")
	static bool FillAndShowTicketWithCustomPaths(const FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen);
};
