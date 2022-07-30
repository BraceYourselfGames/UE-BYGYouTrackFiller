// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFillerSettings.h"

DEFINE_LOG_CATEGORY(LogBYGYouTrackFiller);

#define LOCTEXT_NAMESPACE "BUIEditorValidator"

UBYGYouTrackFillerSettings::UBYGYouTrackFillerSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	  , DefaultFillerClass(UBYGYouTrackFiller::StaticClass())
{
	DefaultTicketValues = FBYGYouTrackTicketData{
		true, "YourProjectName",
		false, "",
		true, "Please enter repro steps.\nVersion: {Version}\nComputer Name: {ComputerName}",
		{
			{"assignee", "me"}
		},
	};
}

#undef LOCTEXT_NAMESPACE
