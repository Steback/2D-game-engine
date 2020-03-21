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
#include "components/ProjectileEmitterComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
Map* map;
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
bool ColliderComponent::isDebugger = false;
Entity* mainPlayer = nullptr;

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

    loadLevel(1);

    isRunning = true;
}

void Game::loadLevel(int levelNumber) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

   std::string levelName = "Level" + std::to_string(levelNumber);
   lua.script_file("assets/scripts/" + levelName + ".lua");

   sol::table levelData = lua[levelName];

   // LOADS ASSETS FORM LUA CONFIG FILE
   sol::table levelAssets = levelData["assets"];

   unsigned int assetIndex = 0;

   while ( true ) {
       sol::optional<sol::table> existsAssetsIndexNode = levelAssets[assetIndex];

       if ( existsAssetsIndexNode == sol::nullopt ) {
           break;
       } else {
           sol::table asset = levelAssets[assetIndex];
           std::string assetType = asset["type"];

           if ( assetType == "texture" ) {
               std::string assetID = asset["id"];
               std::string assetFile = asset["file"];
               assetManager->addTexture(assetID, assetFile.c_str());
           }

           assetIndex++;
       }
   }

   // LOADS MAP FORM LUA CONFIG FILE
   sol::table levelMap = levelData["map"];
   std::string mapTextureID = levelMap["textureAssetId"];
   std::string mapFile = levelMap["file"];

   map = new Map(
           mapTextureID,
           static_cast<int>( levelMap["scale"] ),
           static_cast<int>( levelMap["tileSize"] )
           );

   map->loadMap(
           mapFile,
           static_cast<int>( levelMap["mapSizeX"] ),
           static_cast<int>( levelMap["mapSizeY"] )
           );

   // LOADS ENITITES FORM LUA CONFIG FILE
   sol::table levelEntities = levelData["entities"];

   unsigned int entityIndex = 0;

   while ( true ) {
       sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];

       if ( existsEntityIndexNode == sol::nullopt ) {
           break;
       } else {
            sol::table entity = levelEntities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

            // Add entity
            auto& newEntity( manager.addEntity(entityName, entityLayerType) );

            // Add Transform component
            sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];

            if ( existsTransformComponent != sol::nullopt ) {
                newEntity.addComponent<TransformComponent>(
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                       static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                       static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                       static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                       static_cast<int>(entity["components"]["transform"]["width"]),
                       static_cast<int>(entity["components"]["transform"]["height"]),
                       static_cast<int>(entity["components"]["transform"]["scale"])
                   );
               }

               // Add Sprite Component
               sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];

               if (existsSpriteComponent != sol::nullopt) {
                   std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                   bool isAnimated = entity["components"]["sprite"]["animated"];

                   if ( isAnimated ) {
                       newEntity.addComponent<SpriteComponent>(
                           textureId,
                           static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                           static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                           static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                           static_cast<bool>(entity["components"]["sprite"]["fixed"])
                       );
                   } else {
                       newEntity.addComponent<SpriteComponent>(textureId, false);
                   }
               }

               // Add input control component
               sol::optional<sol::table> existsInputComponent = entity["components"]["input"];

               if (existsInputComponent != sol::nullopt) {
                   sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["input"]["keyboard"];

                   if (existsKeyboardInputComponent != sol::nullopt) {
                       std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                       std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                       std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                       std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                       std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                       newEntity.addComponent<KeyboardControlComponent>(upKey, downKey, rightKey, leftKey, shootKey);
                   }
               }

               // Add collider component
               sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];

               if (existsColliderComponent != sol::nullopt) {
                   std::string colliderTag = entity["components"]["collider"]["tag"];
                   newEntity.addComponent<ColliderComponent>(
                       colliderTag,
                       static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                       static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                       static_cast<int>(entity["components"]["transform"]["width"]),
                       static_cast<int>(entity["components"]["transform"]["height"])
                   );
               }

               // Add projectile emitter component
               sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];

               if (existsProjectileEmitterComponent != sol::nullopt) {
                   int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                   int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                   int parentEntityWidth = entity["components"]["transform"]["width"];
                   int parentEntityHeight = entity["components"]["transform"]["height"];
                   int projectileWidth = entity["components"]["projectileEmitter"]["width"];
                   int projectileHeight = entity["components"]["projectileEmitter"]["height"];
                   int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                   int projectileRange = entity["components"]["projectileEmitter"]["range"];
                   int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
                   bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
                   std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
                   Entity& projectile(manager.addEntity("projectile", PROJECTILE_LAYER));
                   projectile.addComponent<TransformComponent>(
                           parentEntityXPos + (parentEntityWidth / 2),
                           parentEntityYPos + (parentEntityHeight / 2),
                           0,
                           0,
                           projectileWidth,
                           projectileHeight,
                           1
                   );
                   projectile.addComponent<SpriteComponent>(textureAssetId);
                   projectile.addComponent<ProjectileEmitterComponent>(
                           projectileSpeed,
                           projectileAngle,
                           projectileRange,
                           projectileShouldLoop
                   );
                   projectile.addComponent<ColliderComponent>(
                           "PROJECTILE",
                           parentEntityXPos,
                           parentEntityYPos,
                           projectileWidth,
                           projectileHeight
                   );
               }
           }

       entityIndex++;
    }

    mainPlayer = manager.getEntityByName("player");
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
    if ( mainPlayer ) {
        auto* mainPlayerTransform = mainPlayer->getComponent<TransformComponent>();
        camera.x = static_cast<int>(mainPlayerTransform->position.x) - static_cast<int>( WINDOW_WIDTH / 2 );
        camera.y = static_cast<int>(mainPlayerTransform->position.y) - static_cast<int>( WINDOW_HEIGHT / 2 );

        camera.x = camera.x < 0 ? 0 : camera.x;
        camera.y = camera.y < 0 ? 0 : camera.y;
        camera.x = camera.x > camera.w ? camera.w : camera.x;
        camera.y = camera.y > camera.h ? camera.h : camera.y;
    }
}

void Game::checkCollision() {
    CollisionType collisionTagType = manager.checkCollisions();

    if (collisionTagType == PLAYER_ENEMY_COLLISION) {
        processGameOver();
    }
    if (collisionTagType == PLAYER_PROJECTILE_COLLISION) {
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