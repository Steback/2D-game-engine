#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <utility>

#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class ColliderComponent : public Component {
    public:
        std::string colliderTag;
        SDL_Rect collider;
        SDL_Rect sourceRectangle{};
        SDL_Rect destinationRectangle{};
        TransformComponent* transform{};
        SDL_Texture * colliderTexture;
        static bool isDebugger;

        ColliderComponent(std::string _colliderTag, int _x, int _y, int _width, int _height)
            : colliderTag( std::move(_colliderTag) ), collider( {_x, _y, _width, _height} ) {
            colliderTexture = Game::assetManager->getTexture("collision-texture");
        }

        void initialize() override {
            if ( owner->hasComponent<TransformComponent>() ) {
                transform = owner->getComponent<TransformComponent>();
                sourceRectangle = {0, 0, transform->width, transform->height};
                destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
            }
        }

        void update(float deltaTime) override {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
            destinationRectangle.x = collider.x - Game::camera.x;
            destinationRectangle.y = collider.y - Game::camera.y;
        }

        void render() override {
            if ( isDebugger ) {
                TextureManager::draw(colliderTexture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
            }
        }
};

#endif