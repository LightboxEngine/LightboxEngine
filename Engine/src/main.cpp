#include <iostream>
#include "GlobalAccess.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDevice.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDeviceWindow.h"
#include "Renderer/BaseRenderer.h"
#include "FrameWork/Scene.h"

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
