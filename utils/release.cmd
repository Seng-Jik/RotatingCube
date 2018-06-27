call cleansst.cmd
call buildsst.cmd
del /f /s /q ..\Bin\save.sav
devenv "..\SourceCode\VCProject2010\MyGame.sln" /Build "Release|Win32"
powershell Compress-Archive -Path ..\Bin\* -DestinationPath ..\release-$(Get-Date -Format 'yyyy-M-d-H-m-s').zip
