#include <iostream>
#include "RenderDevice/OpenGL/OpenGL_RenderDevice.h"
#include "RenderDevice/OpenGL/OpenGL_RenderDeviceWindow.h"

int main()
{
    std::cout << "main" << std::endl;

    RenderDeviceWindow *renderDeviceWindow = new OpenGL_RenderDeviceWindow();
    RenderDevice *renderDevice = new OpenGL3_RenderDevice();

    renderDeviceWindow->Init(1920, 1080, false);
    renderDevice->init();

    std::cout << "Renderer Info: " << renderDevice->getRenderDeviceInfo() << std::endl;

    while(!renderDeviceWindow->windowShouldClose())
    {
        renderDeviceWindow->BeginFrame();
        renderDevice->BeginFrame();



        renderDevice->EndFrame();
        renderDeviceWindow->EndFrame();
    }
}
