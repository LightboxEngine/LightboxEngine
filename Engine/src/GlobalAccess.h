#ifndef GLOBALACCESS_H
#define GLOBALACCESS_H
#include "RenderDevice/RenderDevice.h"
#include "RenderDevice/RenderDeviceWindow.h"
#include "MessageSystem.h"

class GlobalAccess
{
public:
    static RenderDevice *renderDevice;
    static RenderDeviceWindow *renderDeviceWindow;
    static MessageSystem* messageSystem;
};

#endif // GLOBALACCESS_H
