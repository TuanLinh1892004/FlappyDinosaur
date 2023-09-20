#pragma once

#include "ECS.h"
#include "TextureManager.h"
#include "Position.h"
#include "SDL.h"

class Sprite : public Component
{
private:
    SDL_Texture *texture;
    SDL_Rect src, dst;
    Position *pos;
    double change;

public:
    Sprite()
    {
        texture = TextureManager::LoadTexture("assets/dino.png");
        src.x = src.y = 0;
        src.w = 35; src.h = 35;
        dst.w = 35; dst.h = 35;
    }
    void init() override
    {
        pos = &entity->getComponent <Position>();
    }
    void render() override
    {
        dst.x = pos->getx(); dst.y = pos->gety();
        if (Game::state == 0) src.x = 0;
        else if (Game::state == 1) {
            change += 0.002;
            if (change >= 2) change = 0;
            src.x = int(change + 1) * 35;
        }
        else src.x = 105;
        TextureManager::RenderCopy(texture, &src, &dst);
    }
};
