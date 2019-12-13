#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <map>
#include <memory>
#include <vector>
#include "Component.h"

class GameObject
{
public:
    GameObject();

    void begin();///< Executed only once, when the object is created.
    void tick(float delta);///< Executed every frame, delta is in ms.

    std::string publicName;

    Component *parentComponent;
    GameObject *parentGameObject;

    bool markedForDeletion;
    void deleteSelf();///< This will cause this GameObject to be deleted at the next frame!

    std::map<std::string, std::shared_ptr<Component>> components;
    std::map<std::string, std::shared_ptr<GameObject>> gameobjects;

    std::vector<GameObject*> getAllChildGameObjects();
    std::vector<Component*> getAllChildComponents();

    GameObject* getChildGameObjectByName(std::string name);
    Component* getChildComponentByName(std::string name);
};

#endif // GAMEOBJECT_H
