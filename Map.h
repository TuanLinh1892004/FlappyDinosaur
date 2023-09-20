#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "ECS.h"

class Map : public Component
{
private:
    SDL_Texture *texture;
    SDL_Rect src;
    double x;

public:
    Map()
    {
        texture = TextureManager::LoadTexture("assets/map.png");
        src.w = 400; src.h = 500;
        src.x = 0; src.y = 0;
        x = 0;
    }
    void update() override
    {
        if (Game::state != 1) return;
        x += Game::speed;
        if (x > 400) x = 0;
    }
    void render() override
    {
        src.x = x;
        TextureManager::RenderCopy(texture, &src, 0);
    }
};
