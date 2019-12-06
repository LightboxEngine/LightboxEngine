#ifndef SCENE_H
#define SCENE_H
#include <map>
#include <string>
#include "GameObject.h"

class Scene
{
public:
    Scene();

    std::map<std::string, GameObject> gameObjects;
};

#endif // SCENE_H
