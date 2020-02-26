#include "Entity.h"

Entity::Entity(EntityManager &_manager) : manager(_manager) {
    isEntityActive = true;
}

Entity::Entity(EntityManager &_manager, std::string _name) : manager(_manager), name(_name) {
    isEntityActive = true;
}

void Entity::update(float deltaTime) {
    for ( auto& component : components ) {
        component->update(deltaTime);
    }
}

void Entity::render() {
    for ( auto& component : components ) {
        component->render();
    }
}

void Entity::destroy() {
    isEntityActive = false;
}

bool Entity::isActive() const { return isEntityActive; }