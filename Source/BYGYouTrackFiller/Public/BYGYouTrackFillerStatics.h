// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "BYGYouTrackFillerStatics.generated.h"

UCLASS()
class BYGYOUTRACKFILLER_API UBYGYouTrackFillerStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category="BYG YouTrack Filler")
	static bool FillAndShowTicket(const struct FBYGYouTrackTicketData& Data);
	
	UFUNCTION(BlueprintCallable, Category="BYG YouTrack Filler")
	static bool FillAndShowTicketWithCustomPaths(const struct FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen);
};
