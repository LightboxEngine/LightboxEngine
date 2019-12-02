#pragma once
#include <string>
#include <vector>

enum RDTextureType
{
    RD_RGBA,///< RGBA 4 bytes/ 32bit total
    RD_RGB,///< RGB 4 bytes/32 bit total
    RD_DEPTHSTENCIL,///< DepthStencil Combined depth and stencil buffer, depth is 24bit and stencil is 8 bit. Total 4bytes/32bit.
    /*RD_ABGR,
    RD_BGR*/
};

enum RDVertexStructureType
{
    RD_FLOAT,
    RD_INT,
    RD_UINT,
    RD_BOOL,
    RD_BYTE,
    RD_UBYTE
};

enum RDEnableFeatures
{
    RD_DEPTH_TEST,
    RD_SCISSOR_TEST
};

class RDShaderProgram
{

};

class RDFrameBuffer
{

};

class RDVertexStructurePart
{
public:
    bool skip;
    unsigned int offset;
    unsigned int position;
    RDVertexStructureType type;
    unsigned int size;
    bool normalised;
};

class RDVertexStructure
{
public:
    RDVertexStructure()
    {
        totalSize = 0;
    }
    std::vector<RDVertexStructurePart> structure;
    unsigned int totalSize;
    virtual void add(unsigned int position, unsigned int size, RDVertexStructureType type, bool normalised);
    virtual void skip(unsigned int bytes);
};

class RDVertexBuffer
{
public:
    RDVertexStructure structure;
};

class RDIndexBuffer
{

};

class RDTexture2D
{

};

/// Class RenderDevice contains all needed features for the Renderer to draw things, this includes window creation and rendering functions.
class RenderDevice
{
public:
    virtual void init();

    virtual void BeginFrame();
    virtual void EndFrame();

    virtual std::string getRenderDeviceInfo();
    virtual std::string getRendererType();
    virtual bool isRendererInitialised();

    virtual RDShaderProgram* createShaderProgram(std::string fragmentPath, std::string vertexPath);
    virtual bool bindShaderProgram(RDShaderProgram* program);
    virtual void setShaderInt(RDShaderProgram *program, std::string varname, int val);
    virtual void setShaderMat4(RDShaderProgram *program, std::string varname, float* val);

    virtual RDTexture2D* createTexture2D(void* textureData, unsigned int size, unsigned int width, unsigned int height, RDTextureType type);
    virtual RDTexture2D* createEmptyTexture2D(unsigned int width, unsigned int height, RDTextureType type);
    virtual void useTexture2D(RDTexture2D* texture);
    virtual void deleteTexture2D(RDTexture2D* texture);

    virtual RDVertexBuffer* createVertexBuffer(void* vertexData, unsigned int size, RDVertexStructure structure);
    virtual RDIndexBuffer* createIndexBuffer(void* indexData, unsigned int size);
    virtual RDFrameBuffer* createFrameBuffer(RDTexture2D* colorBufferTex, RDTexture2D* depthBufferTex);
    virtual bool bindVertexBuffer(RDVertexBuffer* buffer);
    virtual bool bindIndexBuffer(RDIndexBuffer* buffer);
    virtual bool bindFrameBuffer(RDFrameBuffer* buffer);///< set buffer to 0 to render to main game window.
    virtual bool unbindVertexBuffer(RDVertexBuffer* buffer);
    virtual bool unbindIndexBuffer(RDIndexBuffer* buffer);
    virtual void deleteVertexBuffer(RDVertexBuffer* buffer);
    virtual void deleteIndexBuffer(RDIndexBuffer* buffer);
    virtual void deleteFrameBuffer(RDFrameBuffer* buffer);

    virtual void setScissorArea(int x, int y, int width, int height);///< Set scissor area in pixels.
    virtual void clearScreen(float r, float g, float b, float a);
    virtual void setRendererViewportSize(int x, int y, int w, int h);

    virtual void enableFeature(RDEnableFeatures feature);
    virtual void disableFeature(RDEnableFeatures feature);

    virtual void drawIndexed(unsigned int count, unsigned int offset);
};
