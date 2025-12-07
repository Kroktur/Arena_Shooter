//#include "EmptyProjectGameState.h"
#include "ASGameState.h"
#include "GraphicsSystem.h"

#include "Compositor/OgreCompositorManager2.h"
#include "OgreCamera.h"
#include "OgreConfigFile.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include "OgreWindow.h"

// Declares WinMain / main
#include "MainEntryPointHelper.h"
#include "System/MainEntryPoints.h"
#include "shlobj.h"



INT WINAPI WinMainApp(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR strCmdLine, INT nCmdShow)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    return Demo::MainEntryPoints::mainAppSingleThreaded(DEMO_MAIN_ENTRY_PARAMS);
}

namespace Demo
{
    class EmptyProjectGraphicsSystem final : public GraphicsSystem
    {
        Ogre::CompositorWorkspace* setupCompositor() override
        {
            return GraphicsSystem::setupCompositor();
        }

        void setupResources() override
        {
            GraphicsSystem::setupResources();

            Ogre::ConfigFile cf;
            cf.load(mResourcePath + "resources2.cfg");

         /*   Ogre::String dataFolder = cf.getSetting("DoNotUseAsResource", "Hlms", "");

            if (dataFolder.empty())
                dataFolder = "./";
            else if (*(dataFolder.end() - 1) != '/')
                dataFolder += "/";

            dataFolder += "Pbs/Materials";

           addResourceLocation(dataFolder, "FileSystem", "General");*/

            addResourceLocation(
                mResourcePath + "Data/Hlms/Pbs/Any/",
                "FileSystem", "General"
            );
            addResourceLocation(
                mResourcePath + "Data/Hlms/Pbs/GLSL/",
                "FileSystem", "General"
            );
            addResourceLocation(
                mResourcePath + "Data/Hlms/Pbs/GLSLES/",
                "FileSystem", "General"
            );
            addResourceLocation(
                mResourcePath + "Data/Hlms/Pbs/Materials/",
                "FileSystem", "General"
            );
            addResourceLocation(
                mResourcePath + "Data/Hlms/Pbs/Metal/",
                "FileSystem", "General"
            );
            addResourceLocation(
                mResourcePath + "Data/Hlms/Pbs/Textures/",
                "FileSystem", "General"
            );
        }

    public:
        EmptyProjectGraphicsSystem(GameState* gameState) : GraphicsSystem(gameState)
        {
            mResourcePath = "../../../Media/";

            // It's recommended that you set this path to:
            //	%APPDATA%/EmptyProject/ on Windows
            //	~/.config/EmptyProject/ on Linux
            //	macCachePath() + "/EmptyProject/" (NSCachesDirectory) on Apple -> Important because
            //	on iOS your app could be rejected from App Store when they see iCloud
            //	trying to backup your Ogre.log & ogre.cfg auto-generated without user
            //	intervention. Also convenient because these settings will be deleted
            //	if the user removes cached data from the app, so the settings will be
            //	reset.
            //  Obviously you can replace "EmptyProject" by your app's name.
            mWriteAccessFolder = +"/";
            TCHAR path[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, path) !=
                S_OK))
            {
                // Need to convert to OEM codepage so that fstream can
                // use it properly on international systems.
                int size_needed =
                    WideCharToMultiByte(CP_OEMCP, 0, path, (int)wcslen(path), NULL, 0, NULL, NULL);
                mWriteAccessFolder = std::string(size_needed, 0);
                WideCharToMultiByte(CP_OEMCP, 0, path, (int)wcslen(path), &mWriteAccessFolder[0],
                    size_needed, NULL, NULL);

                mWriteAccessFolder += "/EmptyProject/";

                // Attempt to create directory where config files go
                if (!CreateDirectoryA(mWriteAccessFolder.c_str(), NULL) &&
                    GetLastError() != ERROR_ALREADY_EXISTS)
                {
                    // Couldn't create directory (no write access?),
                    // fall back to current working dir
                    mWriteAccessFolder = "";
                }
            }
        }
    };

    void MainEntryPoints::createSystems(GameState** outGraphicsGameState,
        GraphicsSystem** outGraphicsSystem,
        GameState** outLogicGameState, LogicSystem** outLogicSystem)
    {
        ArenaShooterGameState* gfxGameState = new ArenaShooterGameState("Arena Shooter Project Example");

        GraphicsSystem* graphicsSystem = new EmptyProjectGraphicsSystem(gfxGameState);

        gfxGameState->_notifyGraphicsSystem(graphicsSystem);

        *outGraphicsGameState = gfxGameState;
        *outGraphicsSystem = graphicsSystem;
    }

    void MainEntryPoints::destroySystems(GameState* graphicsGameState, GraphicsSystem* graphicsSystem,
        GameState* logicGameState, LogicSystem* logicSystem)
    {
        delete graphicsSystem;
        delete graphicsGameState;
    }

    const char* MainEntryPoints::getWindowTitle() { return "Empty Project Sample"; }
}  // namespace Demo
