#include "geometry.h"
#include <stdexcept>

void computeCap(VertexCollection& v, IndexCollection& i, size_t n, float h, float r);
XMVECTOR computeCircleVector(size_t i, size_t n) noexcept;
XMVECTOR computeCircleTangent(size_t i, size_t tessellation) noexcept;

void computeCone(VertexCollection& v, IndexCollection& ind, float d, float h, size_t n) {
    v.clear();
    ind.clear();

    if (n < 3)
        throw std::invalid_argument("tesselation parameter must be at least 3");

    h /= 2;

    const XMVECTOR topOffset = XMVectorScale(g_XMIdentityR1, h);

    const float radius = d / 2;
    const size_t stride = n + 1;

    for (size_t i = 0; i <= n; i++)
    {
        const XMVECTOR circlevec = computeCircleVector(i, n);

        const XMVECTOR sideOffset = XMVectorScale(circlevec, radius);

        const float u = float(i) / float(n);

        const XMVECTOR textureCoordinate = XMLoadFloat(&u);

        const XMVECTOR pt = XMVectorSubtract(sideOffset, topOffset);

        XMVECTOR normal = XMVector3Cross(
            computeCircleTangent(i, n),
            XMVectorSubtract(topOffset, pt));
        normal = XMVector3Normalize(normal);

        v.emplace_back(topOffset, normal/* g_XMZero)*/);
        v.emplace_back( pt, normal  /*, XMVectorAdd(textureCoordinate, g_XMIdentityR1))*/);

        ind.push_back(i * 2);
        ind.push_back((i * 2 + 3) % (stride * 2));
        ind.push_back((i * 2 + 1) % (stride * 2));
    }

    computeCap(v, ind, n, h, radius);
}

inline XMVECTOR computeCircleTangent(size_t i, size_t n) noexcept
{
    const float angle = (float(i) * XM_2PI / float(n)) + XM_PIDIV2;
    float dx, dz;

    XMScalarSinCos(&dx, &dz, angle);

    const XMVECTORF32 v = { { { dx, 0, dz, 0 } } };
    return v;
}

inline XMVECTOR computeCircleVector(size_t i, size_t n) noexcept
{
    const float angle = float(i) * XM_2PI / float(n);
    float dx, dz;

    XMScalarSinCos(&dx, &dz, angle);

    const XMVECTORF32 v = { { { dx, 0, dz, 0 } } };
    return v;
}

void computeCap(VertexCollection& v, IndexCollection& ind, size_t n, float h, float r)
{
    for (size_t i = 0; i < n - 2; i++)
    {
        size_t i1 = (i + 1) % n;
        size_t i2 = (i + 2) % n;

        const size_t vbase = v.size();
        ind.push_back(vbase);
        ind.push_back(vbase + i1);
        ind.push_back(vbase + i2);
    }

    XMVECTOR normal = g_XMIdentityR1;
    XMVECTOR textureScale = g_XMNegativeOneHalf;

    normal = XMVectorNegate(normal);
    textureScale = XMVectorMultiply(textureScale, g_XMNegateX);


    for (size_t i = 0; i < n; i++)
    {
        const XMVECTOR circleVector = computeCircleVector(i, n);

        const XMVECTOR position = XMVectorAdd(XMVectorScale(circleVector, r), XMVectorScale(normal, h));

        //const XMVECTOR textureCoordinate = XMVectorMultiplyAdd(XMVectorSwizzle<0, 2, 3, 3>(circleVector), textureScale, g_XMOneHalf);

        v.emplace_back(position, normal/*, textureCoordinate*/ );
    }
}
