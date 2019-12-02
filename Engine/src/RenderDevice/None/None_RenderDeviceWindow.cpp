#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "RenderDevice/None/None_RenderDeviceWindow.h"

None_RenderDeviceWindow::None_RenderDeviceWindow()
{
    width = 0;
    height = 0;
    vsync = true;
}

None_RenderDeviceWindow::~None_RenderDeviceWindow()
{
    //
}

void None_RenderDeviceWindow::Init(unsigned int _width, unsigned int _height, bool _vsyncEnabled)
{
    width = _width;
    height = _height;
    vsync = _vsyncEnabled;
}

void None_RenderDeviceWindow::BeginFrame()
{
    //
}

void None_RenderDeviceWindow::EndFrame()
{
    //
}

std::string None_RenderDeviceWindow::getWindowInfo()
{
    return "Please load a valid RenderDeviceWindow! No info available!";
}

bool None_RenderDeviceWindow::windowShouldClose()
{
    return false;
}

bool* None_RenderDeviceWindow::getMouseButtonsPressed()
{
    return new bool[3] {false, false, false};
}

Vector3f None_RenderDeviceWindow::getMousePosition()
{
    return Vector3f(0, 0, 0);
}

Vector3f None_RenderDeviceWindow::getWindowSize()
{
    return Vector3f(0, 0, 0);
}
