#include "GameObject.h"

GameObject::GameObject()
{
    markedForDeletion = false;
}

void GameObject::deleteSelf()
{
    markedForDeletion = true;
}
