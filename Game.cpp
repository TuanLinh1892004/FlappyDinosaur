#include "Game.h"
#include "TextureManager.h"
#include "ECS.h"
#include "Text.h"
#include "Map.h"
#include "Score.h"
#include "Position.h"
#include "Sprite.h"
#include "Button.h"
#include "Dino.h"
#include "Object.h"

Manager manager;
auto &myMap(manager.addEntity());
auto &object1(manager.addEntity());
auto &object2(manager.addEntity());
auto &object3(manager.addEntity());
auto &object4(manager.addEntity());
auto &dino(manager.addEntity());
auto &score(manager.addEntity());
auto &button(manager.addEntity());

SDL_Renderer *Game::renderer;
SDL_Event Game::event;
Text *Game::printText;
int Game::state;
bool Game::reload;
double Game::speed;
int Game::sc;
double Game::next;

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int x, int y, int w, int h, int flag)
{
    window = SDL_CreateWindow(title, x, y, w, h, flag);
    Game::renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(Game::renderer, 0, 255, 0, 255);
    running = 1;
    Game::printText = new Text();
    Game::state = 0;
    Game::reload = 0;
    Game::speed = 0.05;
    Game::sc = 0;
    Game::next = 0;
    cur = 5;

    myMap.addComponent <Map>();
    score.addComponent <Score>();
    dino.addComponent <Position>(70, 385);
    dino.addComponent <Sprite>();
    dino.addComponent <Dino>();
    button.addComponent <Button>();
    object1.addComponent <Position>(650, 0);
    object1.addComponent <Object>(0);
    object2.addComponent <Position>(900, 0);
    object2.addComponent <Object>(1);
    object3.addComponent <Position>(1150, 0);
    object3.addComponent <Object>(0);
    object4.addComponent <Position>(1400, 0);
    object4.addComponent <Object>(1);
}

void Game::handleEvents()
{
    SDL_PollEvent(&Game::event);
    if (Game::event.type == SDL_QUIT) running = 0;
}

void Game::update()
{
    manager.refresh();
    Game::next = std::max({object1.getComponent <Position>().getx(),
                           object2.getComponent <Position>().getx(),
                           object3.getComponent <Position>().getx(),
                           object4.getComponent <Position>().getx()});
    manager.update();
    if (Game::sc == cur) { Game::speed += 0.01; cur += 5; }
    if (Game::reload) { Game::state = 1; Game::reload = 0; manager.init(); dino.getComponent <Dino>().jump(); }
    if (Game::state != 1) return;
    if (object1.getComponent <Object>().hit(dino.getComponent <Position>().getx(), dino.getComponent <Position>().gety())) Game::state = 2;
    if (object2.getComponent <Object>().hit(dino.getComponent <Position>().getx(), dino.getComponent <Position>().gety())) Game::state = 2;
    if (object3.getComponent <Object>().hit(dino.getComponent <Position>().getx(), dino.getComponent <Position>().gety())) Game::state = 2;
    if (object4.getComponent <Object>().hit(dino.getComponent <Position>().getx(), dino.getComponent <Position>().gety())) Game::state = 2;
}

void Game::render()
{
    SDL_RenderClear(Game::renderer);
    manager.render();
    SDL_RenderPresent(Game::renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
}
