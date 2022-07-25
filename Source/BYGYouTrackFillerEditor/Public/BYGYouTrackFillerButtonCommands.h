// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BYGYouTrackFillerButtonStyle.h"

class FBYGYouTrackFillerButtonCommands : public TCommands<FBYGYouTrackFillerButtonCommands>
{
public:
	FBYGYouTrackFillerButtonCommands()
		: TCommands<FBYGYouTrackFillerButtonCommands>(TEXT("BYGYouTrackFillerButton"), NSLOCTEXT("Contexts", "BYGYouTrackFillerButton", "BYGYouTrackFillerButton Plugin"), NAME_None, FBYGYouTrackFillerButtonStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> PluginAction;
};
