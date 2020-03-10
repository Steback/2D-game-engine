#ifndef COMPONENT_H
#define COMPONENT_H

#include "Entity.h"

class Entity;

class Component {
    private:

    public:
        Entity* owner{};
        virtual ~Component() = default;
        virtual void initialize() {  }
        virtual void update(float deltaTime) {  }
        virtual void render() {  }
};

#endif