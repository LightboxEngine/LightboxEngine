#ifndef SCENE_H
#define SCENE_H
#include <map>
#include <string>
#include "GameObject.h"

class Scene
{
public:
    Scene();

    std::shared_ptr<GameObject> rootGameObject;
};

#endif // SCENE_H
