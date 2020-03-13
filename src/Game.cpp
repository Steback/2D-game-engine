#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include "components/TransformComponent.h"
#include "components/SpriteComponent.h"
#include "components/KeyboardControlComponent.h"
#include "components/ColliderComponent.h"
#include "components/LabelComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
Map* map;
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
bool ColliderComponent::isDebugger = false;

Game::Game() {
    isRunning = false;
}

Game::~Game() = default;

bool Game::gameISRunning() const { return isRunning; }

void Game::initialize(int width, int height) {
    if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) {
        std::cerr << "Error Initializing SDL." <<  std::endl;
        return ;
    }
    if ( TTF_Init() != 0 ) {
        std::cerr << "Error Initializing SDL_TTF." <<  std::endl;
        return ;
    }

    window = SDL_CreateWindow(
            nullptr,
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
}

Entity& player(manager.addEntity("chopper", PLAYER_LAYER));

void Game::loadLevel(int levelNumber) {
    // Start including new assets to the assetmanager list
    assetManager->addTexture("tank-image",std::string("assets/images/tank-big-right.png").c_str());
    assetManager->addTexture("chopper-image",std::string("assets/images/chopper-spritesheet.png").c_str());
    assetManager->addTexture("radar-image",std::string("assets/images/radar.png").c_str());
    assetManager->addTexture("jungle-tiletexture", std::string("assets/tilemaps/jungle.png").c_str());
    assetManager->addTexture("collision-texture",std::string("assets/images/collision-texture.png").c_str());
    assetManager->addTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
    assetManager->addFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

    map = new Map("jungle-tiletexture", 2, 32);
    map->loadMap("assets/tilemaps/jungle.map", 25, 20);

    // Start including entities and also components to them
    player.addComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    player.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    player.addComponent<KeyboardControlComponent>("w", "s", "d", "a", "space");
    player.addComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);

    Entity& tankEntity(manager.addEntity("tank", ENEMY_LAYER));
    tankEntity.addComponent<TransformComponent>(150, 495, 5, 0, 32, 32, 1);
    tankEntity.addComponent<SpriteComponent>("tank-image");
    tankEntity.addComponent<ColliderComponent>("ENEMY", 150, 495, 32, 32);

    Entity& heliport(manager.addEntity("Heliport", OBSTACLE_LAYER));
    heliport.addComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    heliport.addComponent<SpriteComponent>("heliport-image");
    heliport.addComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    Entity& radarEntity(manager.addEntity("radar", UI_LAYER));
    radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.addComponent<SpriteComponent>("radar-image", 8, 150, false, true);

    Entity& labelLevelName(manager.addEntity("labelLevelName", UI_LAYER));
    labelLevelName.addComponent<TextLabelComponent>(10, 10, "First Level...", "charriot-font", WHITE_COLOR);
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

            if ( event.key.keysym.sym == SDLK_F3 ) {
               ColliderComponent::isDebugger = !ColliderComponent::isDebugger;
            }

            break;

        default:
            break;
    }
}

void Game::handleCameraMove() {
    auto* mainPlayerTransform = player.getComponent<TransformComponent>();

    camera.x = static_cast<int>(mainPlayerTransform->position.x) - static_cast<int>( WINDOW_WIDTH / 2 );
    camera.y = static_cast<int>(mainPlayerTransform->position.y) - static_cast<int>( WINDOW_HEIGHT / 2 );

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::checkCollision() {
    CollisionType collisionTagType = manager.checkCollisions();

    if (collisionTagType == PLAYER_ENEMY_COLLISION) {
        processGameOver();
    }
    if (collisionTagType == PLAYER_LEVEL_COMPLETE_COLLISION) {
        processNextLevel(1);
    }
}

void Game::processNextLevel(int _levelNumber) {
    isRunning = false;
}

void Game::processGameOver() {
    isRunning = false;
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

    handleCameraMove();

    checkCollision();
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
    delete assetManager;
    delete map;
    SDL_Quit();
}