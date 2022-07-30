@echo off
SETLOCAL

rem Set your plugin name, should match the .uplugin filename
set PLUGIN_NAME=BYGYouTrackFiller

rem Always add trailing space please
rem Don't put trailing slashes
set UNREAL_PATHS=E:\UE_4.25 ^
E:\UE_4.26 ^
E:\UE_4.27 ^
E:\UE_5.0

rem You might want to change this
set TEMP_DIR=C:\Temp\PluginTest

(for %%p in (%UNREAL_PATHS%) do (

	rem Find last path use that as our unique temp dir

	%%p\Engine\Build\BatchFiles\RunUAT.bat BuildPlugin ^
	-Plugin="%~dp0%PLUGIN_NAME%.uplugin" ^
	-Package="%TEMP_DIR%" ^
	-%PLUGIN_NAME% ^
	-VS2019 ^
	-NoHostPlatform ^
	-TargetPlatforms=Win64+Mac+Linux
	-StrictIncludes
))

ENDLOCAL
