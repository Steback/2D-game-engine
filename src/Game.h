#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <sol/sol.hpp>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

class AssetManager;

class Game {
    private:
        bool isRunning;
        SDL_Window* window{};

    public:
        static SDL_Renderer* renderer;
        static AssetManager* assetManager;
        static SDL_Event event;
        static SDL_Rect camera;
        Game();
        ~Game();
        bool gameISRunning() const;
        static void loadLevel(int levelNumber);
        void initialize(int width, int height);
        void processInput();
        static void handleCameraMove();
        void checkCollision();
        void processGameOver();
        void processNextLevel(int _levelNumber);
        void update();
        void render();
        void destroy();
        int ticksLastFrame{};
};

#endif