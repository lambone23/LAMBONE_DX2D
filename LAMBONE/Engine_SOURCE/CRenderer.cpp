#include "CRenderer.h"
#include "CResources.h"
#include "CTexture.h"
#include "CMaterial.h"
#include "CStructedBuffer.h"
#include "CPaintShader.h"
#include "CParticleShader.h"

namespace renderer
{
	using namespace yha;
	using namespace yha::graphics;

	//Vertex vertexes[4] = {};
	yha::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	// Light
	std::vector<CLight*> lights = {};
	CStructedBuffer* lightsBuffer = nullptr;

	// Camera
	yha::CCamera* mainCamera = nullptr;
	std::vector<yha::CCamera*> cameras = {};
	
	// Collider
	std::vector<DebugMesh> debugMeshs = {};

	void FnSetupState()
	{
#pragma region InputLayout
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		// Material
		//CShader* shader = yha::CResources::FnFind<CShader>(L"TriangleShader");
		std::shared_ptr<CShader> shader = yha::CResources::FnFind<CShader>(L"TriangleShader");
		yha::graphics::FnGetDevice()->FnCreateInputLayout(
			arrLayout
			, 3
			, shader->FnGetVSCode()
			, shader->FnGetInputLayoutAddressOf());

		shader = yha::CResources::FnFind<CShader>(L"SpriteShader");
		yha::graphics::FnGetDevice()->FnCreateInputLayout(
			arrLayout
			, 3
			, shader->FnGetVSCode()
			, shader->FnGetInputLayoutAddressOf());

		shader = yha::CResources::FnFind<CShader>(L"GridShader");
		yha::graphics::FnGetDevice()->FnCreateInputLayout(
			arrLayout
			, 3
			, shader->FnGetVSCode()
			, shader->FnGetInputLayoutAddressOf());

		shader = yha::CResources::FnFind<CShader>(L"DebugShader");
		yha::graphics::FnGetDevice()->FnCreateInputLayout(
			arrLayout
			, 3
			, shader->FnGetVSCode()
			, shader->FnGetInputLayoutAddressOf());

		shader = yha::CResources::FnFind<CShader>(L"SpriteAnimationShader");
		yha::graphics::FnGetDevice()->FnCreateInputLayout(
			arrLayout
			, 3
			, shader->FnGetVSCode()
			, shader->FnGetInputLayoutAddressOf());

		shader = yha::CResources::FnFind<CShader>(L"ParticleShader");
		yha::graphics::FnGetDevice()->FnCreateInputLayout(
			arrLayout
			, 3
			, shader->FnGetVSCode()
			, shader->FnGetInputLayoutAddressOf());
#pragma endregion
#pragma region Sampler State
		// Sampler State
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

		// Sampler_Point
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		FnGetDevice()->FnCreateSamplerState(&desc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		FnGetDevice()->FnBindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		// Sampler_Anisotropic
		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		FnGetDevice()->FnCreateSamplerState(&desc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		FnGetDevice()->FnBindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		// Rasterizer State
		D3D11_RASTERIZER_DESC rasterizerDesc = {};

		// SolidBack
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		FnGetDevice()->FnCreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		// SolidFront
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		FnGetDevice()->FnCreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		// SolidNone
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		FnGetDevice()->FnCreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		// WireframeNone
		rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		FnGetDevice()->FnCreateRasterizeState(&rasterizerDesc, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		// Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

		// Less
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		FnGetDevice()->FnCreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::Less].GetAddressOf());

		// Greater
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.StencilEnable = false;
		FnGetDevice()->FnCreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::Greater].GetAddressOf());

