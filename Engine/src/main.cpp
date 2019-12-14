#include <iostream>
#include "GlobalAccess.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDevice.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDeviceWindow.h"
#include "Renderer/BaseRenderer.h"
#include "FrameWork/Scene.h"

void printAllComponentChilds(Component *ptr, int index = 0)
{
    if (index == 0)
    {
        std::cout << "|-";
    }
    else
    {
        std::cout << "|";
        for(int i = 0; i < index; i++)
        {
            std::cout << " |";
        }
        std::cout << "-";
    }
    std::cout << "[Component]" << ptr->publicName << std::endl;

    for (int i = 0; i < ptr->components.size(); i++)
    {
        printAllComponentChilds(ptr->components[i].get(), index + 1);
    }
}

void printGameObjectChilds(GameObject *ptr, int index = 0)
{
    if (index == 0)
    {
        std::cout << "|-";
    }
    else
    {
        std::cout << "|";
        for(int i = 0; i < index; i++)
        {
            std::cout << " |";
        }
        std::cout << "-";
    }


    std::cout << "[GameObject]" << ptr->publicName << std::endl;
    for (int i = 0; i < ptr->gameobjects.size(); i++)
    {
        printGameObjectChilds(ptr->gameobjects[i].get(), index + 1);
        printAllComponentChilds(ptr->rootComponent.get(), index + 1);
    }
}

void printSceneChilds(Scene *ptr)
{
    printGameObjectChilds(ptr->rootGameObject.get());
}

int main()
{
    std::cout << "Lightbox Engine Compiled: " << __DATE__ << " " << __TIME__ << std::endl;
    MessageSystem *messageSystem = new MessageSystem();
    GlobalAccess::messageSystem = messageSystem;

    RenderDeviceWindow *renderDeviceWindow = new OpenGL3_RenderDeviceWindow();
    RenderDevice *renderDevice = new OpenGL3_RenderDevice();
    GlobalAccess::renderDevice = renderDevice;
    GlobalAccess::renderDeviceWindow = renderDeviceWindow;
    renderDeviceWindow->Init(1920, 1080, false);
    renderDevice->init();
    std::cout << "Renderer Info: " << renderDevice->getRenderDeviceInfo() << std::endl;

    BaseRenderer *baseRenderer = new BaseRenderer();
    GlobalAccess::baseRenderer = baseRenderer;

    Scene newScene;
    GameObject* newGameObjectInScene = newScene.rootGameObject->addNewGameObject("New GameObject");
    newGameObjectInScene->addNewComponent("New Component");
    newGameObjectInScene->addNewGameObject("Second GameObject");

    printSceneChilds(&newScene);

    while(!renderDeviceWindow->windowShouldClose())
    {
        renderDeviceWindow->BeginFrame();
        renderDevice->BeginFrame();
        renderDevice->clearScreen(0.5f, 0.5f, 0.5f, 1);
        renderDevice->setRendererViewportSize(0, 0, renderDeviceWindow->getWindowSize().x, renderDeviceWindow->getWindowSize().y);

        baseRenderer->renderFrame();

        renderDevice->EndFrame();
        renderDeviceWindow->EndFrame();
    }
}
