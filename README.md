# BYG YouTrack Filler

Simplifies submitting tickets to YouTrack by pre-filling information and opening relevant directories on the user's PC so they can drag and drop log files and screenshots.

* Does not require or store authentication information. All operations are local to the user's computer.
* Works in editor and non-shipping builds.
* Set a default issue template and use text replacements to fill out useful info.
* Supports custom fields in your private YouTrack e.g. Priority.
* Does not submit tickets, only pre-fills data.
* Can use either Blueprints or C++.
* YouTrack information automatically stripped from Shipping builds.

## Usage

### In-Editor

Click the button in the editor to open a pre-filled ticket.

![](Resources/editor-button.jpg)

### Blueprints

Fill and Show Ticket can be called from Blueprints.

![](Resources/example-blueprint.jpg)

### C++

```c++
FBYGYouTrackTicketData Data;
// Any instances of {ComputerName} in the ticket will be replaced
Data.TextReplacements.Add("ComputerName", FPlatformProcess::ComputerName());

bool bSuccess = UBYGYouTrackFillerStatics::FillAndShowTicket(Data);
```

### Cheat Console

By default the cheat console command is `youtrack`. This can be changed in the plugin settings.

## Customization

### Setting Custom Ticket Properties

Your YouTrack may have custom properties for priority, category, severity etc. It is possible to set these using the
Custom Fields property when calling Fill And Show Ticket. First you need to confirm the name of your custom properties:

1. Click "New Ticket".
2. In your new ticket, change values in the right-hand properties panel.
3. Click "Generate issue template URL".
4. Note the `c=Property` values, where `Property` is the name of your custom value field. e.g. `Assignee`.

You can now use these custom values on your default settings or when submitting reports via C++ or Blueprints.

### Templates

The plugin will automatically replace any text wrapped with curly braces `{Example}`. This is only done for the Summary and Description fields.

```c++
FBYGYouTrackTicketData Data;
Data.TextReplacements.Add("MapName", "Facing Worlds");
Data.TextReplacements.Add("GameVersion", "4.2");
Data.TextReplacements.Add("PerforceVersion", "82582");
```

In the plugin settings, we set up this default Description.
```c++
Current Map: {MapName}
Game Version: {GameVersion}
Perforce Checklist: {PerforceVersion}
```

The resulting ticket would have this in the Description:
```
Current Map: Facing Worlds
Game Version: 4.2
Perforce Checklist: 82582
```

### C++ Behavior

Customizing other behavior is supported by subclassing `UBYGYouTrackFiller` and changing the Plugin settings to use
this new class as the default.


## Useful Debug Info Functions

```c++
const FString CPUBrand = FWindowsPlatformMisc::GetCPUBrand();
const FString GPUBrand = FWindowsPlatformMisc::GetPrimaryGPUBrand();

// Monitor info
FDisplayMetrics Display;
FDisplayMetrics::RebuildDisplayMetrics( Display );
```