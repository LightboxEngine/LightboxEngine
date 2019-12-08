#include "BaseRenderer.h"

BaseRenderer::BaseRenderer()
{

}

void BaseRenderer::renderFrame()
{
    for (int i = 0; i < meshList.size(); i++)
    {
        renderMesh(&meshList[i]);
    }
    for (int i = 0; i < canvas2DList.size(); i++)
    {
        renderCanvas2D(&canvas2DList[i]);
    }
}

void BaseRenderer::renderMesh(MeshRenderObj *obj)
{

}

void BaseRenderer::renderCanvas2D(Canvas2DRenderObj *obj)
{

}
