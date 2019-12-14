#include "GameObject.h"

GameObject::GameObject()
{
    markedForDeletion = false;
    parentGameObject = 0;
    rootComponent = std::make_unique<Component>();
    rootComponent->publicName = "Root Component";
    initiated = false;
}

void GameObject::deleteSelf()
{
    markedForDeletion = true;
}

void GameObject::addGameObjectByPtr(GameObject *ptr)
{
    gameobjects.push_back(std::unique_ptr<GameObject>(ptr));
    gameobjects.back()->parentGameObject = this;
}

GameObject *GameObject::addNewGameObject(std::string publicName)
{
    gameobjects.push_back(std::make_unique<GameObject>());
    gameobjects.back()->publicName = publicName;
    gameobjects.back()->parentGameObject = this;

    return gameobjects.back().get();
}

void GameObject::addComponentByPtr(Component *ptr)
{
    rootComponent->components.push_back(std::unique_ptr<Component>(ptr));
    rootComponent->components.back()->parentComponent = rootComponent.get();
}

Component *GameObject::addNewComponent(std::string publicName)
{
    rootComponent->components.push_back(std::make_unique<Component>());
    rootComponent->components.back()->publicName = publicName;
    rootComponent->components.back()->parentComponent = rootComponent.get();

    return rootComponent->components.back().get();
}
