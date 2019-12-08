#ifndef GLOBALACCESS_H
#define GLOBALACCESS_H
#include "RenderDevice/RenderDevice.h"
#include "RenderDevice/RenderDeviceWindow.h"
#include "MessageSystem.h"
#include "Renderer/BaseRenderer.h"

class GlobalAccess
{
public:
    static RenderDevice *renderDevice;
    static RenderDeviceWindow *renderDeviceWindow;
    static MessageSystem* messageSystem;
    static BaseRenderer* baseRenderer;
};

#endif // GLOBALACCESS_H
