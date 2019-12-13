#include "GameObject.h"

GameObject::GameObject()
{
    markedForDeletion = false;
    parentComponent = 0;
    parentGameObject = 0;
}

void GameObject::deleteSelf()
{
    markedForDeletion = true;
}
