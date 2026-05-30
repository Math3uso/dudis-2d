#include "dudis2d/graphics/ddgl/render/renderDevice.h"

using namespace dudis;
using namespace ddgl;

bool DDRenderDevice::init()
{

    // _projectionType = ProjectionType::ORTHOGRAPHIC;
    _projection = glm::mat4(1.0f);
    _view = glm::mat4(1.0f);

    // _vert.reserve(DD_MAX_VERTEX);
    _vertRect.reserve(DD_MAX_VERTEX);
    _index.reserve(DD_MAX_INDEX);

    return true;
}