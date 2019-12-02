#pragma once
#include "Math/Vector2i.h"
#include <string>
#include "RenderDevice/RenderDeviceWindow.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class OpenGL_RenderDeviceWindow : public RenderDeviceWindow
{
public:
    OpenGL_RenderDeviceWindow();
    ~OpenGL_RenderDeviceWindow();

    virtual void Init(unsigned int _width, unsigned int _height, bool _vsyncEnabled = true);
    virtual void BeginFrame();
    virtual void EndFrame();

    virtual std::string getWindowInfo();
    virtual bool windowShouldClose();
    virtual bool* getMouseButtonsPressed();
    virtual Vector2i getMousePosition();
    virtual Vector2i getWindowSize();
    virtual std::pair<int, bool> getKeyboardKeySingle();
    virtual std::pair<unsigned int, bool> getKeyboardCharSingle();

    int keyPressed;
    int keyReleased;

    unsigned int charPressed;
    bool pressed;

private:
    unsigned int width, height;
    bool vsync;

    GLFWwindow * GLFWGLwindow;
    static void glfwErrorCallback(int error, const char* description);
};

