@echo off
setlocal enabledelayedexpansion

echo ==============================================
echo   Configuration des variables OGRE
echo ==============================================
echo.

:CHOIX
echo 1 Entrer un repertoire Ogre manuellement
echo 2 Utiliser le dossier ./Ogre dans ce dossier
echo 3 quit
echo.

CHOICE /C 123 /N /M "Votre choix (1 ou 2 ou 3 ): "
IF ERRORLEVEL 3 GOTO END
IF ERRORLEVEL 2 GOTO USEDEFAULT
IF ERRORLEVEL 1 GOTO SETEXISTING

:END
exit /b 0

:SETEXISTING
SET /p OGRE_DIR="Chemin vers Ogre : "
IF NOT EXIST "%OGRE_DIR%\ogre-next" (
    ECHO Invalid Path need ogre-next
    pause 
    GOTO CHOIX
)
IF NOT EXIST "%OGRE_DIR%\ogre-next-deps" (
    ECHO Invalid Path need ogre-next-deps
    pause 
    GOTO CHOIX
)
 ECHO Valid Path Succes
GOTO SETVALUE


:USEDEFAULT
 SET OGRE_DIR="%cd%\Ogre"
IF NOT EXIST "%OGRE_DIR%\ogre-next" (
    echo Ogre non trouvé, Installation de Ogre.
    call StartUP/InstallOgre.bat
    ECHO Installation Succes
    goto SETVALUE
)
IF NOT EXIST "%OGRE_DIR%\ogre-next-deps" (
    echo Ogre non trouvé, Installation de Ogre.
    call StartUP/InstallOgre.bat
    ECHO Installation Succes
    goto SETVALUE
)
 ECHO Valid Folder Succes
GOTO SETVALUE


:SETVALUE
echo.
echo Chemin Ogre choisi : %OGRE_DIR%
echo.

:: Définition des variables d'environnement
SETX OGRE_SOURCE "%OGRE_DIR%\ogre-next"
SETX OGRE_BINARIES "%OGRE_DIR%\ogre-next\build"
SETX OGRE_LIBRARIES "%OGRE_DIR%\ogre-next-deps"

echo Variables d'environnement definies :
echo   OGRE_SOURCE=%OGRE_DIR%\ogre-next
echo   OGRE_BINARIES=%OGRE_DIR%\ogre-next\build
echo   OGRE_LIBRARIES=%OGRE_DIR%\ogre-next-deps
echo.

echo ATTENTION : Vous devrez ouvrir un nouveau terminal
echo pour que les variables soient prises en compte.
echo.

pause
