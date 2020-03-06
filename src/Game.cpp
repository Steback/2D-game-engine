#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "components/KeyboardControlComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
Map* map;
SDL_Renderer* Game::renderer;
SDL_Event Game::event;

Game::Game() {
    isRunning = false;
}

Game::~Game() = default;

bool Game::gameISRunning() const { return isRunning; }

void Game::loadLevel(int levelNumber) {
    // Start including new assets to the assetmanager list
    assetManager->addTexture("tank-image",std::string("assets/images/tank-big-right.png").c_str());
    assetManager->addTexture("chopper-image",std::string("assets/images/chopper-spritesheet.png").c_str());
    assetManager->addTexture("radar-image",std::string("assets/images/radar.png").c_str());
    assetManager->addTexture("jungle-tiletexture", std::string("assets/tilemaps/jungle.png").c_str());

    map = new Map("jungle-tiletexture", 2, 32);
    map->loadMap("assets/tilemaps/jungle.map", 25, 20);

    // Start including entities and also components to them
    Entity& chopperEntity(manager.addEntity("chopper"));
    chopperEntity.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    chopperEntity.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
//    chopperEntity.addComponent<KeyboardControlComponent>("up", "down", "right", "left", "space");
    chopperEntity.addComponent<KeyboardControlComponent>("w", "s", "d", "a", "space");

    Entity& tankEntity(manager.addEntity("tank"));
    tankEntity.addComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    tankEntity.addComponent<SpriteComponent>("tank-image");

    Entity& radarEntity(manager.addEntity("radar"));
    radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false, false);

    manager.listAllEntites();
}

void Game::initialize(int width, int height) {
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        std::cerr << "Error Initializing SDL." <<  std::endl;
        return ;
    }

    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_BORDERLESS
            );

    if ( !window ) {
        std::cerr << "Error creating SDL Window." <<  std::endl;
        return ;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if ( !renderer ) {
        std::cerr << "Error creating SDL Renderer." <<  std::endl;
        return ;
    }

    loadLevel(0);

    isRunning = true;

    return ;
}

void Game::processInput() {
    SDL_PollEvent(&event);

    switch ( event.type ) {
        case SDL_QUIT:
            isRunning = false;
            break;

        case SDL_KEYDOWN:
            if ( event.key.keysym.sym == SDLK_ESCAPE ) {
                isRunning = false;
            }

            break;

        default:
            break;
    }
}

void Game::update() {
    // wait untill 16ms has ellasped since the last frame
    while ( !SDL_TICKS_PASSED( SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME ) );

    // Delta time is the diference in ticks from last frame converted to seconds
    float deltaTime = ( SDL_GetTicks() - (float)ticksLastFrame ) / 1000.0f;

    // Clamp deltaTime to a maximum value
    deltaTime = ( deltaTime > 0.05f ) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass
    ticksLastFrame = SDL_GetTicks();

    manager.update(deltaTime);
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if ( manager.hasNoEntities() ) {
        return ;
    }

    manager.render();

    SDL_RenderPresent(renderer);
}

void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    delete assetManager;
}