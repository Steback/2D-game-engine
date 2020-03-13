#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>
#include <SDL2/SDL_ttf.h>
#include "EntityManager.h"
#include "TextureManager.h"
#include "FontManager.h"

class AssetManager {
    private:
        EntityManager* manager;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;

    public:
        explicit AssetManager(EntityManager* _manager);
        ~AssetManager();
        void clearData();
        void addTexture(const std::string& textureID, const char* filePath);
        SDL_Texture* getTexture(const std::string& textureID);
        void addFont(const std::string& fontID, const char* filePath, int fontSize);
        TTF_Font * getFont(const std::string& fontID);
};

#endif