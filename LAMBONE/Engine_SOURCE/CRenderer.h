#pragma once
#include "ZEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"
#include "CCamera.h"

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

	CBUFFER(GridCB, CBSLOT_GRID)
	{
		Vector4 CameraPosition;
		Vector2 CameraScale;
		Vector2 Resolution;
	};

	extern Vertex vertexes[];
	extern yha::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<yha::CCamera*> cameras;

	void FnInitialize();
	void FnRender();
	void FnRelease();
}
