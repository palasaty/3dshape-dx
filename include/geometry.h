#pragma once
#include "common.h"

using namespace DirectX;

struct SimpleVertex
{
	XMFLOAT3 pos;
	XMFLOAT3 normal;
	//XMFLOAT4 Color;
	SimpleVertex(FXMVECTOR  pos, FXMVECTOR  normal)
	{
		XMStoreFloat3(&this->pos, pos);
		XMStoreFloat3(&this->normal, normal);
	}
};

using VertexCollection = std::vector<SimpleVertex>;
using IndexCollection = std::vector<WORD>;

void computeCylinder(VertexCollection& v, IndexCollection& i, float d, float h, size_t n);