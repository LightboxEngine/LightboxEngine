#ifndef BASERENDERER_H
#define BASERENDERER_H
#include <vector>
#include "MeshRenderObj.h"
#include "Canvas2DRenderObj.h"

class BaseRenderer
{
public:
    BaseRenderer();

    void renderFrame();
    void renderMesh(MeshRenderObj *obj);
    void renderCanvas2D(Canvas2DRenderObj *obj);

    std::vector<MeshRenderObj> meshList;
    std::vector<Canvas2DRenderObj> canvas2DList;
};

#endif // BASERENDERER_H
