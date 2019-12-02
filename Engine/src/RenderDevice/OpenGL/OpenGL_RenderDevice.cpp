#include "OpenGL_RenderDevice.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <chrono>

void initVAO()
{
    static unsigned int vao = 0;
    if (vao == 0)
    {
        glGenVertexArrays(1, &vao);
    }
    glBindVertexArray(vao);
}

void OpenGL3_RenderDevice::printShaderError(int ID)
{
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(ID, 1024, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 1024, NULL, infoLog);
        std::cout << infoLog << std::endl;
    }
}

void OpenGL3_RenderDevice::init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);// Enable depth-testing so triangles that are further away then another triangle overlapping it are drawn behind it.

    //Enable alpha blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initVAO();
}

void OpenGL3_RenderDevice::BeginFrame()
{
}

void OpenGL3_RenderDevice::EndFrame()
{
}

std::string OpenGL3_RenderDevice::getRenderDeviceInfo()
{
    int majorVersion, minorVersion;
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

    return  std::string((char*)glGetString(GL_VENDOR)) + ", " +
            std::string((char*)glGetString(GL_RENDERER)) + ", " +
            std::string((char*)glGetString(GL_VERSION));

}

std::string OpenGL3_RenderDevice::getRendererType()
{
    return "OpenGL3";
}

bool OpenGL3_RenderDevice::isRendererInitialised()
{
    return true;
}

RDShaderProgram *OpenGL3_RenderDevice::createShaderProgram(std::string fragmentPath, std::string vertexPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        //DO nothing, for now.
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    printShaderError(vertex);
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    printShaderError(fragment);
    // shader Program
    unsigned int ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    RD_OpenGL3_ShaderProgram *newShaderProgram = new RD_OpenGL3_ShaderProgram();
    newShaderProgram->shaderID = ID;

    return newShaderProgram;
}

bool OpenGL3_RenderDevice::bindShaderProgram(RDShaderProgram *program)
{
    glUseProgram(static_cast<RD_OpenGL3_ShaderProgram*>(program)->shaderID);
    return true;
}

void OpenGL3_RenderDevice::setShaderInt(RDShaderProgram *program, std::string varname, int val)
{
    glUniform1i(glGetUniformLocation(static_cast<RD_OpenGL3_ShaderProgram*>(program)->shaderID, varname.c_str()), val);
}

void OpenGL3_RenderDevice::setShaderMat4(RDShaderProgram *program, std::string varname, float *val)
{
    glUniformMatrix4fv(glGetUniformLocation(static_cast<RD_OpenGL3_ShaderProgram*>(program)->shaderID, varname.c_str()), 1, GL_FALSE, val);
}

RDTexture2D *OpenGL3_RenderDevice::createTexture2D(void *textureData, unsigned int size, unsigned int width, unsigned int height, RDTextureType type)
{
    unsigned int texID = 0;

    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);// Bind texture
    switch(type)
    {
        case RD_RGBA:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
            break;
        case RD_RGB:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData);
            break;
        case RD_DEPTHSTENCIL:
            glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, textureData);
            break;
    }

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glGenerateMipmap(GL_TEXTURE_2D);

    RD_OpenGL3_Texture2D* newTexture2D = new RD_OpenGL3_Texture2D();

    newTexture2D->texType = type;
    newTexture2D->texID = texID;

    return newTexture2D;
}

RDTexture2D *OpenGL3_RenderDevice::createEmptyTexture2D(unsigned int width, unsigned int height, RDTextureType type)
{
    return createTexture2D(0, 0, width, height, type);
}

void OpenGL3_RenderDevice::useTexture2D(RDTexture2D *texture)
{
    glBindTexture(GL_TEXTURE_2D, static_cast<RD_OpenGL3_Texture2D*>(texture)->texID);
}

void OpenGL3_RenderDevice::deleteTexture2D(RDTexture2D *texture)
{
    glDeleteTextures(1, &static_cast<RD_OpenGL3_Texture2D*>(texture)->texID);

    delete texture;
}

RDVertexBuffer *OpenGL3_RenderDevice::createVertexBuffer(void *vertexData, unsigned int size, RDVertexStructure structure)
{
    unsigned int vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, vertexData, GL_STATIC_DRAW);

    RD_OpenGL3_VertexBuffer* newVertexBuffer = new RD_OpenGL3_VertexBuffer();
    newVertexBuffer->vbo = vbo;
    newVertexBuffer->structure = structure;
    return newVertexBuffer;
}

RDIndexBuffer *OpenGL3_RenderDevice::createIndexBuffer(void *indexData, unsigned int size)
{
    unsigned int ibo;

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexData, GL_STATIC_DRAW);

    RD_OpenGL3_IndexBuffer* newIndexBuffer = new RD_OpenGL3_IndexBuffer();
    newIndexBuffer->ibo = ibo;
    return newIndexBuffer;
}

