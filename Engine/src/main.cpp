#include <iostream>
#include "GlobalAccess.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDevice.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDeviceWindow.h"

int main()
{
    std::cout << "main" << std::endl;

    RenderDeviceWindow *renderDeviceWindow = new OpenGL3_RenderDeviceWindow();
    RenderDevice *renderDevice = new OpenGL3_RenderDevice();
    GlobalAccess::renderDevice = renderDevice;
    GlobalAccess::renderDeviceWindow = renderDeviceWindow;
    renderDeviceWindow->Init(1920, 1080, false);
    renderDevice->init();

    std::cout << "Renderer Info: " << renderDevice->getRenderDeviceInfo() << std::endl;

    MessageSystem *messageSystem = new MessageSystem();
    GlobalAccess::messageSystem = messageSystem;

    while(!renderDeviceWindow->windowShouldClose())
    {
        renderDeviceWindow->BeginFrame();
        renderDevice->BeginFrame();
        renderDevice->clearScreen(0.5f, 0.5f, 0.5f, 1);
        renderDevice->setRendererViewportSize(0, 0, renderDeviceWindow->getWindowSize().x, renderDeviceWindow->getWindowSize().y);

        renderDevice->EndFrame();
        renderDeviceWindow->EndFrame();
    }
}
