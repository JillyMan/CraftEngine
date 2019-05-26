@echo off

IF EXIST bin\Debug-x64\Sandbox\Craft.dll GOTO :DELETE

xcopy /s bin\Debug-x64\Craft\Craft.dll bin\Debug-x64\Sandbox
GOTO :Finish

:DELETE
del bin\Debug-x64\Sandbox\Craft.dll

:Finish
@echo on