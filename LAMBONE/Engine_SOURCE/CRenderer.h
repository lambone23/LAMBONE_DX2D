#pragma once
#include "ZEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"
#include "CCamera.h"
#include "CLight.h"

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

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
		UINT animationType;
	};

	CBUFFER(ParticleCB, CBSLOT_PARTICLE)
	{
		UINT elementCount;
		float elapsedTime;
		float deltaTime;
		int padd2;
	};

	CBUFFER(NoiseCB, CBSLOT_NOISE)
	{
		Vector4 size;
	};

	//extern Vertex vertexes[];
	extern yha::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<yha::CLight*> lights;
	extern yha::CCamera* mainCamera;
	extern std::vector<yha::CCamera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void FnInitialize();
	void FnBindLights();
	void FnRender();
	void FnRelease();

	void FnPushDebugMeshAttribute(DebugMesh mesh);

	void FnLoadMaterial_LAMBONE();
	void FnLoadMaterial_BG();
	void FnLoadMaterial_UI();
	void FnLoadMaterial_Cards();
	void FnLoadMaterial_Plants();
}
