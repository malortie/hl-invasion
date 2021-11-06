@setlocal
@prompt $
@echo off

echo Setup starting...

:: Copy mp3 sound files to media folder.
xcopy /f /i /y /s sound\mp3\*.mp3 media\invasion\sound\mp3\
xcopy /f /i /y /s sound\outro\*.mp3 media\invasion\sound\outro\

echo Setup successfully completed

endlocal
