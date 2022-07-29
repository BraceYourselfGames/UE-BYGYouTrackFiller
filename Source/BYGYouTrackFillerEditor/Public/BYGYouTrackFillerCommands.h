// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BYGYouTrackFillerStyle.h"

class FBYGYouTrackFillerCommands : public TCommands<FBYGYouTrackFillerCommands>
{
public:
	FBYGYouTrackFillerCommands()
		: TCommands<FBYGYouTrackFillerCommands>(TEXT("BYGYouTrackFiller"), NSLOCTEXT("Contexts", "BYGYouTrackFiller", "BYGYouTrackFiller Plugin"), NAME_None, FBYGYouTrackFillerStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> FillAndShowYouTrack;
};
