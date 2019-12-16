#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <map>
#include <memory>
#include <vector>
#include "Component.h"
#include "Asset.h"

class GameObject : Asset
{
public:
    GameObject();

    void begin();///< Executed only once, when the object is created.
    void tick(float delta);///< Executed every frame, delta is in ms.

    bool initiated;

    std::string publicName;

    GameObject *parentGameObject;

    bool markedForDeletion;
    void deleteSelf();///< This will cause this GameObject to be deleted at the next frame!

    std::unique_ptr<Component> rootComponent;
    std::vector<std::unique_ptr<GameObject>> gameobjects;

    std::vector<GameObject*> getAllChildGameObjects();
    std::vector<Component*> getAllChildComponents();

    std::vector<GameObject*> getChildGameObjectByName(std::string name);
    std::vector<Component*> getChildComponentByName(std::string name);

    std::vector<GameObject*> getChildGameObjectByNameRecursive(std::string name);
    std::vector<Component*> getChildComponentByNameRecursive(std::string name);

    void addGameObjectByPtr(GameObject* ptr);///< This will add the provided GameObject as child to this GameObject. Doing this WILL take ownership of the GameObject provided.
    GameObject *addNewGameObject(std::string publicName);///< Add new child GameObject by name and return pointer to it.

    void addComponentByPtr(Component* ptr);///< This function will add the provided Component by pointer and name as child to this GameObject. This WILL take ownership of the Component.
    Component *addNewComponent(std::string publicName);///< Add new child Component to this GameObject and return the pointer to it.

};

#endif // GAMEOBJECT_H
