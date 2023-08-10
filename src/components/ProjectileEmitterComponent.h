#ifndef PROJECTILE_EMITTER_COMPONENT_H
#define PROJECTILE_EMITTER_COMPONENT_H

#include "glm/glm.hpp"
#include "../EntityManager.h"

class ProjectileEmitterComponent : public Component {
    private:
        TransformComponent* transfrom{};
        glm::vec2 origin{};
        int speed;
        int range;
        float angleRad;
        bool shotLoop;

    public:
        ProjectileEmitterComponent(int _speed, int _angleDeg, int _range, bool _shotLoop)
        : speed(_speed), range(_range), shotLoop(_shotLoop) {
            angleRad = glm::radians(static_cast<float>(_angleDeg));
        }

        void initialize() override {
            transfrom = owner->getComponent<TransformComponent>();
            origin = glm::vec2(transfrom->position.x, transfrom->position.y);
            transfrom->velocity = glm::vec2(glm::cos(angleRad) * static_cast<float>(speed), glm::sin(angleRad) * static_cast<float>(speed));
        }

        void update(float deltaTime) override {
            if ( glm::distance(transfrom->position, origin) > static_cast<float>(range) ) {
                if ( shotLoop ) {
                    transfrom->position.x = origin.x;
                    transfrom->position.y = origin.y;
                } else {
                    owner->destroy();
                }
            }
        }
};

#endif