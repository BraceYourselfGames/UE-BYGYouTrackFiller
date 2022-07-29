// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FBYGYouTrackFillerEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void HandlePluginButtonExecute();
	bool HandlerPluginButtonCanExecute();
	
protected:
	bool HandleSettingsSaved();

	void RegisterMenus();
};
