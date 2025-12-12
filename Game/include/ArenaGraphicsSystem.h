#pragma once
#include "GraphicsSystem.h"
#include <SDL.h>

class ArenaGraphicsSystem : public Demo::GraphicsSystem
{
public:
    ArenaGraphicsSystem(Demo::GameState* gameState);
    ~ArenaGraphicsSystem();

    void handleRawSdlEvent(const SDL_Event& evt) override;
};
