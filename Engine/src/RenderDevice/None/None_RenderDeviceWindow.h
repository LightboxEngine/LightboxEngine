#pragma once
#include "Types/Vector3f.h"
#include <string>

class None_RenderDeviceWindow
{
public:
    None_RenderDeviceWindow();
    virtual ~None_RenderDeviceWindow();

    virtual void Init(unsigned int _width, unsigned int _height, bool _vsyncEnabled = true);
    virtual void BeginFrame();
    virtual void EndFrame();

    virtual std::string getWindowInfo();
    virtual bool windowShouldClose();
    virtual bool* getMouseButtonsPressed();
    virtual Vector3f getMousePosition();
    virtual Vector3f getWindowSize();

private:
    unsigned int width, height;
    bool vsync;
};

