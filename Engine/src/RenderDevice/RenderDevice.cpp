#include "RenderDevice.h"

void RenderDevice::init()
{
    //
}

void RenderDevice::BeginFrame()
{
    //
}

void RenderDevice::EndFrame()
{
    //
}

std::string RenderDevice::getRenderDeviceInfo()
{
    return "Renderer not loaded, getRendererDeviceInfo not available!";
}

std::string RenderDevice::getRendererType()
{
    return "Renderer not loaded, getRendererType unavailable!";
}

bool RenderDevice::isRendererInitialised()
{
    return false;
}

RDShaderProgram *RenderDevice::createShaderProgram(std::string fragmentPath, std::string vertexPath)
{
    return 0;
}

bool RenderDevice::bindShaderProgram(RDShaderProgram *program)
{
    return false;
}

void RenderDevice::setShaderInt(RDShaderProgram *program, std::string varname, int val)
{

}

void RenderDevice::setShaderMat4(RDShaderProgram *program, std::string varname, float *val)
{

}

RDTexture2D *RenderDevice::createTexture2D(void *textureData, unsigned int size, unsigned int width, unsigned int height, RDTextureType type)
{
    return 0;
}

RDTexture2D *RenderDevice::createEmptyTexture2D(unsigned int width, unsigned int height, RDTextureType type)
{
    return 0;
}

void RenderDevice::useTexture2D(RDTexture2D *texture)
{

}

void RenderDevice::deleteTexture2D(RDTexture2D *texture)
{

}

RDVertexBuffer *RenderDevice::createVertexBuffer(void *vertexData, unsigned int size, RDVertexStructure structure)
{
    return 0;
}

RDIndexBuffer *RenderDevice::createIndexBuffer(void *indexData, unsigned int size)
{
    return 0;
}

RDFrameBuffer *RenderDevice::createFrameBuffer(RDTexture2D *colorBufferTex, RDTexture2D *depthBufferTex)
{
    return 0;
}

bool RenderDevice::bindVertexBuffer(RDVertexBuffer *buffer)
{
    return false;
}

bool RenderDevice::bindIndexBuffer(RDIndexBuffer *buffer)
{
    return false;
}

bool RenderDevice::bindFrameBuffer(RDFrameBuffer *buffer)
{
    return true;
}

bool RenderDevice::unbindVertexBuffer(RDVertexBuffer *buffer)
{
    return true;
}

bool RenderDevice::unbindIndexBuffer(RDIndexBuffer *buffer)
{
    return true;
}

void RenderDevice::deleteVertexBuffer(RDVertexBuffer *buffer)
{

}

void RenderDevice::deleteIndexBuffer(RDIndexBuffer *buffer)
{

}

void RenderDevice::deleteFrameBuffer(RDFrameBuffer *buffer)
{

}

void RenderDevice::setScissorArea(int x, int y, int width, int height)
{

}

void RenderDevice::clearScreen(float r, float g, float b, float a)
{

}

void RenderDevice::setRendererViewportSize(int x, int y, int w, int h)
{

}

void RenderDevice::enableFeature(RDEnableFeatures feature)
{

}

void RenderDevice::disableFeature(RDEnableFeatures feature)
{

}

void RenderDevice::drawIndexed(unsigned int count, unsigned int offset)
{

}

void RDVertexStructure::add(unsigned int position, unsigned int size, RDVertexStructureType type, bool normalised)
{
    RDVertexStructurePart newPart;
    newPart.offset = totalSize;
    newPart.skip = false;
    newPart.position = position;
    newPart.type = type;
    newPart.size = size;
    newPart.normalised = normalised;

    structure.push_back(newPart);

    int typeSize = 0;

    switch (type)
    {
        case RD_FLOAT:
            typeSize = sizeof(float);
            break;
        case RD_INT:
            typeSize = sizeof(int);
            break;
        case RD_UINT:
            typeSize = sizeof(unsigned int);
            break;
        case RD_BOOL:
            typeSize = sizeof(bool);
            break;
        case RD_BYTE:
            typeSize = sizeof(char);
            break;
        case RD_UBYTE:
            typeSize = sizeof(unsigned char);
            break;
    }

    totalSize += size*typeSize;
    /*switch (type)
    {
        case RD_FLOAT: totalSize += size*sizeof(float);
        case RD_INT: totalSize += size*sizeof(int);
        case RD_UINT: totalSize += size*sizeof(unsigned int);
        case RD_BOOL: totalSize += size*sizeof(bool);
        case RD_BYTE: totalSize += size*sizeof(char);
        case RD_UBYTE: totalSize += size*sizeof(unsigned char);
    }*/
}

void RDVertexStructure::skip(unsigned int bytes)
{
    RDVertexStructurePart newPart;
    newPart.skip = true;
    newPart.size = bytes;

    totalSize += bytes;

    structure.push_back(newPart);
}
