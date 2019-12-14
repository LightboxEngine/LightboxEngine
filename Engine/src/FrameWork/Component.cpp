#include "Component.h"

Component::Component()
{
    parentComponent = 0;
}

void Component::addComponentByPtr(Component *ptr)
{
    components.push_back(std::unique_ptr<Component>(ptr));
    components.back()->parentComponent = this;
}

Component *Component::addNewComponent(std::string publicName)
{
    components.push_back(std::make_unique<Component>());
    components.back()->publicName = publicName;
    components.back()->parentComponent = this;

    return components.back().get();
}
