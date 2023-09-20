#pragma once

#include "SDL.h"
#include "ECS.h"
#include "Position.h"

class Dino : public Component
{
private:
    Position *pos;
    double v, a, maxa;
    bool ok;

public:
    Dino()
    {
        maxa = 0.0001;
        v = 0; a = maxa;
        ok = 0;
    }
    void init() override
    {
        pos = &entity->getComponent <Position>();
    }
    void jump()
    {
        a = -0.003; v = 0;
    }
    void update() override
    {
        if (Game::state != 1) return;
        if (ok == 0 && Game::event.type == SDL_KEYDOWN && Game::event.key.keysym.sym == SDLK_SPACE) { ok = 1; jump(); }
        else if (Game::event.type == SDL_KEYUP && Game::event.key.keysym.sym == SDLK_SPACE) ok = 0;
        v += a;
        if (a < maxa) a += 0.00005;
        pos->up(0, v);
        if (pos->gety() > 385 || pos->gety() < -50) Game::state = 2;
    }
};
