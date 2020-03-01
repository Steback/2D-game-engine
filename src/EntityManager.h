#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "Component.h"
#include <vector>

class EntityManager {
    private:
        std::vector<Entity*> entities;

    public:
        void clearData();
        void update(float deltaTime);
        void render();
        bool hasNoEntities();
        Entity& addEntity(std::string entityName);
        std::vector<Entity*> getEntities() const;
        unsigned int getEntityCount() const;
        void listAllEntites() const;
};

#endif