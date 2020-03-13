#ifndef FONT_MANAGER_H
#define FONT_MANAGER_H

#include "Game.h"

class FontManager {
    public:
        static TTF_Font *loadFont(const char* filePath, int fileSize);
        static void draw(SDL_Texture* texture, SDL_Rect position);
};

#endif