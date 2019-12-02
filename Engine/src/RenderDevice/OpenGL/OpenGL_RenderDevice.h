#pragma once
#include "RenderDevice/RenderDevice.h"
#include <vector>

class RD_OpenGL3_ShaderProgram : public RDShaderProgram
{
public:
    unsigned int shaderID;
};

class RD_OpenGL3_Texture2D : public RDTexture2D
{
public:
    unsigned int texID;
    RDTextureType texType;
};

class RD_OpenGL3_VertexBuffer : public RDVertexBuffer
{
public:
    unsigned int vbo;
};

class RD_OpenGL3_IndexBuffer : public RDIndexBuffer
{
public:
    unsigned int ibo;
};

class RD_OpenGL3_FrameBuffer : public RDFrameBuffer
{
public:
    unsigned int fbo;
};

class RD_OpenGL3_VertexStructure : public RDVertexStructure
{
public:
};

/// OpenGL 3.3 RenderDevice, contains everything needed for the Renderer to draw stuff.
class OpenGL3_RenderDevice : public RenderDevice
{
    void printShaderError(int ID);
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
    virtual bool bindFrameBuffer(RDFrameBuffer* buffer);
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
