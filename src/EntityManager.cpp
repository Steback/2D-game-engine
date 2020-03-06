#include <iostream>
#include "EntityManager.h"

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
    for ( auto& entity : entities ) {
        entity->render();
    }
}

Entity & EntityManager::addEntity(std::string entityName) {
    auto* entity = new Entity(*this, std::move(entityName));
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::getEntities() const { return entities; }

unsigned int EntityManager::getEntityCount() const { return entities.size(); }

void EntityManager::listAllEntites() const {
    unsigned int i = 0;

    for (auto& entity : entities ) {
        std::cout << "Entity[" << i << "]: " << entity->name << std::endl;
        entity->listAllComponents();
        i++;
    }
}