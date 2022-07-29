// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFiller.h"
#include "Misc/OutputDeviceNull.h"
#include "PlatformHttp.h"

FBYGYouTrackTicketData UBYGYouTrackFiller::Merge( const FBYGYouTrackTicketData& DefaultsData, const FBYGYouTrackTicketData& CustomData )
{
	FBYGYouTrackTicketData Merged = DefaultsData;

	if ( CustomData.bIncludeProject )
		Merged.Project = CustomData.Project;
	if ( CustomData.bIncludeSummary )
		Merged.Summary = CustomData.Summary;
	if ( CustomData.bIncludeDescription )
		Merged.Description = CustomData.Description;

	for ( const auto& Pair : CustomData.CustomFields )
	{
		Merged.CustomFields.Add( Pair.Key, Pair.Value );
	}

	for ( const auto& Pair : CustomData.TextReplacements )
	{
		Merged.TextReplacements.Add( Pair.Key, Pair.Value );
	}

	return Merged;
}

bool UBYGYouTrackFiller::FillAndShowTicket( const FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen )
{
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();

	FBYGYouTrackTicketData MergedData = Merge( Settings.DefaultTicketValues, Data );

	TArray<FString> PathsToOpen = OtherPathsToOpen;
	GetPathsToOpen( MergedData, PathsToOpen );

	bool bAllSucceeded = true;
	for ( const FString& Path : PathsToOpen )
	{
		UE_LOG( LogBYGYouTrackFiller, Verbose, TEXT("Opening path '%s'"), *Path );
		const bool bSuccess = FPlatformMisc::OsExecute( TEXT( "open" ), *Path, TEXT( "" ) );
		if ( bSuccess )
		{
		}
		else
		{
			UE_LOG( LogBYGYouTrackFiller, Warning, TEXT("Failed to open path '%s'"), *Path );
			bAllSucceeded = false;
		}
	}
	return bAllSucceeded;
}

void UBYGYouTrackFiller::GetPathsToOpen( const FBYGYouTrackTicketData& Data, TArray<FString>& Paths )
{
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();

	if ( Settings.bTakeScreenshotOnSubmit )
	{
		FString RequestedScreenshotPath = FPaths::ScreenShotDir() / "YouTrackFiller.png";
		FScreenshotRequest::RequestScreenshot( RequestedScreenshotPath, true, true );
	}

	if ( Settings.bOpenScreenshotDirectoryOnSubmit )
	{
		Paths.Add( IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead( *FPaths::ScreenShotDir() ) );
	}

	if ( Settings.bOpenUserSettingsDirectoryOnSubmit )
	{
		Paths.Add( IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead( FPlatformProcess::UserSettingsDir() ) );
	}

	Paths.Add( GetYouTrackURL( Data ) );
}

FString UBYGYouTrackFiller::GetYouTrackURL( const FBYGYouTrackTicketData& Data )
{
	FBYGYouTrackTicketData LocalData = Data;

	for ( const auto& Pair : Data.TextReplacements )
	{
		const FString Key = "{" + Pair.Key + "}";
		LocalData.Summary = LocalData.Summary.Replace( *Key, *Pair.Value );
		LocalData.Description = LocalData.Description.Replace( *Key, *Pair.Value );
	}
	// TODO find {} that are *not* replaced and warn?

	TArray<FString> Parts;
	if ( !LocalData.Project.IsEmpty() )
		Parts.Add( "project=" + FPlatformHttp::UrlEncode( LocalData.Project ) );
	if ( !LocalData.Summary.IsEmpty() )
		Parts.Add( "summary=" + FPlatformHttp::UrlEncode( LocalData.Summary ) );
	if ( !LocalData.Description.IsEmpty() )
		Parts.Add( "description=" + FPlatformHttp::UrlEncode( LocalData.Description ) );

	for ( const auto& Pair : LocalData.CustomFields )
	{
		Parts.Add( "c=" + FPlatformHttp::UrlEncode( Pair.Key + " " + Pair.Value ) );
	}

	const FString Joined = FString::Join( Parts, TEXT( "&" ) );
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();
	const FString URL = Settings.YouTrackBaseURL + "?" + Joined;
	return URL;
}
