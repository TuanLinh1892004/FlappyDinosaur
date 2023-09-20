#pragma once

#include "SDL.h"
#include "TextureManager.h"
#include "ECS.h"
#include "Position.h"
#include <random>

class Object : public Component
{
private:
    SDL_Texture *texture;
    SDL_Rect dst;
    Position *pos;
    double scale;
    int ok;
    bool give_score;
    double x, y;
    double l, r;

public:
    void change()
    {
        dst.w = 320.0 * scale; dst.h = 280.0 * scale;
        pos->sety((ok) ? 0.0 : (420.0 - double(dst.h)));
        give_score = 0;
    }
    Object(int OK)
    {
        texture = TextureManager::LoadTexture("assets/object.png");
        ok = OK;
        scale = 1;
        give_score = 0;
    }
    void init() override
    {
        pos = &entity->getComponent <Position>();
        change();
    }
    void f(double len)
    {
        l = x - abs(len) * 160.0 / 280.0;;
        r = x * 2.0 - l;
    }
    bool check(double u) { return(u >= y && u <= y + dst.h); }
    bool hit(double xpos, double ypos)
    {
        x = pos->getx(); y = pos->gety();
        if (xpos > x + dst.w / 2 || xpos + 35 < x - dst.w / 2 || ypos > y + dst.h || ypos + 35 < y) return 0;

        if (check(ypos + 34)) {
            f(ypos + 34 - y - ok * dst.h);
            if (xpos + 14 < r && xpos + 21 > l) return 1;
        }

        if (check(ypos + 15)) {
            f(ypos + 15 - y - ok * dst.h);
            if (xpos < r && xpos + 24 > l) return 1;
        }

        if (check(ypos)) {
            f(ypos - y - ok * dst.h);
            if (xpos + 17 < r && xpos + 35 > l) return 1;
        }

        return 0;
    }
    void update() override
    {
        if (Game::state != 1) return;
        pos->up(-Game::speed, 0);
        x = pos->getx();
        if (!give_score && x < 70) { Game::sc++; give_score = 1; }
        if (x + dst.w <= 0) {
            scale = double(rand() % 31 + 70) / 100.0;
            ok = rand() % 2;
            pos->setx(Game::next + 250);
            change();
        }
    }
    void render() override
    {
        dst.x = pos->getx() - dst.w / 2; dst.y = pos->gety();
        TextureManager::RenderCopyEx(texture, 0, &dst, ok * 180, 0, SDL_FLIP_NONE);
    }
};
