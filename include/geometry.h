#pragma once
#include "common.h"

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	XMFLOAT4 Color;

	SimpleVertex() = default;
	SimpleVertex(FXMVECTOR  pos, FXMVECTOR  normal)
	{
		XMStoreFloat3(&this->pos, pos);
		XMStoreFloat3(&this->normal, normal);
		Color = {1, 0, 0, 0};
	}
	SimpleVertex(XMFLOAT3 p, XMFLOAT3 n) : pos(p), normal(n) {
		Color = { 1, 0, 0, 0 };
	}
};

using VertexCollection = std::vector<SimpleVertex>;
using IndexCollection = std::vector<WORD>;

void computeCylinder(VertexCollection& v, IndexCollection& i, float d, float h, size_t n);
void computeCylinderNew(VertexCollection& v, IndexCollection& ind, float d, float h, size_t n, size_t m);