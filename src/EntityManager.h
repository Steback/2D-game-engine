#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "Component.h"
#include <vector>

class EntityManager {
    private:
        std::vector<Entity*> entities;

    public:
        ~EntityManager();
        void clearData();
        void update(float deltaTime);
        void render();
        bool hasNoEntities();
        Entity& addEntity(std::string entityName, LayerType _layer);
        std::vector<Entity*> getEntities() const;
        std::vector<Entity*> getEntitiesLayer(LayerType _layer) const;
        unsigned int getEntityCount() const;
        void listAllEntites() const;
        CollisionType checkCollisions() const;
        void destroyInactiveEntities();
};

#endif