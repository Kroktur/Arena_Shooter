#include "ArenaGraphicsSystem.h"
#include "GameState.h"

ArenaGraphicsSystem::ArenaGraphicsSystem(Demo::GameState* gameState)
    : Demo::GraphicsSystem(gameState)
{
    SDL_SetRelativeMouseMode(SDL_TRUE);
}

ArenaGraphicsSystem::~ArenaGraphicsSystem()
{
}

void ArenaGraphicsSystem::handleRawSdlEvent(const SDL_Event& evt)
{
    Demo::GraphicsSystem::handleRawSdlEvent(evt);

    if (evt.type == SDL_MOUSEMOTION)
    {
        if (mCurrentGameState)
            mCurrentGameState->mouseMoved(evt);
    }
}