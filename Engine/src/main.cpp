#include <iostream>
#include "RenderDevice/OpenGL3/OpenGL3_RenderDevice.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDeviceWindow.h"

int main()
{
    std::cout << "main" << std::endl;

    RenderDeviceWindow *renderDeviceWindow = new OpenGL3_RenderDeviceWindow();
    RenderDevice *renderDevice = new OpenGL3_RenderDevice();

    renderDeviceWindow->Init(1920, 1080, false);
    renderDevice->init();

    std::cout << "Renderer Info: " << renderDevice->getRenderDeviceInfo() << std::endl;

    std::cout << "Loading shader" << std::endl;
    RDShaderProgram *default2DShader = renderDevice->createShaderProgram("/home/tim/Documents/GitProjects/build-LightboxEngine-Desktop_Qt_5_11_2_GCC_64bit-Default/Shaders/default2D.f",
                                                                         "/home/tim/Documents/GitProjects/build-LightboxEngine-Desktop_Qt_5_11_2_GCC_64bit-Default/Shaders/default2D.v");

    float triangleV[] = {
        .0f, .0f, .0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, .0f,
        0.0f, 1.0f, 0.0f,

        1.0f, 1.0f, .0f,
        0.0f, 0.0f, 1.0f
    };
    int triangleI[] = {
        0, 1, 2
    };
    RDVertexStructure structure;
    structure.add(0, 3, RD_FLOAT, true);
    structure.add(1, 3, RD_FLOAT, true);
    RDVertexBuffer *triangleVertices = renderDevice->createVertexBuffer(&triangleV[0], sizeof(triangleV), structure);

    RDIndexBuffer *triangleIndices = renderDevice->createIndexBuffer(triangleI, sizeof(triangleI));

    while(!renderDeviceWindow->windowShouldClose())
    {
        renderDeviceWindow->BeginFrame();
        renderDevice->BeginFrame();
        renderDevice->clearScreen(0.5f, 0.5f, 0.5f, 1);

        renderDevice->bindShaderProgram(default2DShader);
        renderDevice->bindVertexBuffer(triangleVertices);
        renderDevice->bindIndexBuffer(triangleIndices);
        renderDevice->drawIndexed(3, 0);

        renderDevice->EndFrame();
        renderDeviceWindow->EndFrame();
    }
}