RDFrameBuffer *OpenGL3_RenderDevice::createFrameBuffer(RDTexture2D *colorBufferTex, RDTexture2D *depthBufferTex)
{
    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ((RD_OpenGL3_Texture2D*)colorBufferTex)->texID, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, ((RD_OpenGL3_Texture2D*)depthBufferTex)->texID, 0);

    RD_OpenGL3_FrameBuffer *buffer = new RD_OpenGL3_FrameBuffer();
    buffer->fbo = fbo;

    return buffer;
}

bool OpenGL3_RenderDevice::bindVertexBuffer(RDVertexBuffer *buffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, static_cast<RD_OpenGL3_VertexBuffer*>(buffer)->vbo);

    /*for (int i = 0; i < 5; i++)
    {
        glDisableVertexAttribArray(i);
    }*/

    for (int i = 0; i < buffer->structure.structure.size(); i++)
    {
        int glType = GL_FLOAT;
        switch (buffer->structure.structure[i].type)
        {
            case RD_FLOAT:
                glType = GL_FLOAT;
                break;
            case RD_INT:
                glType = GL_INT;
                break;
            case RD_UINT:
                glType = GL_UNSIGNED_INT;
                break;
            case RD_BOOL:
                glType = GL_BOOL;
                break;
            case RD_BYTE:
                glType = GL_BYTE;
                break;
            case RD_UBYTE:
                glType = GL_UNSIGNED_BYTE;
                break;
        }

        RDVertexStructurePart part = buffer->structure.structure[i];
        glVertexAttribPointer(part.position, part.size, glType, part.normalised, buffer->structure.totalSize, (void*)part.offset);
        glEnableVertexAttribArray(part.position);
    }

    return true;
}

bool OpenGL3_RenderDevice::bindIndexBuffer(RDIndexBuffer *buffer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, static_cast<RD_OpenGL3_IndexBuffer*>(buffer)->ibo);
    return true;
}

bool OpenGL3_RenderDevice::bindFrameBuffer(RDFrameBuffer *buffer)
{
    if (buffer == 0)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, ((RD_OpenGL3_FrameBuffer*)buffer)->fbo);
    }
    return true;
}

bool OpenGL3_RenderDevice::unbindVertexBuffer(RDVertexBuffer *buffer)
{
    for (int i = 0; i < buffer->structure.structure.size(); i++)
    {
        RDVertexStructurePart part = buffer->structure.structure[i];
        glDisableVertexAttribArray(part.position);
    }

    return true;
}

bool OpenGL3_RenderDevice::unbindIndexBuffer(RDIndexBuffer *buffer)
{
    return true;
}

void OpenGL3_RenderDevice::deleteVertexBuffer(RDVertexBuffer *buffer)
{
    glDeleteBuffers(1, &static_cast<RD_OpenGL3_VertexBuffer*>(buffer)->vbo);

    delete buffer;
}

void OpenGL3_RenderDevice::deleteIndexBuffer(RDIndexBuffer *buffer)
{
    glDeleteBuffers(1, &static_cast<RD_OpenGL3_IndexBuffer*>(buffer)->ibo);

    delete buffer;
}

void OpenGL3_RenderDevice::deleteFrameBuffer(RDFrameBuffer *buffer)
{
    glDeleteFramebuffers(1, &((RD_OpenGL3_FrameBuffer*)buffer)->fbo);

    delete buffer;
}

void OpenGL3_RenderDevice::setScissorArea(int x, int y, int width, int height)
{
    glScissor(x, y, width, height);
}

void OpenGL3_RenderDevice::clearScreen(float r, float g, float b, float a)
{
    disableFeature(RD_SCISSOR_TEST);
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL3_RenderDevice::setRendererViewportSize(int x, int y, int w, int h)
{
    glViewport(x, y, w, h);
}

void OpenGL3_RenderDevice::enableFeature(RDEnableFeatures feature)
{
    switch (feature)
    {
        case RD_DEPTH_TEST:
            glEnable(GL_DEPTH_TEST);
            break;
        case RD_SCISSOR_TEST:
            glEnable(GL_SCISSOR_TEST);
            break;
    }
}

void OpenGL3_RenderDevice::disableFeature(RDEnableFeatures feature)
{
    switch (feature)
    {
        case RD_DEPTH_TEST:
            glDisable(GL_DEPTH_TEST);
            break;
        case RD_SCISSOR_TEST:
            glDisable(GL_SCISSOR_TEST);
            break;
    }
}

void OpenGL3_RenderDevice::drawIndexed(unsigned int count, unsigned int offset)
{
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)offset);
}
