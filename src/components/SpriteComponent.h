#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Component.h"
#include "../AssetManager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
    private:
        TransformComponent* transform;
        SDL_Texture* texture;
        SDL_Rect sourceTectangle;
        SDL_Rect destinationRectangle;

    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        SpriteComponent(const char* filePath) {
            setTexture(filePath);
        }

        void setTexture(std::string assetTexture) {
            texture  = Game::assetManager->getTexture(assetTexture);
        }

        void initialize() override {
            transform = owner->getComponent<TransformComponent>();
            sourceTectangle.x = 0;
            sourceTectangle.y = 0;
            sourceTectangle.w = transform->width;
            sourceTectangle.h = transform->height;
        }

        void update(float deltaTime) override {
            destinationRectangle.x = (int) transform->position.x;
            destinationRectangle.y = (int) transform->position.y;
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
        }

        void render() override {
            TextureManager::draw(texture, sourceTectangle, destinationRectangle, spriteFlip);
        }
};

#endif