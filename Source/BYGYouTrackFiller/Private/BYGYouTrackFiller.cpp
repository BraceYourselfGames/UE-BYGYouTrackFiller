// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFiller.h"

#include "Misc/OutputDeviceNull.h"
#include "PlatformHttp.h"

// TODO Make cross-platform
//#include "PlatformMisc.h"


FBYGYouTrackTicketData UBYGYouTrackFiller::Merge(const FBYGYouTrackTicketData& DefaultsData, const FBYGYouTrackTicketData& CustomData)
{
	FBYGYouTrackTicketData Merged = DefaultsData;

	if (CustomData.bIncludeSummary)
		Merged.Summary = CustomData.Summary;
	if (CustomData.bIncludeDescription)
		Merged.Description = CustomData.Description;

	for (const auto& Pair : CustomData.CustomFields)
	{
		Merged.CustomFields.Add(Pair.Key, Pair.Value);
	}

	return Merged;
}

void UBYGYouTrackFiller::CreateTicket(const FBYGYouTrackTicketData& Data)
{
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();

	const FBYGYouTrackTicketData MergedData = Merge(Settings.DefaultTicketValues, Data);

	TArray<FString> PathsToOpen;

	if (Settings.bTakeScreenshotOnSubmit)
	{
		FString RequestedScreenshotPath = FPaths::ScreenShotDir() / "YouTrackFiller.png";
		FScreenshotRequest::RequestScreenshot(RequestedScreenshotPath, true, true);
	}

	if (Settings.bOpenScreenshotFolderOnSubmit)
	{
		PathsToOpen.Add(IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::ScreenShotDir()));
	}

	if (Settings.bOpenSavesDirectoryOnSubmit)
	{
		PathsToOpen.Add(IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(FPlatformProcess::UserSettingsDir()));
	}

	{
		TArray<FString> Parts;
		Parts.Add("summary=" + MergedData.Summary);
		Parts.Add("description=" + MergedData.Description);

		for (const auto& Pair : MergedData.CustomFields)
		{
			Parts.Add("c=" + FPlatformHttp::UrlEncode(Pair.Key + " " + Pair.Value));
		}

		const FString Joined = FString::Join(Parts, TEXT("&"));

		const FString URL = Settings.YouTrackBaseURL + "?" + Joined;
		PathsToOpen.Add(URL);
	}

	for (const FString& Path : PathsToOpen)
	{
		UE_LOG(LogBYGYouTrackFiller, Verbose, TEXT("Opening path '%s'"), *Path);
		const bool bSuccess = FPlatformMisc::OsExecute(TEXT("open"), *Path, TEXT(""));
		if (bSuccess)
		{
		}
		else
		{
			UE_LOG(LogBYGYouTrackFiller, Warning, TEXT("Failed to open path '%s'"), *Path);
		}
	}
}
