@echo off

IF NOT EXIST "%cd%\StartUp" (
    ECHO NEED STARTUP FOLDER
    pause 
    GOTO END
)

:GLOBALCHOICE

ECHO Choisissez une option:
ECHO 1. Ogre
ECHO 2. Vcpkg
ECHO 3. Build
ECHO 4. End


SET "StartUpDir=%cd%\StartUp"

:: Choix de base
CHOICE /C 1234 /N /M "Votre choix (1 ou 2 ou 3 ): "




IF ERRORLEVEL 4 GOTO END
IF ERRORLEVEL 3 GOTO BUILD
IF ERRORLEVEL 2 GOTO VCPKG
IF ERRORLEVEL 1 GOTO OGRE

:END
EXIT /B 0

:BUILD
IF NOT EXIST "%StartUpDir%\Build.bat" (
    ECHO need build.bat
    pause 
    GOTO END
)
call "%StartUpDir%\Build.bat"
GOTO GLOBALCHOICE

:VCPKG
IF NOT EXIST "%StartUpDir%\VcpkgSetup.bat" (
    ECHO need VcpkgSetup.bat
    pause 
    GOTO END
)
call "%StartUpDir%\VcpkgSetup.bat"
GOTO GLOBALCHOICE

:OGRE
IF NOT EXIST "%StartUpDir%\OgreSetup.bat" (
    ECHO need OgreSetup.bat
    pause 
    GOTO END
)
call "%StartUpDir%\OgreSetup.bat"
GOTO GLOBALCHOICE