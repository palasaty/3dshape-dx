#include "geometry.h"
#include <stdexcept>

void computeCap(VertexCollection& v, IndexCollection& i, size_t n, float h, float r, bool top);
void computeCapNew(VertexCollection& v, IndexCollection& ind, float r, float h, UINT n, bool top);
XMVECTOR computeCircleVector(size_t i, size_t n) noexcept;
XMVECTOR computeCircleTangent(size_t i, size_t tessellation) noexcept;

void computeCylinder(VertexCollection& v, IndexCollection& ind, float d, float h, size_t n) {
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
        const XMVECTOR normal = computeCircleVector(i, n);
        const XMVECTOR sideOffset = XMVectorScale(normal, radius);

        //const float u = float(i) / float(n);
        //const XMVECTOR textureCoordinate = XMLoadFloat(&u);

        v.emplace_back(XMVectorAdd(sideOffset, topOffset), normal/*, textureCoordinate*/);
        v.emplace_back(XMVectorSubtract(sideOffset, topOffset), normal/*, XMVectorAdd(textureCoordinate, g_XMIdentityR1)*/);

        ind.push_back(i*2);
        ind.push_back((i * 2 + 2) % (stride * 2));
        ind.push_back(i*2 + 1);

        ind.push_back(i * 2 + 1);
        ind.push_back((i * 2 + 2) % (stride * 2));
        ind.push_back((i * 2 + 3) % (stride * 2));
    }

    computeCap(v, ind, n, h, radius, true);
    computeCap(v, ind, n, h, radius, false);
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

void computeCap(VertexCollection& v, IndexCollection& ind, size_t n, float h, float r, bool top)
{
    for (size_t i = 0; i < n - 2; i++)
    {
        size_t i1 = (i + 1) % n;
        size_t i2 = (i + 2) % n;

        if (top)
            std::swap(i1, i2);

        const size_t vbase = v.size();
        ind.push_back(vbase);
        ind.push_back(vbase + i1);
        ind.push_back(vbase + i2);
    }

    XMVECTOR normal = g_XMIdentityR1;
    XMVECTOR textureScale = g_XMNegativeOneHalf;

    if (!top) {
        normal = XMVectorNegate(normal);
        textureScale = XMVectorMultiply(textureScale, g_XMNegateX);
    }


    for (size_t i = 0; i < n; i++)
    {
        const XMVECTOR circleVector = computeCircleVector(i, n);

        const XMVECTOR position = XMVectorAdd(XMVectorScale(circleVector, r), XMVectorScale(normal, h));

        //const XMVECTOR textureCoordinate = XMVectorMultiplyAdd(XMVectorSwizzle<0, 2, 3, 3>(circleVector), textureScale, g_XMOneHalf);

        v.emplace_back(position, normal/*, textureCoordinate*/ );
    }
}

void computeCylinderNew(VertexCollection& v, IndexCollection& ind, float d, float h, size_t n, size_t m)
{
	v.clear();
	ind.clear();

	float stackHeight = h / n;
	UINT mm = m + 1;
	const float r = d / 2;

	for (UINT i = 0; i < mm; ++i)
	{
		float y = -0.5f * h + i * stackHeight;

		float dTheta = 2.0f * XM_PI / n;
		for (UINT j = 0; j <= n; ++j)
		{
			float c = cosf(j * dTheta);
			float s = sinf(j * dTheta);

            XMFLOAT3 pos(r * c, y, r * s);
		    XMFLOAT3 tangentU(-s, 0.0f, c);
			XMFLOAT3 bitangent(0, -h, 0);

			XMVECTOR T = XMLoadFloat3(&tangentU);
			XMVECTOR B = XMLoadFloat3(&bitangent);
			XMVECTOR N = XMVector3Normalize(XMVector3Cross(T, B));

			v.emplace_back(XMLoadFloat3(&pos), N);
		}
	}

	UINT nn = n + 1;

	for (UINT i = 0; i < m; ++i)
	{
		for (UINT j = 0; j < n; ++j)
		{
			ind.push_back(i * nn + j);
			ind.push_back((i + 1) * nn + j);
			ind.push_back((i + 1) * nn + j + 1);

			ind.push_back(i * nn + j);
			ind.push_back((i + 1) * nn + j + 1);
			ind.push_back(i * nn + j + 1);
		}
	}

    computeCapNew(v, ind, r, h, n, true);
    computeCapNew(v, ind, r, h, n, false);
}

void computeCapNew(VertexCollection& v, IndexCollection& ind, float r, float h, UINT n, bool top) {

	UINT baseIndex = (UINT)v.size();
	float y = -0.5f * h;

	float dTheta = 2.0f * XM_PI / n;
	for (UINT i = 0; i <= n; ++i)
	{
		float x = r * cosf(i * dTheta);
		float z = r * sinf(i * dTheta);

        v.emplace_back(XMFLOAT3(x, y, z), XMFLOAT3(0, top ? 1 : -1, 0));
	}

    v.emplace_back(XMFLOAT3(0.0, y, 0.0), XMFLOAT3(0, top ? 1 : -1, 0));

	UINT centerIndex = (UINT)v.size() - 1;

	for (UINT i = 0; i < n; ++i)
	{
		ind.push_back(centerIndex);
        
        if (!top) {
            ind.push_back(baseIndex + i);
            ind.push_back(baseIndex + i + 1);
        }
        else {
            ind.push_back(baseIndex + i + 1);
            ind.push_back(baseIndex + i);
        }
	}
}