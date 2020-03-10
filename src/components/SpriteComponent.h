#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <SDL2/SDL.h>
#include "../Component.h"
#include "../AssetManager.h"
#include "../Animation.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
    private:
        TransformComponent* transform{};
        SDL_Texture* texture{};
        SDL_Rect sourceTectangle{};
        SDL_Rect destinationRectangle{};
        bool isAnimated;
        int numFrames{};
        int animationSpeed{};
        bool isFixed;
        std::map<std::string, Animation> animations;
        std::string currentAnimationName;
        unsigned int animationIndex = 0;

    public:
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

        explicit SpriteComponent(const std::string& assetTextureID) {
            isAnimated = false;
            isFixed = false;
            setTexture(assetTextureID);
        }

        SpriteComponent(const std::string& _id, int _numframes, int _animationSpeed, bool _hasDirections, bool _isFixed) {
            isAnimated = true;
            numFrames = _numframes;
            animationSpeed = _animationSpeed;
            isFixed = _isFixed;

            if ( _hasDirections ) {
                Animation downAnimation = Animation(0, numFrames, animationSpeed);
                Animation rightAnimation = Animation(1, numFrames, animationSpeed);
                Animation leftAnimation = Animation(2, numFrames, animationSpeed);
                Animation upAnimation = Animation(3, numFrames, animationSpeed);

                animations.emplace("DownAnimation", downAnimation);
                animations.emplace("RightAnimation", rightAnimation);
                animations.emplace("LeftAnimation", leftAnimation);
                animations.emplace("UpAnimation", upAnimation);

                animationIndex = 0;
                currentAnimationName = "DownAnimation";
            } else {
                Animation singleAnimation = Animation(0, numFrames, animationSpeed);
                animations.emplace("singleAnimation", singleAnimation);
                animationIndex = 0;
                currentAnimationName = "singleAnimation";
            }

            play(currentAnimationName);

            setTexture(_id);
        }

        void play(const std::string& _animationFrame) {
            numFrames = static_cast<int>( animations[_animationFrame].numFrames );
            animationIndex = animations[_animationFrame].index;
            animationSpeed = static_cast<int>( animations[_animationFrame].animationSpeed );
            currentAnimationName = _animationFrame;
        }

        void setTexture(const std::string& assetTextureID) {
            texture  = Game::assetManager->getTexture(assetTextureID);
        }

        void initialize() override {
            transform = owner->getComponent<TransformComponent>();
            sourceTectangle.x = 0;
            sourceTectangle.y = 0;
            sourceTectangle.w = transform->width;
            sourceTectangle.h = transform->height;
        }

        void update(float deltaTime) override {
            if ( isAnimated ) {
                sourceTectangle.x = sourceTectangle.w * static_cast<int>( ( SDL_GetTicks() / animationSpeed ) % numFrames );
            }

            sourceTectangle.y = static_cast<int>(animationIndex) * transform->height;

            destinationRectangle.x = static_cast<int>( transform->position.x ) - ( isFixed ? 0 : Game::camera.x );
            destinationRectangle.y = static_cast<int>( transform->position.y ) - ( isFixed ? 0 : Game::camera.y );
            destinationRectangle.w = transform->width * transform->scale;
            destinationRectangle.h = transform->height * transform->scale;
        }

        void render() override {
            TextureManager::draw(texture, sourceTectangle, destinationRectangle, spriteFlip);
        }
};

#endif