#pragma once

#include "SDL.h"
#include "ECS.h"
#include "TextureManager.h"

class Button : public Component
{
private:
    SDL_Texture *texture;
    int x, y;
    SDL_Rect dst;
    bool ok;

public:
    Button()
    {
        texture = TextureManager::LoadTexture("assets/start.png");
        ok = 0;
        dst.w = dst.h = 40;
        dst.x = 200 - dst.w / 2;
        dst.y = 250 - dst.h / 2;
    }
    void play()
    {
        Game::reload = 1;
        if (ok == 0) { texture = TextureManager::LoadTexture("assets/restart.png"); ok = 1; }
    }
    void update() override
    {
        if (Game::state == 1) return;
        if (Game::event.type == SDL_KEYUP) play();
        else if (Game::event.type == SDL_MOUSEBUTTONDOWN) {
            SDL_GetMouseState(&x, &y);
            if (x >= dst.x && x <= dst.x + dst.w && y >= dst.y && y <= dst.y + dst.h) play();
        }
    }
    void render() override
    {
        if (Game::state != 1) TextureManager::RenderCopy(texture, 0, &dst);
    }
};
