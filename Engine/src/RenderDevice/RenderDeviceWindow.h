#pragma once
#include "Types/Vector2i.h"
#include <string>

class RenderDeviceWindow/// Window to render to, provides input functionality as well.
{
public:
    RenderDeviceWindow();
    ~RenderDeviceWindow();

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

private:
    unsigned int width, height;
    bool vsync;
};

