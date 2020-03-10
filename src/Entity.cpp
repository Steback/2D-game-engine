#include <iostream>
#include "Entity.h"

Entity::Entity(EntityManager &_manager) : manager(_manager) {
    isEntityActive = true;
}

Entity::Entity(EntityManager &_manager, std::string _name, LayerType _layer) : manager(_manager), name( std::move(_name) ), layer(_layer) {
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

void Entity::listAllComponents() const {
    for ( auto mapElement : componentTypeMap ) {
        std::cout << " Component<" << mapElement.first->name() << ">" << std::endl;
    }
}