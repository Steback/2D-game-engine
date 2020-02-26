#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "../lib/glm/glm.hpp"

EntityManager manager;
SDL_Renderer* Game::renderer;

Game::Game() {
    isRunning = false;
}

Game::~Game() = default;

bool Game::gameISRunning() const { return isRunning; }

void Game::loadLevel(int levelNumber) {  }

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

    isRunning = true;
}

void Game::processInput() {
    SDL_Event event;
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

    // TODO:
    // Here we call the manager.update to update all entities as functions of deltaTime
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // TODO:
    // Here we call the manager.render to render all entities

    SDL_RenderPresent(renderer);
}

void Game::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}