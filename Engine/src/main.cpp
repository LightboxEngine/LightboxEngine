#include <iostream>
#include <chrono>
#include "RenderDevice/OpenGL3/OpenGL3_RenderDevice.h"
#include "RenderDevice/OpenGL3/OpenGL3_RenderDeviceWindow.h"

void printFps()
{
    static std::chrono::high_resolution_clock::time_point lastTime = std::chrono::high_resolution_clock::now();
    static float fps;

    std::chrono::high_resolution_clock::time_point nowTime = std::chrono::high_resolution_clock::now();
    fps+=1.0f;
    if(std::chrono::duration_cast<std::chrono::microseconds>( nowTime - lastTime ).count() > 1000*1000)
    {
        std::cout << "FPS: " << fps << std::endl;
        //Gfps = fps;
        fps = 0;
        lastTime = std::chrono::high_resolution_clock::now();
    }
}

float randFloatNorm()
{
    return (((rand()%1000)/500.0f)-1.f)*((rand()%11 )/10.0f);
}

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
/////////////////////////
    float mX = (renderDeviceWindow->getMousePosition().x/(1920.0f/2.0f))-1;
    float mY = ((renderDeviceWindow->getMousePosition().y/(1080.0f/2.0f))-1)*-1;

    std::vector<float> vertices;
    std::vector<int> indices;
    float triangleV[] = {
        .0f+mX, .0f+mY, .0f,
        1.0f, 0.0f, 0.0f,

        0.3f+mX, 0.0f+mY, .0f,
        0.0f, 1.0f, 0.0f,

        0.3f+mX, 0.3f+mY, .0f,
        0.0f, 0.0f, 1.0f
    };
    vertices.insert(vertices.end(), std::begin(triangleV), std::end(triangleV));

    int off = 0;
    int triangleI[] = {
        0+off, 1+off, 2+off
    };
    indices.insert(indices.end(), std::begin(triangleI), std::end(triangleI));
    int triangleCount = 1000000;
    for (int i = 0; i < triangleCount; i++)
    {
        float triangleV[] = {
            randFloatNorm(), randFloatNorm(), randFloatNorm(),
            1.0f, 0.0f, 0.0f,

            randFloatNorm(), randFloatNorm(), randFloatNorm(),
            0.0f, 1.0f, 0.0f,

            randFloatNorm(), randFloatNorm(), randFloatNorm(),
            0.0f, 0.0f, 1.0f
        };
        vertices.insert(vertices.end(), std::begin(triangleV), std::end(triangleV));

        off = i*3;
        int triangleI[] = {
            0+off, 1+off, 2+off
        };
        indices.insert(indices.end(), std::begin(triangleI), std::end(triangleI));
    }

    RDVertexStructure structure;
    structure.add(0, 3, RD_FLOAT, true);
    structure.add(1, 3, RD_FLOAT, true);
    RDVertexBuffer *triangleVertices = renderDevice->createVertexBuffer(&vertices[0], vertices.size()*sizeof(float), structure);

    RDIndexBuffer *triangleIndices = renderDevice->createIndexBuffer(&indices[0], indices.size()*sizeof(float));
//////////////////////
    while(!renderDeviceWindow->windowShouldClose())
    {
        printFps();
        renderDeviceWindow->BeginFrame();
        renderDevice->BeginFrame();
        renderDevice->clearScreen(0.5f, 0.5f, 0.5f, 1);
        renderDevice->setRendererViewportSize(0, 0, renderDeviceWindow->getWindowSize().x, renderDeviceWindow->getWindowSize().y);
        renderDevice->enableFeature(RD_DEPTH_TEST);

        renderDevice->bindShaderProgram(default2DShader);
        renderDevice->bindVertexBuffer(triangleVertices);
        renderDevice->bindIndexBuffer(triangleIndices);
        renderDevice->drawIndexed(triangleCount*3, 0);

        //renderDevice->deleteVertexBuffer(triangleVertices);//////////////////////////
        //renderDevice->deleteIndexBuffer(triangleIndices);///////////////////////////

        renderDevice->EndFrame();
        renderDeviceWindow->EndFrame();
    }
}
