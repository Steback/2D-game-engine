#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "Constants.h"
#include "EntityManager.h"
#include "Component.h"

class EntityManager;

class Entity {
    private:
        EntityManager& manager;
        bool isEntityActive;
        std::vector<Component*> components;
        std::map<const std::type_info*, Component*> componentTypeMap;

    public:
        std::string name;
        LayerType layer;
        Entity(EntityManager& _manager);
        Entity(EntityManager& _manager, std::string _name, LayerType _layer);
        ~Entity();
        void update(float deltaTime);
        void render();
        void destroy();
        bool isActive() const;
        void listAllComponents() const;

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
        bool hasComponent() const { return componentTypeMap.count( &typeid(T) ); };

        template <typename T>
        T* getComponent() { return static_cast<T*>(componentTypeMap[&typeid(T)]); }
};

#endif