// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBYGYouTrackFillerModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	BYGYOUTRACKFILLER_API void RefreshCheats();

	static inline FBYGYouTrackFillerModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FBYGYouTrackFillerModule>("BYGYouTrackFiller");
	}

protected:
	void RegisterCheats();
	void UnregisterCheats();
	void FillAndShowYouTrack(const TArray<FString>& Args);

	TArray<class IConsoleObject*> ConsoleCommands;
};
