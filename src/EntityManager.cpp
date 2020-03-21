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

    destroyInactiveEntities();
}

void EntityManager::destroyInactiveEntities() {
    for ( int i = 0; i < entities.size(); i++ ) {
        if ( !entities[i]->isActive() ) {
            entities.erase(entities.begin() + i);
        }
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

Entity* EntityManager::getEntityByName(std::string entityName) const {
    for (auto* entity: entities) {
        if (entity->name.compare(entityName) == 0) {
            return entity;
        }
    }
    return NULL;
}

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

CollisionType EntityManager::checkCollisions() const {
    for ( int i = 0; i < entities.size() - 1; i++ ) {
        auto& thisEntity = entities[i];

        if ( thisEntity->hasComponent<ColliderComponent>() ) {
            auto* thisCollider = thisEntity->getComponent<ColliderComponent>();

            for ( int j = i + 1; j < entities.size(); j++ ) {
                auto& thatEntity = entities[j];

                if ( thisEntity->name != thatEntity->name && thatEntity->hasComponent<ColliderComponent>() ) {
                    auto* thatCollider = thatEntity->getComponent<ColliderComponent>();

                    if ( Collision::checkRectangleCollision(thisCollider->collider, thatCollider->collider) ) {
                        if ( thisCollider->colliderTag == "PLAYER" && thatCollider->colliderTag == "ENEMY" ) {
                            return PLAYER_ENEMY_COLLISION;
                        }
                        if ( thisCollider->colliderTag == "PLAYER" && thatCollider->colliderTag == "PROJECTILE" ) {
                            return PLAYER_PROJECTILE_COLLISION;
                        }
                        if ( thisCollider->colliderTag == "ENEMY" && thatCollider->colliderTag == "FRIENDLY_PROJECTILE" ) {
                            return ENEMY_PROJECTILE_COLLISION;
                        }
                        if ( thisCollider->colliderTag == "PLAYER" && thatCollider->colliderTag == "LEVEL_COMPLETE" ) {
                            return PLAYER_LEVEL_COMPLETE_COLLISION;
                        }
                    }
                }
            }
        }
    }

    return NO_COLLISION;
}