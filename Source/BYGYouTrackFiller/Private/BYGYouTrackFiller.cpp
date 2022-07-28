// Copyright Brace Yourself Games. All Rights Reserved.

#include "BYGYouTrackFiller.h"
#include "Misc/OutputDeviceNull.h"
#include "PlatformHttp.h"

FBYGYouTrackTicketData UBYGYouTrackFiller::Merge(const FBYGYouTrackTicketData& DefaultsData, const FBYGYouTrackTicketData& CustomData)
{
	FBYGYouTrackTicketData Merged = DefaultsData;

	if (CustomData.bIncludeProject)
		Merged.Project = CustomData.Project;
	if (CustomData.bIncludeSummary)
		Merged.Summary = CustomData.Summary;
	if (CustomData.bIncludeDescription)
		Merged.Description = CustomData.Description;

	for (const auto& Pair : CustomData.CustomFields)
	{
		Merged.CustomFields.Add(Pair.Key, Pair.Value);
	}

	for (const auto& Pair : CustomData.TextReplacements)
	{
		Merged.TextReplacements.Add(Pair.Key, Pair.Value);
	}

	return Merged;
}

bool UBYGYouTrackFiller::FillAndShowTicket(const FBYGYouTrackTicketData& Data, const TArray<FString>& OtherPathsToOpen)
{
	const UBYGYouTrackFillerSettings& Settings = *GetDefault<UBYGYouTrackFillerSettings>();

	FBYGYouTrackTicketData MergedData = Merge(Settings.DefaultTicketValues, Data);

	TArray<FString> PathsToOpen = OtherPathsToOpen;

	if (Settings.bTakeScreenshotOnSubmit)
	{
		FString RequestedScreenshotPath = FPaths::ScreenShotDir() / "YouTrackFiller.png";
		FScreenshotRequest::RequestScreenshot(RequestedScreenshotPath, true, true);
	}

	if (Settings.bOpenScreenshotDirectoryOnSubmit)
	{
		PathsToOpen.Add(IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(*FPaths::ScreenShotDir()));
	}

	if (Settings.bOpenUserSettingsDirectoryOnSubmit)
	{
		PathsToOpen.Add(IFileManager::Get().ConvertToAbsolutePathForExternalAppForRead(FPlatformProcess::UserSettingsDir()));
	}

	for (const auto& Pair : MergedData.TextReplacements)
	{
		const FString Key = "{" + Pair.Key + "}";
		MergedData.Summary = MergedData.Summary.Replace(*Key, *Pair.Value);
		MergedData.Description = MergedData.Description.Replace(*Key, *Pair.Value);
	}
	// TODO find {} that are *not* replaced and warn?

	{
		TArray<FString> Parts;
		if (!MergedData.Project.IsEmpty())
			Parts.Add("project=" + FPlatformHttp::UrlEncode(MergedData.Project));
		if (!MergedData.Summary.IsEmpty())
			Parts.Add("summary=" + FPlatformHttp::UrlEncode(MergedData.Summary));
		if (!MergedData.Description.IsEmpty())
			Parts.Add("description=" + FPlatformHttp::UrlEncode(MergedData.Description));

		for (const auto& Pair : MergedData.CustomFields)
		{
			Parts.Add("c=" + FPlatformHttp::UrlEncode(Pair.Key + " " + Pair.Value));
		}

		const FString Joined = FString::Join(Parts, TEXT("&"));

		const FString URL = Settings.YouTrackBaseURL + "?" + Joined;
		PathsToOpen.Add(URL);
	}

	bool bAllSucceeded = true;
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
			bAllSucceeded = false;
		}
	}
	return bAllSucceeded;
}
