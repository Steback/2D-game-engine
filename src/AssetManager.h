#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>
#include "EntityManager.h"
#include "./TextureManager.h"

class AssetManager {
    private:
        EntityManager* manager;
        std::map<std::string, SDL_Texture*> textures;

    public:
        AssetManager(EntityManager* _manager);
        ~AssetManager();
        void clearData();
        void addTexture(const std::string& textureID, const char* filePath);
        SDL_Texture* getTexture(const std::string& textureID);
};

#endif