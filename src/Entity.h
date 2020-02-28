#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "EntityManager.h"
#include "Component.h"

class Component;
class EntityManager;

class Entity {
    private:
        EntityManager& manager;
        bool isEntityActive;
        std::vector<Component*> components;
        std::map<std::type_info*, Components*> componentTypeMap;

    public:
        std::string name;
        Entity(EntityManager& _manager);
        Entity(EntityManager& _manager, std::string _name);
        void update(float deltaTime);
        void render();
        void destroy();
        bool isActive() const;

        template <typename T, typename... Targs>
        T& addComponent(Targs&&... args) {
            T* newComponent( new T( std::forward<Targs>(args)... ) );

            newComponent->owner = this;
            components.emplace_back(newComponent);
            componentTypeMap[&typeid(*newComponent)] = newComponent;
            newComponent->initialize();

            return *newComponent;
        }

        template <typename T>
        T* getComponent() { return static_cast<T*>(componentTypeMap[&typeid(T)]); }
};

#endif