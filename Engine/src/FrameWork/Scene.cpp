#include "Scene.h"

Scene::Scene()
{
    rootGameObject = std::make_unique<GameObject>();
    rootGameObject->parentGameObject = 0;
    rootGameObject->publicName = "Root GameObject";
}