		// NoWrite
		depthStencilDesc.DepthEnable = true;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		FnGetDevice()->FnCreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		// None
		depthStencilDesc.DepthEnable = false;
		depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		depthStencilDesc.StencilEnable = false;
		FnGetDevice()->FnCreateDepthStencilState(&depthStencilDesc, depthStencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		// Blend State
		D3D11_BLEND_DESC blendDesc = {};

		// default
		blendStates[(UINT)eBSType::Default] = nullptr;

		// Alpha Blend
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		FnGetDevice()->FnCreateBlendState(&blendDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		// one one
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		FnGetDevice()->FnCreateBlendState(&blendDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
#pragma endregion
	}//END-void FnSetupState

	void FnLoadMesh()
	{
		std::vector<Vertex> vertexes = {};
		std::vector<UINT> indexes = {};

		// PointMesh
		Vertex v = {};
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexes.push_back(v);
		indexes.push_back(0);
		std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
		mesh->FnCreateVertexBuffer(vertexes.data(), vertexes.size());
		mesh->FnCreateIndexBuffer(indexes.data(), indexes.size());
		CResources::FnInsert(L"PointMesh", mesh);

		vertexes.clear();
		indexes.clear();

		// RectMesh
		vertexes.resize(4);

		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		//==================================================================
		// Vertex Buffer
		//==================================================================
		//std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
		mesh = std::make_shared<CMesh>();
		CResources::FnInsert(L"RectMesh", mesh);
		mesh->FnCreateVertexBuffer(vertexes.data(), vertexes.size());

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		//==================================================================
		// Index Buffer
		//==================================================================
		mesh->FnCreateIndexBuffer(indexes.data(), indexes.size());

		//==================================================================
		// Rect Debug Mesh
		//==================================================================
		std::shared_ptr<CMesh> rectDebug = std::make_shared<CMesh>();
		CResources::FnInsert(L"DebugRect", rectDebug);
		rectDebug->FnCreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->FnCreateIndexBuffer(indexes.data(), indexes.size());

		for (int i = 0; i < vertexes.size(); ++i)
			vertexes[i].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		rectDebug = std::make_shared<CMesh>();
		CResources::FnInsert(L"DebugRedRect", rectDebug);
		//rectDebug->FnSetVertexes(vertexes);
		rectDebug->FnCreateVertexBuffer(vertexes.data(), vertexes.size());
		rectDebug->FnCreateIndexBuffer(indexes.data(), indexes.size());

		//==================================================================
		// Circle Debug Mesh
		//==================================================================
		vertexes.clear();
		indexes.clear();

		Vertex center = {};
		center.pos = Vector3(0.0f, 0.0f, 0.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes.push_back(center);

		int iSlice = 40;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (int i = 0; i < iSlice; ++i)
		{
			center.pos = Vector3(
				fRadius * cosf(fTheta * (float)i)
				, fRadius * sinf(fTheta * (float)i)
				, 0.0f);
			center.color = Vector4(0.0f, 1.0f, 0.0f, 1.f);
			vertexes.push_back(center);
		}

		//for (UINT i = 0; i < (UINT)iSlice; ++i)
		//{
		//	indexes.push_back(0);
		//	if (i == iSlice - 1)
		//	{
		//		indexes.push_back(1);
		//	}
		//	else
		//	{
		//		indexes.push_back(i + 2);
		//	}
		//	indexes.push_back(i + 1);
		//}

		for (int i = 0; i < vertexes.size() - 2; ++i)
		{
			indexes.push_back(i + 1);
		}

		indexes.push_back(1);

		std::shared_ptr<CMesh> circleDebug = std::make_shared<CMesh>();
		CResources::FnInsert(L"DebugCircle", circleDebug);
		circleDebug->FnCreateVertexBuffer(vertexes.data(), vertexes.size());
		circleDebug->FnCreateIndexBuffer(indexes.data(), indexes.size());
	}//END-void FnLoadMesh

	void FnLoadBuffer()
	{
		//==================================================================
		// Constant Buffer
		//==================================================================
		constantBuffer[(UINT)eCBType::Transform] = new CConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->FnCreate(sizeof(TransformCB));

		//==================================================================
		// Grid Buffer
		//==================================================================
		constantBuffer[(UINT)eCBType::Grid] = new CConstantBuffer(eCBType::Grid);
		constantBuffer[(UINT)eCBType::Grid]->FnCreate(sizeof(TransformCB));

		//==================================================================
		// Animator Buffer
		//==================================================================
		constantBuffer[(UINT)eCBType::Animator] = new CConstantBuffer(eCBType::Animator);
		constantBuffer[(UINT)eCBType::Animator]->FnCreate(sizeof(AnimatorCB));

		//==================================================================
		// ParticleCB
		//==================================================================
		constantBuffer[(UINT)eCBType::Particle] = new CConstantBuffer(eCBType::Particle);
		constantBuffer[(UINT)eCBType::Particle]->FnCreate(sizeof(ParticleCB));

		//==================================================================
		// NoiseCB
		//==================================================================
		constantBuffer[(UINT)eCBType::Noise] = new CConstantBuffer(eCBType::Noise);
		constantBuffer[(UINT)eCBType::Noise]->FnCreate(sizeof(NoiseCB));

		//==================================================================
		// Light Structed buffer
		//==================================================================
		lightsBuffer = new CStructedBuffer();
		lightsBuffer->FnCreate(sizeof(LightAttribute), 2, eViewType::SRV, nullptr, true);
	}//END-void FnLoadBuffer

	void FnLoadShader()
	{
		//yha::graphics::FnGetDevice()->FnCreateShader();

		//==================================================================
		// Triangle Shader
		//==================================================================
		//shader = new yha::CShader();
		//CShader* shader = new yha::CShader();
		std::shared_ptr<CShader> shader = std::make_shared<CShader>();
		shader->FnCreate(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->FnCreate(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		yha::CResources::FnInsert(L"TriangleShader", shader);

		//==================================================================
		// Sprite Shader
		//==================================================================
		//CShader* spriteShader = new yha::CShader();
		//std::shared_ptr<CShader> spriteShader = std::make_shared<CShader>();
		//spriteShader->FnCreate(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		//spriteShader->FnCreate(eShaderStage::PS, L"SpritePS.hlsl", "main");
		//yha::CResources::FnInsert(L"SpriteShader", spriteShader);
		shader = std::make_shared<CShader>();
		shader->FnCreate(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		shader->FnCreate(eShaderStage::PS, L"SpritePS.hlsl", "main");
		yha::CResources::FnInsert(L"SpriteShader", shader);

		//==================================================================
		// SpriteAnimation Shader
		//==================================================================
		std::shared_ptr<CShader> spriteAniShader = std::make_shared<CShader>();
		spriteAniShader->FnCreate(eShaderStage::VS, L"SpriteAnimationVS.hlsl", "main");
		spriteAniShader->FnCreate(eShaderStage::PS, L"SpriteAnimationPS.hlsl", "main");
		yha::CResources::FnInsert(L"SpriteAnimationShader", spriteAniShader);

		//==================================================================
		// Grid Shader
		//==================================================================
		std::shared_ptr<CShader> girdShader = std::make_shared<CShader>();
		girdShader->FnCreate(eShaderStage::VS, L"GridVS.hlsl", "main");
		girdShader->FnCreate(eShaderStage::PS, L"GridPS.hlsl", "main");
		yha::CResources::FnInsert(L"GridShader", girdShader);

		//==================================================================
		// Debug Shader
		//==================================================================
		std::shared_ptr<CShader> debugShader = std::make_shared<CShader>();
		debugShader->FnCreate(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->FnCreate(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->FnSetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		debugShader->FnSetRSState(eRSType::WireframeNone);
		//debugShader->FnSetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
		//debugShader->FnSetRSState(eRSType::SolidNone);
		//debugShader->SetDSState(eDSType::NoWrite);
		yha::CResources::FnInsert(L"DebugShader", debugShader);

		//==================================================================
		// Paint Shader
		//==================================================================
		std::shared_ptr<CPaintShader> paintShader = std::make_shared<CPaintShader>();
		paintShader->FnCreate(L"PaintCS.hlsl", "main");
		yha::CResources::FnInsert(L"PaintShader", paintShader);

		//==================================================================
		// Particle Shader
		//==================================================================
		std::shared_ptr<CParticleShader> psSystemShader = std::make_shared<CParticleShader>();
		psSystemShader->FnCreate(L"ParticleCS.hlsl", "main");
		yha::CResources::FnInsert(L"ParticleSystemShader", psSystemShader);
		
		std::shared_ptr<CShader> paritcleShader = std::make_shared<CShader>();
		paritcleShader->FnCreate(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		paritcleShader->FnCreate(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		paritcleShader->FnCreate(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		paritcleShader->FnSetRSState(eRSType::SolidNone);
		paritcleShader->FnSetDSState(eDSType::NoWrite);
		paritcleShader->FnSetBSState(eBSType::AlphaBlend);
		paritcleShader->FnSetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		yha::CResources::FnInsert(L"ParticleShader", paritcleShader);
	}//END-void FnLoadShader

	void FnLoadTexture()
	{
		//paint texture
		std::shared_ptr<CTexture> uavTexture = std::make_shared<CTexture>();
		uavTexture->FnCreate(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		yha::CResources::FnInsert(L"PaintTexuture", uavTexture);

		std::shared_ptr<CTexture> particle = std::make_shared<CTexture>();
		CResources::FnLoad<CTexture>(L"CartoonSmoke", L"..\\Resources\\particle\\CartoonSmoke.png");

		CResources::FnLoad<CTexture>(L"Noise01", L"..\\Resources\\noise\\noise_01.png");
		CResources::FnLoad<CTexture>(L"Noise02", L"..\\Resources\\noise\\noise_02.png");
		CResources::FnLoad<CTexture>(L"Noise03", L"..\\Resources\\noise\\noise_03.png");
	}//END-void LoadTexture

	void FnLoadMaterial()
	{
		//==================================================================
		// Shader
		//==================================================================
		// Sample - spriteShader
		//std::shared_ptr<CShader> spriteShader = CResources::FnFind<CShader>(L"SpriteShader");
		std::shared_ptr<CShader> shader = CResources::FnFind<CShader>(L"SpriteShader");
		
		// Animation적용 오브젝트 전용shader
		std::shared_ptr<CShader> SpriteAnimationShader = CResources::FnFind<CShader>(L"SpriteAnimationShader");

#pragma region Sample Resources
		//==================================================================
		// Sample Contents (spriteShader)
		//==================================================================
		//-------------------------------------
		// SpriteMaterial (Link)
		//-------------------------------------
		//CTexture* texture = CResources::FnLoad<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		//CMaterial* spriteMateiral = new yha::graphics::CMaterial();
		std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>();
		//material->FnSetShader(spriteShader);
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"SpriteMaterial", material);

		//-------------------------------------
		// SpriteMaterial02 (Smile)
		//-------------------------------------
		texture = CResources::FnLoad<CTexture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		//texture = CResources::FnFind<CTexture>(L"PaintTexuture");
		material = std::make_shared<CMaterial>();
		//material->FnSetShader(spriteShader);
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		material->FnSetRenderingMode(eRenderingMode::Transparent);
		CResources::FnInsert(L"SpriteMaterial02", material);

		//==================================================================
		// SpriteAnimation Shader
		//==================================================================
		SpriteAnimationShader = CResources::FnFind<CShader>(L"SpriteAnimationShader");
		//shader = CResources::FnFind<CShader>(L"SpriteAnimationShader");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(SpriteAnimationShader);
		//material->FnSetShader(shader);
		material->FnSetRenderingMode(eRenderingMode::Transparent);
		CResources::FnInsert(L"SpriteAnimaionMaterial", material);
#pragma endregion

		FnLoadMaterial_BG();
		FnLoadMaterial_UI();
		FnLoadMaterial_Cards();

		//==================================================================
		// grid Shader
		//==================================================================
		std::shared_ptr<CShader> gridShader = CResources::FnFind<CShader>(L"GridShader");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(gridShader);
		CResources::FnInsert(L"GridMaterial", material);

		//==================================================================
		// Debug Shader
		//==================================================================
		std::shared_ptr<CShader> debugShader = CResources::FnFind<CShader>(L"DebugShader");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(debugShader);
		CResources::FnInsert(L"DebugMaterial", material);

		//==================================================================
		// Particle Shader
		//==================================================================
		shader = CResources::FnFind<CShader>(L"ParticleShader");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetRenderingMode(eRenderingMode::Transparent);
		std::shared_ptr<CTexture> particleTexx = CResources::FnFind<CTexture>(L"CartoonSmoke");
		material->FnSetTexture(particleTexx);
		CResources::FnInsert(L"ParticleMaterial", material);
	}//END-void FnLoadMaterial

	void FnInitialize()
	{
		FnLoadMesh();
		FnLoadBuffer();
		FnLoadShader();
		FnSetupState();
		FnLoadTexture();
		FnLoadMaterial();

	}//END-void FnInitialize

	void FnPushDebugMeshAttribute(DebugMesh mesh)
	{
		debugMeshs.push_back(mesh);
	}//END-void FnPushDebugMeshAttribute

	void FnBindLights()
	{
		std::vector<LightAttribute> lightsAttributes = {};
		for (CLight* light : lights)
		{
			LightAttribute attribute = light->FnGetAttribute();
			lightsAttributes.push_back(attribute);
		}

		lightsBuffer->FnSetData(lightsAttributes.data(), lightsAttributes.size());
		lightsBuffer->FnBindSRV(eShaderStage::VS, 13);
		lightsBuffer->FnBindSRV(eShaderStage::PS, 13);
	}//END-void FnBindLights

	void FnBindNoiseTexture()
	{
		std::shared_ptr<CTexture> texture = CResources::FnFind<CTexture>(L"Noise01");

		texture->FnBindShaderResource(eShaderStage::VS, 15);
		texture->FnBindShaderResource(eShaderStage::HS, 15);
		texture->FnBindShaderResource(eShaderStage::DS, 15);
		texture->FnBindShaderResource(eShaderStage::GS, 15);
		texture->FnBindShaderResource(eShaderStage::PS, 15);
		texture->FnBindShaderResource(eShaderStage::CS, 15);

		CConstantBuffer* cb = constantBuffer[(UINT)eCBType::Noise];
		NoiseCB data = {};
		data.size.x = texture->FnGetWidth();
		data.size.y = texture->FnGetHeight();

		cb->FnSetData(&data);
		cb->FnBind(eShaderStage::VS);
		cb->FnBind(eShaderStage::GS);
		cb->FnBind(eShaderStage::PS);
		cb->FnBind(eShaderStage::CS);
	}//END-void FnBindNoiseTexture

	void FnRender()
	{
		FnBindNoiseTexture();
		FnBindLights();

		for (CCamera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->FnRender();
		}

		cameras.clear();
		lights.clear();
	}//END-void FnRender

	void FnRelease()
	{
		//delete mesh;
		//delete shader;
		//delete constantBuffer;

		for (CConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}

		delete lightsBuffer;
		lightsBuffer = nullptr;
	}//END-void FnRelease

	void FnLoadMaterial_BG()
	{
		//==================================================================
		// Shader
		//==================================================================
		std::shared_ptr<CShader> shader = CResources::FnFind<CShader>(L"SpriteShader");

		//==================================================================
		// 00_Title (SpriteShader)
		//==================================================================
		// Intro
		std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Intro", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_Intro.jpg");
		std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_Intro", material);

		// LoadingPage
		texture = CResources::FnLoad<CTexture>(L"LoadingPage", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_Loading.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_Loading", material);

		// MainMenu
		texture = CResources::FnLoad<CTexture>(L"MainMenu", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_MainMenu.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_MainMenu", material);

		// Ending_Win
		texture = CResources::FnLoad<CTexture>(L"Ending_Win", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_Ending_Win.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_Ending_Win", material);

		// Ending_Lose
		texture = CResources::FnLoad<CTexture>(L"Ending_Lose", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_Ending_Lose.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_Ending_Lose", material);

		//==================================================================
		// 01_PlayGrass (SpriteShader)
		//==================================================================
		// GrassDay
		texture = CResources::FnLoad<CTexture>(L"GrassDay", L"..\\Resources\\Texture\\MyGame\\BG\\01_PlayGrass\\Grassday.jpg");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_GrassDay", material);

		// GrassDay
		texture = CResources::FnLoad<CTexture>(L"GrassNight", L"..\\Resources\\Texture\\MyGame\\BG\\01_PlayGrass\\Grassnight.jpg");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_GrassNight", material);

		//==================================================================
		// 02_PlayPool (SpriteShader)
		//==================================================================
		// PoolDay
		texture = CResources::FnLoad<CTexture>(L"PoolDay", L"..\\Resources\\Texture\\MyGame\\BG\\02_PlayPool\\PVZBackground_7.jpg");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_PoolDay", material);

		// PoolNight
		texture = CResources::FnLoad<CTexture>(L"PoolNight", L"..\\Resources\\Texture\\MyGame\\BG\\02_PlayPool\\PVZBackground_8.jpg");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"BG_PoolNight", material);
	}//END-void FnLoadMaterial_BG

	void FnLoadMaterial_UI()
	{
		//==================================================================
		// Shader
		//==================================================================
		std::shared_ptr<CShader> shader = CResources::FnFind<CShader>(L"SpriteShader");

		//==================================================================
		// UI (SpriteShader)
		//==================================================================
		//-------------------------------------
		// Loading
		//-------------------------------------
		// Loading_Floor
		std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Loading_Floor", L"..\\Resources\\Texture\\MyGame\\UI\\Loading_Floor.png");
		std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Loading_Floor", material);

		// Loading_Grass
		texture = CResources::FnLoad<CTexture>(L"Loading_Grass", L"..\\Resources\\Texture\\MyGame\\UI\\Loading_Grass.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Loading_Grass", material);

		// Loading_Tag
		texture = CResources::FnLoad<CTexture>(L"Loading_Tag", L"..\\Resources\\Texture\\MyGame\\UI\\Loading_Tag.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Loading_Tag", material);

		//-------------------------------------
		// Play
		//-------------------------------------
		// SeedChooserBG
		texture = CResources::FnLoad<CTexture>(L"SeedChooserBG", L"..\\Resources\\Texture\\MyGame\\UI\\SeedChooserBG_edit.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_SeedChooserBG", material);

		// SelectedCardBG
		texture = CResources::FnLoad<CTexture>(L"SelectedCardBG", L"..\\Resources\\Texture\\MyGame\\Cards\\_EmptySpace.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_SelectedCardBG", material);

		// SunPointChk
		texture = CResources::FnLoad<CTexture>(L"SunPointChk", L"..\\Resources\\Texture\\MyGame\\UI\\SunPointChk.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_SunPointChk", material);

		// ShovelBG
		texture = CResources::FnLoad<CTexture>(L"ShovelBG", L"..\\Resources\\Texture\\MyGame\\UI\\ShovelBG.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_ShovelBG", material);

		// Shovel
		texture = CResources::FnLoad<CTexture>(L"Shovel", L"..\\Resources\\Texture\\MyGame\\UI\\Shovel.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Shovel", material);

		// FlagMeterEmpty
		texture = CResources::FnLoad<CTexture>(L"FlagMeterEmpty", L"..\\Resources\\Texture\\MyGame\\UI\\FlagMeterEmpty.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_FlagMeterEmpty", material);

		// FlagMeterParts_Zombie
		texture = CResources::FnLoad<CTexture>(L"FlagMeterParts_Zombie", L"..\\Resources\\Texture\\MyGame\\UI\\FlagMeterParts_Zombie.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_FlagMeterParts_Zombie", material);

		// FlagMeterParts_Flag
		texture = CResources::FnLoad<CTexture>(L"FlagMeterParts_Flag", L"..\\Resources\\Texture\\MyGame\\UI\\FlagMeterParts_Flag.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_FlagMeterParts_Flag", material);

		// SelectedCard
		texture = CResources::FnLoad<CTexture>(L"SelectedCard", L"..\\Resources\\Texture\\MyGame\\UI\\SelectedCard.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_SelectedCard", material);

		//==================================================================
		// UI Button (SpriteShader)
		//==================================================================
		//-------------------------------------
		// MainMenu
		//-------------------------------------
		// btn_StartAdventure_Original
		texture = CResources::FnLoad<CTexture>(L"btn_StartAdventure", L"..\\Resources\\Texture\\MyGame\\UI\\btn_StartAdventure_Original.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_btn_StartAdventure", material);

		// btn_StartAdventure_Hightlight
		texture = CResources::FnLoad<CTexture>(L"btn_StartAdventure_Hightlight", L"..\\Resources\\Texture\\MyGame\\UI\\btn_StartAdventure_Hightlight.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_btn_StartAdventure_Hightlight", material);

		// btn_StartAdventure_MouseOver
		texture = CResources::FnLoad<CTexture>(L"btn_StartAdventure_MouseOver", L"..\\Resources\\Texture\\MyGame\\UI\\btn_StartAdventure_MouseOver.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_btn_StartAdventure_MouseOver", material);

		//-------------------------------------
		// Play
		//-------------------------------------
		// btn_Play
		texture = CResources::FnLoad<CTexture>(L"btn_Play", L"..\\Resources\\Texture\\MyGame\\UI\\btn_Play.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_btn_Play", material);

		// btn_Play_Disabled
		texture = CResources::FnLoad<CTexture>(L"btn_Play_Disabled", L"..\\Resources\\Texture\\MyGame\\UI\\btn_Play_Disabled.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_btn_Play_Disabled", material);

		// btn_Menu
		texture = CResources::FnLoad<CTexture>(L"btn_Menu", L"..\\Resources\\Texture\\MyGame\\UI\\btn_Menu.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_btn_Menu", material);

		// btn_ResetChoose
		texture = CResources::FnLoad<CTexture>(L"btn_ResetChoose", L"..\\Resources\\Texture\\MyGame\\UI\\btn_ResetChoose.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_btn_ResetChoose", material);
	}//END-void FnLoadMaterial_UI

	void FnLoadMaterial_Cards()
	{
		//==================================================================
		// Shader
		//==================================================================
		std::shared_ptr<CShader> shader = CResources::FnFind<CShader>(L"SpriteShader");

		//==================================================================
		// Cards (SpriteShader)
		//==================================================================
		// Card_SunFlower
		std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"UI_SunFlower", L"..\\Resources\\Texture\\MyGame\\Cards\\SunFlower.png");
		std::shared_ptr<CMaterial> material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_SunFlower", material);

		// Card_SunFlower_Disabled
		texture = CResources::FnLoad<CTexture>(L"UI_SunFlower_Disabled", L"..\\Resources\\Texture\\MyGame\\Cards\\SunFlower_Disabled.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_SunFlower_Disabled", material);

		// Card_PeaShooter
		texture = CResources::FnLoad<CTexture>(L"UI_PeaShooter", L"..\\Resources\\Texture\\MyGame\\Cards\\PeaShooter.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_PeaShooter", material);

		// Card_PeaShooter_Disabled
		texture = CResources::FnLoad<CTexture>(L"UI_PeaShooter_Disabled", L"..\\Resources\\Texture\\MyGame\\Cards\\PeaShooter_Disabled.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_PeaShooter_Disabled", material);

		// Card_WallNut
		texture = CResources::FnLoad<CTexture>(L"UI_WallNut", L"..\\Resources\\Texture\\MyGame\\Cards\\WallNut.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_WallNut", material);

		// Card_WallNut_Disabled
		texture = CResources::FnLoad<CTexture>(L"UI_WallNut_Disabled", L"..\\Resources\\Texture\\MyGame\\Cards\\WallNut_Disabled.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_WallNut_Disabled", material);

		// Card_Chomper
		texture = CResources::FnLoad<CTexture>(L"UI_Chomper", L"..\\Resources\\Texture\\MyGame\\Cards\\Chomper.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_Chomper", material);

		// Card_Chomper_Disabled
		texture = CResources::FnLoad<CTexture>(L"UI_Chomper_Disabled", L"..\\Resources\\Texture\\MyGame\\Cards\\Chomper_Disabled.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_Chomper_Disabled", material);

		// Card_Jalapeno
		texture = CResources::FnLoad<CTexture>(L"UI_Jalapeno", L"..\\Resources\\Texture\\MyGame\\Cards\\Jalapeno.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_Jalapeno", material);

		// Card_Jalapeno_Disabled
		texture = CResources::FnLoad<CTexture>(L"UI_Jalapeno_Disabled", L"..\\Resources\\Texture\\MyGame\\Cards\\Jalapeno_Disabled.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_Jalapeno_Disabled", material);

		// Card_CherryBomb
		texture = CResources::FnLoad<CTexture>(L"UI_CherryBomb", L"..\\Resources\\Texture\\MyGame\\Cards\\CherryBomb.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_CherryBomb", material);

		// Card_CherryBomb_Disabled
		texture = CResources::FnLoad<CTexture>(L"UI_CherryBomb_Disabled", L"..\\Resources\\Texture\\MyGame\\Cards\\CherryBomb_Disabled.png");
		material = std::make_shared<CMaterial>();
		material->FnSetShader(shader);
		material->FnSetTexture(texture);
		CResources::FnInsert(L"UI_Card_CherryBomb_Disabled", material);

	}//END-void FnLoadMaterial_Cards
}
