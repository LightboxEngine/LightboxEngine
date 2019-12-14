#ifndef COMPONENT_H
#define COMPONENT_H
#include <string>
#include <vector>
#include <memory>

class Component
{
public:
    Component();

    void begin();
    void tick(float delta);

    bool initiated;

    std::string publicName;

    Component* parentComponent;
    std::vector<std::unique_ptr<Component>> components;

    void addComponentByPtr(Component* ptr);///< This function will add the provided Component by pointer as child to this Component. This WILL take ownership of the Component.
    Component *addNewComponent(std::string publicName);///< Add new child Component to this Component and return the pointer to it.
};

#endif // COMPONENT_H
