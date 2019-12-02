#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "RenderDeviceWindow.h"

RenderDeviceWindow::RenderDeviceWindow()
{
    width = 0;
    height = 0;
    vsync = true;
}

RenderDeviceWindow::~RenderDeviceWindow()
{
    //
}

void RenderDeviceWindow::Init(unsigned int _width, unsigned int _height, bool _vsyncEnabled)
{
    width = _width;
    height = _height;
    vsync = _vsyncEnabled;
}

void RenderDeviceWindow::BeginFrame()
{
    //
}

void RenderDeviceWindow::EndFrame()
{
    //
}

std::string RenderDeviceWindow::getWindowInfo()
{
    return "Please load a valid RenderDeviceWindow! No info available!";
}

bool RenderDeviceWindow::windowShouldClose()
{
    return false;
}

bool* RenderDeviceWindow::getMouseButtonsPressed()
{
    return new bool[3] {false, false, false};
}

Vector2i RenderDeviceWindow::getMousePosition()
{
    return Vector2i(-1, -1);
}

Vector2i RenderDeviceWindow::getWindowSize()
{
    return Vector2i(-1, -1);
}

std::pair<int, bool> RenderDeviceWindow::getKeyboardKeySingle()
{
    return std::pair<int, bool>(-1, false);
}

std::pair<unsigned int, bool> RenderDeviceWindow::getKeyboardCharSingle()
{
    return std::pair<unsigned int, bool>(-1, false);
}
