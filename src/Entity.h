#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "EntityManager.h"
#include "Component.h"

class Component;
class EntityManager;

class Entity {
    private:
        EntityManager& manager;
        bool isEntityActive;
        std::vector<Component*> components;

    public:
        std::string name;
        Entity(EntityManager& _manager);
        Entity(EntityManager& _manager, std::string _name);
        void update(float deltaTime);
        void render();
        void destroy();
        bool isActive() const;
};

#endif