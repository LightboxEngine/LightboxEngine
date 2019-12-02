#pragma once
#include "RenderDevice/RenderDevice.h"

/// Empty RenderDevice, does absolutely nothing. Meant to be used as a server or other applications where a renderer isn't needed.
class None_RenderDevice : public RenderDevice
{

};
