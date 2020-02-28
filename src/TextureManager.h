#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Game.h"

class TextureManager {
    private:

    public:
        static SDL_Texture* loadTexture(const char* fileName);
        static void draw(SDL_Texture* texture, SDL_Rect sourceRactangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);
};

#endif