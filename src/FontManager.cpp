#include "FontManager.h"

TTF_Font * FontManager::loadFont(const char *filePath, int fileSize) {
    return TTF_OpenFont(filePath, fileSize);
}

void FontManager::draw(SDL_Texture *texture, SDL_Rect position) {
    SDL_RenderCopy(Game::renderer, texture, nullptr, &position);
}