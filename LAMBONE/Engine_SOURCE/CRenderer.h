#pragma once
#include "ZEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"

using namespace yha::math;
using namespace yha::graphics;

namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	extern Vertex vertexes[];
	extern yha::CMesh* mesh;
	extern yha::CShader* shader;
	
	//extern yha::graphics::CConstantBuffer* constantBuffer;
	extern yha::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End];

	void FnInitialize();
	void FnRelease();
}
