#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "RenderDevice/OpenGL/OpenGL_RenderDeviceWindow.h"

#include "Math/Vector2i.h"

OpenGL_RenderDeviceWindow::OpenGL_RenderDeviceWindow()
{
    width = 0;
    height = 0;
    vsync = true;
}

OpenGL_RenderDeviceWindow::~OpenGL_RenderDeviceWindow()
{
    //
}

void glfwInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << "Need to implement glfwInputCallback or find a different methode for input." << std::endl;
}

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
    std::cout << "Need to implement character_callback or find a different methode for input." << std::endl;
}

void OpenGL_RenderDeviceWindow::Init(unsigned int _width, unsigned int _height, bool _vsyncEnabled)
{
    width = _width;
    height = _height;
    vsync = _vsyncEnabled;

    keyPressed = -1;
    keyReleased = -1;

    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit())
    {
        std::cout << "glfwInit failed in OpenGL_RenderDeviceInfo!";
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWGLwindow = glfwCreateWindow(width, height, "Engine", NULL, NULL);
    glfwMakeContextCurrent(GLFWGLwindow);
    glfwSwapInterval(vsync); // Enable vsync
    glfwSetKeyCallback(GLFWGLwindow, glfwInputCallback);
    glfwSetCharCallback(GLFWGLwindow, character_callback);
    /*GLFWimage icons[1];

    icons[0].pixels = AssetImport::loadTextureFromFile(FileSystem::GetAssetDir() + std::string("/logo_64.png"), 4);
    icons[0].width = 64;
    icons[0].height = 64;
    glfwSetWindowIcon(GLFWGLwindow, 1, icons);*/ ///Todo
    /*if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);// Enable depth-testing so triangles that are further away then another triangle overlapping it are drawn behind it.

    //Enable alpha blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
}

void OpenGL_RenderDeviceWindow::BeginFrame()
{
    glfwMakeContextCurrent(GLFWGLwindow);
    glfwPollEvents();

    int _width, _height;
    glfwGetWindowSize(GLFWGLwindow, &_width, &_height);
    width = _width;
    height = _height;
}

void OpenGL_RenderDeviceWindow::EndFrame()
{
    glfwSwapBuffers(GLFWGLwindow);
}

std::string OpenGL_RenderDeviceWindow::getWindowInfo()
{
    return "Please load a valid RenderDeviceWindow! No info available!";
}

bool OpenGL_RenderDeviceWindow::windowShouldClose()
{
    return glfwWindowShouldClose(GLFWGLwindow);
}

bool* OpenGL_RenderDeviceWindow::getMouseButtonsPressed()
{
    return new bool[3] {
            (bool)glfwGetMouseButton(GLFWGLwindow, GLFW_MOUSE_BUTTON_LEFT),
            (bool)glfwGetMouseButton(GLFWGLwindow, GLFW_MOUSE_BUTTON_MIDDLE),
            (bool)glfwGetMouseButton(GLFWGLwindow, GLFW_MOUSE_BUTTON_RIGHT)
};
}

Vector2i OpenGL_RenderDeviceWindow::getMousePosition()
{
    double xpos, ypos;
    glfwGetCursorPos(GLFWGLwindow, &xpos, &ypos);
    return Vector2i(xpos, ypos);
}

Vector2i OpenGL_RenderDeviceWindow::getWindowSize()
{
    return Vector2i(width, height);
}

std::pair<int, bool> OpenGL_RenderDeviceWindow::getKeyboardKeySingle()
{
    if (keyPressed != -1)
    {
        return std::pair<int, bool>(keyPressed, true);
    }
    else if (keyReleased != -1)
    {
        return std::pair<int, bool>(keyReleased, false);
    }
    return std::pair<int, bool>(-1, false);
}

std::pair<unsigned int, bool> OpenGL_RenderDeviceWindow::getKeyboardCharSingle()
{
    if (pressed == true)
    {
        pressed = false;
        return std::pair<unsigned int, bool>(charPressed, true);
    }
    else {
        return std::pair<unsigned int, bool>(charPressed, pressed);
    }
}

void OpenGL_RenderDeviceWindow::glfwErrorCallback(int error, const char* description)
{
    std::cout << "GLFW ERROR: " << error << ", " << description << std::endl;
}
