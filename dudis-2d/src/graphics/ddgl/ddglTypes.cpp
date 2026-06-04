#include <cmath>
#include "dudis2d/graphics/ddgl/ddglTypes.h"
#include "dudis2d/core/math/rect.h"

using namespace dudis;
using namespace ddgl;

void ddgl::transformQuadV3FC4B(const DDTransform2D &transform, std::vector<DDVertexV3FC4B> &quad)
{
    float cosR = cosf(transform.rotation);
    float sinR = sinf(transform.rotation);

    float skewX = tanf(transform.skewX); // radianos
    float skewY = tanf(transform.skewY); // radianos

    for (auto &vertex : quad)
    {
        float localX = vertex.x - transform.origin.x;
        float localY = vertex.y - transform.origin.y;

        // scale
        float x = localX * transform.scale.x;
        float y = localY * transform.scale.y;

        // skew
        float skewedX = x + y * skewX;
        float skewedY = y + x * skewY;

        // rotation
        float rotatedX = skewedX * cosR - skewedY * sinR;
        float rotatedY = skewedX * sinR + skewedY * cosR;

        // translate
        vertex.x = rotatedX + transform.origin.x + transform.position.x;
        vertex.y = rotatedY + transform.origin.y + transform.position.y;
    }
}

void ddgl::transformDDVertex(const DDTransform2D &transform, VertexQuadDataTextured &vertexData, bool replacePos)
{
    // float cosR = cosf(transform.rotation);
    // float sinR = sinf(transform.rotation);

    // for (auto &vertex : vertexData.vertices)
    // {
    //     float localX = vertex.x - transform.origin.x;
    //     float localY = vertex.y - transform.origin.y;

    //     // Aplicar escala
    //     float x = localX * transform.scale.x;
    //     float y = localY * transform.scale.y;

    //     // Aplicar rotação
    //     float rotatedX = x * cosR - y * sinR;
    //     float rotatedY = x * sinR + y * cosR;

    //     // Retornar do pivô local e aplicar translação
    //     vertex.x = rotatedX + transform.origin.x + transform.position.x;
    //     vertex.y = rotatedY + transform.origin.y + transform.position.y;
    // }

    float cosR = cosf(transform.rotation);
    float sinR = sinf(transform.rotation);

    float skewX = tanf(transform.skewX); // radianos
    float skewY = tanf(transform.skewY); // radianos

    for (auto &vertex : vertexData.vertices)
    {
        float vertexX = replacePos ? vertex.x - vertexData._pos.x : vertex.x;
        float vertexY = replacePos ? vertex.y - vertexData._pos.y : vertex.y;

        float localX = vertexX - transform.origin.x;
        float localY = vertexY - transform.origin.y;

        // scale
        float x = localX * transform.scale.x;
        float y = localY * transform.scale.y;

        // skew
        float skewedX = x + y * skewX;
        float skewedY = y + x * skewY;

        // rotation
        float rotatedX = skewedX * cosR - skewedY * sinR;
        float rotatedY = skewedX * sinR + skewedY * cosR;

        // translate
        if (replacePos)
        {
            vertex.x = rotatedX + transform.position.x;
            vertex.y = rotatedY + transform.position.y;
        }
        else
        {
            vertex.x = rotatedX + transform.origin.x + transform.position.x;
            vertex.y = rotatedY + transform.origin.y + transform.position.y;
        }
    }

    if (!vertexData.vertices.empty())
    {
        vertexData._pos = Vec2{vertexData.vertices.front().x, vertexData.vertices.front().y};
    }
}

VertexQuadDataTextured ddgl::createQuadData(const SizeF &size, const Vec2 &pos, const Rect &rect, uint32_t color, ddgl::DDTexture2D img)
{
    VertexQuadDataTextured quadData;

    float u0 = rect.x / img.width;
    float v0 = rect.y / img.height;
    float u1 = (rect.x + rect.w) / img.width;
    float v1 = (rect.y + rect.h) / img.height;

    float x0 = pos.x;
    float y0 = pos.y;

    float x1 = pos.x + size.w;
    float y1 = pos.y + size.h;

    quadData.vertices.push_back({x0, y0, u0, v0, color});
    quadData.vertices.push_back({x1, y0, u1, v0, color});
    quadData.vertices.push_back({x1, y1, u1, v1, color});
    quadData.vertices.push_back({x0, y1, u0, v1, color});
    quadData.indices.push_back(0);
    quadData.indices.push_back(1);
    quadData.indices.push_back(2);
    quadData.indices.push_back(2);
    quadData.indices.push_back(3);
    quadData.indices.push_back(0);

    quadData.textureId = img.id;

    quadData._size = size;
    quadData._pos = pos;

    return quadData;
}
