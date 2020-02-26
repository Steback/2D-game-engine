#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

class Component {
    private:

    public:
        Entity* owner;
        virtual ~Component();
        virtual void initialize();
        virtual void update(floar deltaTime);
        virtual void Render();
};

#endif