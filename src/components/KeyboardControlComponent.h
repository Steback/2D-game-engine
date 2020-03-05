#ifndef KEYBOARD_CONTROL_COMPONENT_H
#define KEYBOARD_CONTROL_COMPONENT_H

#include <utility>

#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardControlComponent : public Component {
    public:
        std::string upKey;
        std::string downKey;
        std::string rightKey;
        std::string leftKey;
        std::string shootKey;
        TransformComponent* tranform{};
        SpriteComponent* sprite{};

        KeyboardControlComponent() = default;

        KeyboardControlComponent(const std::string& _upKey, const std::string& _downKey, const std::string& _rightKey, const std::string& _leftKey, const std::string& _shootKey) {
            upKey = getSDLKeyStringCode(_upKey);
            downKey = getSDLKeyStringCode(_downKey);
            rightKey = getSDLKeyStringCode(_rightKey);
            leftKey = getSDLKeyStringCode(_leftKey);
            shootKey = getSDLKeyStringCode(_shootKey);
        }

        std::string getSDLKeyStringCode(const std::string& _key) {
            if ( _key == "up" ) return "1073741906";
            if ( _key == "down" ) return "1073741905";
            if ( _key == "left" ) return "1073741904";
            if ( _key == "right" ) return "1073741903";
            if ( _key == "space" ) return "32";
            return std::to_string( static_cast<int>( _key[0] ) );
        }

        void initialize() override {
            tranform = owner->getComponent<TransformComponent>();
            sprite = owner->getComponent<SpriteComponent>();
        }

        void update(float deltaTime) override {
            if ( Game::event.type == SDL_KEYDOWN ) {
                std::string keyCode = std::to_string( Game::event.key.keysym.sym );

                if ( keyCode == upKey ) {
                    sprite->play("UpAnimation");
                    tranform->velocity.y = -50;
                    tranform->velocity.x = 0;
                }
                if ( keyCode == rightKey ) {
                    sprite->play("RightAnimation");
                    tranform->velocity.x = 50;
                    tranform->velocity.y = 0;
                }
                if ( keyCode == downKey ) {
                    sprite->play("DownAnimation");
                    tranform->velocity.y = 50;
                    tranform->velocity.x = 0;

                }
                if ( keyCode == leftKey ) {
                    sprite->play("LeftAnimation");
                    tranform->velocity.x = -50;
                    tranform->velocity.y = 0;
                }
                if ( keyCode == shootKey ) {
                    // TODO: shot projectile whem 'shoot' key is pressed
                }
            }

            if ( Game::event.type == SDL_KEYUP ) {
                std::string keyCode = std::to_string( Game::event.key.keysym.sym );

                if ( keyCode == upKey ) {
                    tranform->velocity.y = 0;
                }
                if ( keyCode == rightKey ) {
                    tranform->velocity.x = 0;
                }
                if ( keyCode == downKey ) {
                    tranform->velocity.y = 0;
                }
                if ( keyCode == leftKey ) {
                    tranform->velocity.x = 0;
                }
                if ( keyCode == shootKey ) {
                    // TODO:
                }
            }
        }
};

#endif