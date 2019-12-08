#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <map>
#include "Component.h"

class GameObject
{
public:
    GameObject();

    void begin();///< Executed only once, when the object is created.
    void tick(float delta);///< Executed every frame, delta is in ms.

    Component *parentComponent;
    GameObject *parentGameObject;

    bool markedForDeletion;
    void deleteSelf();///< This will cause this GameObject to be deleted at the next frame!

    std::map<std::string, Component> components;
    std::map<std::string, GameObject> gameobjects;
};

#endif // GAMEOBJECT_H
