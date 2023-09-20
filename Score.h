#pragma once

#include "SDL.h"
#include "Text.h"
#include "ECS.h"

class Score : public Component
{
private:
    int Max, i;
    SDL_Rect dst;
    std::string s;

public:
    Score()
    {
        Game::sc = Max = 0;
        dst.w = 33; dst.h = 15;
        dst.y = 10;
    }
    void init() override
    {
        if (Max < Game::sc) Max = Game::sc;
        Game::sc = 0;
    }
    void draw(int u)
    {
        s = "";
        for (i = 0; i < 3; i++) {
            s = char(u % 10 + '0') + s;
            u /= 10;
        }
        Game::printText->DrawText(s, dst);
    }
    void render() override
    {
        dst.x = 350;
        draw(Game::sc);
        dst.x = 300;
        draw(Max);
    }
};
