# BYG YouTrack Filler

Simplifies submitting tickets to YouTrack by pre-filling information and opening relevant directories on the user's PC so they can drag and drop log files and screenshots.

* Does not require or store authentication information. All operations are local to the user's computer.
* Works in editor and non-shipping builds.
* Set a default issue template and use text replacements to fill out useful info like .
* Supports custom fields in your private YouTrack e.g. Priority.
* Does not submit tickets, only pre-fills data.
* Can use either Blueprints or C++.

## Usage

### Blueprints

Fill and Show Ticket function in Blueprints

![](Resources/example-blueprint.jpg)

### C++

```c++
FBYGYouTrackTicketData Data;
// Set up any custom values
bool bSuccess = UBYGYouTrackFillerStatics::FillAndShowTicket(Data);
```

### Custom Values

How to find out the names of your custom values.

1. Click "New Ticket".
2. In your new ticket, change values in the right-hand properties panel.
3. Click "Generate issue template URL".
4. Note the `c=Property` values, where `Property` is the name of your custom value field. e.g. `Assignee`.
5. Add these custom values to your default settings or when submitting reports.

Alternatively fill them in C++ or Blue

### Templates

The plugin will automatically replace any text wrapped with curly braces `{Example}`.

```c++
FBYGYouTrackTicketData Data;
Data.TextReplacements.Add("MapName", "Facing Worlds");
Data.TextReplacements.Add("GameVersion", "4.2");
Data.TextReplacements.Add("PerforceVersion", "82582");
```

In the plugin settings, we set up this default Description.
```c++
Current Map: {MapName}
Perforce Checklist: {PerforceVersion}
Game Version: {GameVersion}
```


### Create a Cheat

Add a cheat function to your `UCheatManager` subclass, e.g.

```c++
// MyCheatManager.h
UFUNCTION(Exec)
void OpenTicket();

// MyCheatManager.cpp
void UMyCheatManager::OpenTicket()
{
    // This will show YouTrack in a browser with ticket default values filled-in.
    const FBYGYouTrackTicketData Data;
    UBYGYouTrackFillerStatics::FillAndShowTicket(Data);
}
```

## Customizing Behavior

Customizing behavior is typically done by subclassing `UBYGYouTrackFiller` and changing the Plugin settings to use this new class as the default.

## Future Goals

* Automatically strip .ini file from Shipping builds.
* Fix keyboard shortcut not working for button.
* Work out how to automatically add cheat shortcut from the plugin.
 
