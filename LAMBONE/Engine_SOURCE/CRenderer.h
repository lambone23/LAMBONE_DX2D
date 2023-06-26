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

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	extern Vertex vertexes[];
	extern yha::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	void FnInitialize();
	void FnRelease();
}
