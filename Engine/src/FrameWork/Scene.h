#ifndef SCENE_H
#define SCENE_H
#include <map>
#include <string>
#include "GameObject.h"

class Scene
{
public:
    Scene();

    std::unique_ptr<GameObject> rootGameObject;///< Root GameObject. Doesn't have any functionality, it just serves as a container for all objects in scene.
};

#endif // SCENE_H
