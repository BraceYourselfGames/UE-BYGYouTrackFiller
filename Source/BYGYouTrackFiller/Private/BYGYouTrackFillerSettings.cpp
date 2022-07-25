#include "BYGYouTrackFillerSettings.h"

DEFINE_LOG_CATEGORY(LogBYGYouTrackFiller);

#define LOCTEXT_NAMESPACE "BUIEditorValidator"

UBYGYouTrackFillerSettings::UBYGYouTrackFillerSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultTicketValues = FBYGYouTrackTicketData{
		false, "",
		false, "",
		{
			{"assignee", "me"}
		}
	};
}

#undef LOCTEXT_NAMESPACE
