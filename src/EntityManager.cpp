#include <iostream>
#include "EntityManager.h"
#include "Collision.h"
#include "components/ColliderComponent.h"

EntityManager::~EntityManager() {
    for ( auto & entity: entities ) {
        delete entity;
    }

    entities.clear();
}

void EntityManager::clearData() {
    for ( auto& entity : entities ) {
        entity->destroy();
    }
}

bool EntityManager::hasNoEntities() {
    return entities.empty();
}

void EntityManager::update(float deltaTime) {
    for ( auto& entity : entities ) {
        entity->update(deltaTime);
    }
}

void EntityManager::render() {
    for ( int layerNumber  = 0; layerNumber < NUM_LAYERS; layerNumber++ ) {
        for ( auto& entity : getEntitiesLayer( static_cast<LayerType>(layerNumber) ) ) {
            entity->render();
        }
    }
}

Entity& EntityManager::addEntity(std::string entityName, LayerType _layer) {
    auto* entity = new Entity(*this, std::move(entityName), _layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const { return entities; }

unsigned int EntityManager::getEntityCount() const { return entities.size(); }

std::vector<Entity *> EntityManager::getEntitiesLayer(LayerType _layer) const {
    std::vector<Entity*> selectedEntities;

    for ( auto& entity : entities ) {
        if ( entity->layer == _layer) {
            selectedEntities.emplace_back(entity);
        }
    }

    return selectedEntities;
}

void EntityManager::listAllEntites() const {
    unsigned int i = 0;

    for (auto& entity : entities ) {
        std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
        entity->listAllComponents();
        i++;
    }
}

std::string EntityManager::checkEntityCollisions(Entity& _entity) const {
    auto* entityCollider = _entity.getComponent<ColliderComponent>();

    for (auto& entity : entities ) {
        if ( entity->name != _entity.name && entity->name != "Tile" ) {
            if ( entity->hasComponent<ColliderComponent>() ) {
                auto* otherCollider = entity->getComponent<ColliderComponent>();

                if ( Collision::checkRectangleCollision(entityCollider->collider, otherCollider->collider) ) {
                    return otherCollider->colliderTag;
                }
            }
        }
    }

    return std::string();
}