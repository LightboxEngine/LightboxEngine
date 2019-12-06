#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <map>
#include "Component.h"

class GameObject
{
public:
    GameObject();

    void begin();
    void tick(float delta);

    std::map<std::string, Component> components;
};

#endif // GAMEOBJECT_H
