#pragma once
#include "ZEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"

using namespace yha::math;
namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	extern Vertex vertexes[];
	extern yha::CMesh* mesh;
	extern yha::CShader* shader;
	extern yha::graphics::CConstantBuffer* constantBuffer;

	void FnInitialize();
	void FnRelease();
}
