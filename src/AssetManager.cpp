#include "AssetManager.h"

AssetManager::AssetManager(EntityManager *_manager) : manager(_manager) {  }

AssetManager::~AssetManager() = default;

void AssetManager::clearData() {
    textures.clear();
}

void AssetManager::addTexture(const std::string& textureID, const char *filePath) {
    textures.emplace(textureID, TextureManager::loadTexture(filePath));
}

SDL_Texture * AssetManager::getTexture(const std::string& textureID) { return textures[textureID]; }

void AssetManager::addFont(const std::string& fontID, const char *filePath, int fontSize) {
    fonts.emplace(fontID, FontManager::loadFont(filePath, fontSize));
}

TTF_Font * AssetManager::getFont(const std::string &fontID) { return fonts[fontID]; }