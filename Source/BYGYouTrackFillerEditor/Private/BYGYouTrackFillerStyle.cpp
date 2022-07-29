// Copyright Epic Games, Inc. All Rights Reserved.

#include "BYGYouTrackFillerStyle.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

#if ENGINE_MAJOR_VERSION >= 5
#include "Styling/SlateStyleMacros.h"
#else
#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#endif

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
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FBYGYouTrackFillerStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("BYGYouTrackFillerStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("BYGYouTrackFiller")->GetBaseDir() / TEXT("Resources"));

#if ENGINE_MAJOR_VERSION >= 5
	Style->Set("BYGYouTrackFiller.FillAndShowYouTrack", new IMAGE_BRUSH_SVG(TEXT("YouTrackFillerButtonIcon"), Icon20x20));
#else
	Style->Set("BYGYouTrackFiller.FillAndShowYouTrack", new IMAGE_BRUSH(TEXT("YouTrackFillerButtonIcon"), Icon40x40));
#endif
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
