// Copyright Epic Games, Inc. All Rights Reserved.

#include "BYGYouTrackFillerStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FBYGYouTrackFillerStyle::StyleInstance = nullptr;

void FBYGYouTrackFillerStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FBYGYouTrackFillerStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FBYGYouTrackFillerStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("BYGYouTrackFillerStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FBYGYouTrackFillerStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("BYGYouTrackFillerStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BYGYouTrackFiller")->GetBaseDir() / TEXT("Resources"));

	Style->Set("BYGYouTrackFiller.FillAndShowYouTrack", new IMAGE_BRUSH_SVG(TEXT("YouTrackFillerButtonIcon"), Icon20x20));
	return Style;
}

void FBYGYouTrackFillerStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FBYGYouTrackFillerStyle::Get()
{
	return *StyleInstance;
}
