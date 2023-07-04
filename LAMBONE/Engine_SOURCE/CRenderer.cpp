#include "CRenderer.h"
#include "CResources.h"
#include "CTexture.h"
#include "CMaterial.h"

namespace renderer
{
	using namespace yha;
	using namespace yha::graphics;

	Vertex vertexes[4] = {};

	yha::graphics::CConstantBuffer* constantBuffer[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	std::vector<yha::CCamera*> cameras = {};

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
		//  Depth Stencil State
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

		//default
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

	void FnLoadBuffer()
	{
		//==================================================================
		// Vertex Buffer
		//==================================================================
		std::shared_ptr<CMesh> mesh = std::make_shared<CMesh>();
		CResources::FnInsert(L"RectMesh", mesh);
		mesh->FnCreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
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
		// Constant Buffer
		//==================================================================
		constantBuffer[(UINT)eCBType::Transform] = new CConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->FnCreate(sizeof(TransformCB));

	}//END-void FnLoadBuffer

	void FnLoadShader()
	{
		//yha::graphics::FnGetDevice()->FnCreateShader();

		//shader = new yha::CShader();
		//CShader* shader = new yha::CShader();
		std::shared_ptr<CShader> shader = std::make_shared<CShader>();
		shader->FnCreate(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->FnCreate(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		yha::CResources::FnInsert(L"TriangleShader", shader);

		//CShader* spriteShader = new yha::CShader();
		std::shared_ptr<CShader> spriteShader = std::make_shared<CShader>();
		spriteShader->FnCreate(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->FnCreate(eShaderStage::PS, L"SpritePS.hlsl", "main");
		yha::CResources::FnInsert(L"SpriteShader", spriteShader);

		{
			// SpriteMaterial
			//CTexture* texture = CResources::FnLoad<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");

			//CMaterial* spriteMateiral = new yha::graphics::CMaterial();
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"SpriteMaterial", spriteMateiral);
		}

		{
			// SpriteMaterial02
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);

			spriteMateiral->FnSetRenderingMode(eRenderingMode::Transparent);

			CResources::FnInsert(L"SpriteMaterial02", spriteMateiral);
		}

#pragma region Resource_BG
		//==================================================================
		// 00_Title
		//==================================================================
		{
			// Intro
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Intro", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_Intro.jpg");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_Intro", spriteMateiral);
		}
		{
			// LoadingPage
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"LoadingPage", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_Loading.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_Loading", spriteMateiral);
		}
		{
			// MainMenu
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"MainMenu", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_MainMenu.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_MainMenu", spriteMateiral);
		}
		{
			// Ending
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Ending", L"..\\Resources\\Texture\\MyGame\\BG\\00_Title\\pvz_Ending.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_Ending", spriteMateiral);
		}
		//==================================================================
		// 01_PlayGrass
		//==================================================================
		{
			// GrassDay
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"GrassDay", L"..\\Resources\\Texture\\MyGame\\BG\\01_PlayGrass\\Grassday.jpg");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_GrassDay", spriteMateiral);
		}
		{
			// GrassNight
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"GrassNight", L"..\\Resources\\Texture\\MyGame\\BG\\01_PlayGrass\\Grassnight.jpg");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_GrassNight", spriteMateiral);
		}
		//==================================================================
		// 02_PlayPool
		//==================================================================
		{
			// PoolDay
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"PoolDay", L"..\\Resources\\Texture\\MyGame\\BG\\02_PlayPool\\PVZBackground_7.jpg");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_PoolDay", spriteMateiral);
		}
		{
			// PoolNight
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"PoolNight", L"..\\Resources\\Texture\\MyGame\\BG\\02_PlayPool\\PVZBackground_8.jpg");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"BG_PoolNight", spriteMateiral);
		}
		//==================================================================
		// 03_roof
		//==================================================================

		//{
		//	// Grassday
		//	std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Roofday", L"..\\Resources\\Texture\\MyGame\\BG\\03_PlayRoof\\Roofday.jpg");
		//	std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
		//	spriteMateiral->FnSetShader(spriteShader);
		//	spriteMateiral->FnSetTexture(texture);
		//	CResources::FnInsert(L"BG_Roofday", spriteMateiral);
		//}
		//{
		//	// Grassnight
		//	std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Roofnight", L"..\\Resources\\Texture\\MyGame\\BG\\03_PlayRoof\\Roofnight.jpg");
		//	std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
		//	spriteMateiral->FnSetShader(spriteShader);
		//	spriteMateiral->FnSetTexture(texture);
		//	CResources::FnInsert(L"BG_Roofnight", spriteMateiral);
		//}
#pragma endregion
#pragma region Resource_UI
		//==================================================================
		// UI
		//==================================================================
		{
			// SeedChooserBG
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"SeedChooserBG_edit", L"..\\Resources\\Texture\\MyGame\\UI\\SeedChooserBG_edit.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_SeedChooserBG", spriteMateiral);
		}
		{
			// SunPointChk
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"SunPointChk", L"..\\Resources\\Texture\\MyGame\\UI\\SunPointChk.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_SunPointChk", spriteMateiral);
		}
		{
			// ShovelBG
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"ShovelBG", L"..\\Resources\\Texture\\MyGame\\UI\\ShovelBG.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_ShovelBG", spriteMateiral);
		}
		{
			// Shovel
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Shovel", L"..\\Resources\\Texture\\MyGame\\UI\\Shovel.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_Shovel", spriteMateiral);
		}

		{
			// FlagMeterEmpty
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"FlagMeterEmpty", L"..\\Resources\\Texture\\MyGame\\UI\\FlagMeterEmpty.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_FlagMeterEmpty", spriteMateiral);
		}
		{
			// FlagMeterParts_Zombie
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"FlagMeterParts_Zombie", L"..\\Resources\\Texture\\MyGame\\UI\\FlagMeterParts_Zombie.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_FlagMeterParts_Zombie", spriteMateiral);
		}
		{
			// FlagMeterParts_Flag
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"FlagMeterParts_Flag", L"..\\Resources\\Texture\\MyGame\\UI\\FlagMeterParts_Flag.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_FlagMeterParts_Flag", spriteMateiral);
		}

		//==================================================================
		// UI Button
		//==================================================================
		{
			// btn_Play
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"btn_Play", L"..\\Resources\\Texture\\MyGame\\UI\\btn_Play.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_btn_Play", spriteMateiral);
		}
		{
			// btn_Menu
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"btn_Menu", L"..\\Resources\\Texture\\MyGame\\UI\\btn_Menu.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_btn_Menu", spriteMateiral);
		}
		{
			// btn_StartAdventure
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"btn_StartAdventure", L"..\\Resources\\Texture\\MyGame\\UI\\btn_StartAdventure_Highlight.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"UI_btn_StartAdventure", spriteMateiral);
		}
#pragma endregion

		//==================================================================
		// Cards
		//==================================================================
		{
			// Card_SunFlower
			std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"SunFlower", L"..\\Resources\\Texture\\MyGame\\Cards\\SunFlower.png");
			std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
			spriteMateiral->FnSetShader(spriteShader);
			spriteMateiral->FnSetTexture(texture);
			CResources::FnInsert(L"Card_SunFlower", spriteMateiral);
		}
		//{
		//	// Card_Peashooter
		//	std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Card_Peashooter", L"..\\Resources\\Texture\\MyGame\\Cards\\Card_Peashooter.png");
		//	std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
		//	spriteMateiral->FnSetShader(spriteShader);
		//	spriteMateiral->FnSetTexture(texture);
		//	CResources::FnInsert(L"Card_Peashooter", spriteMateiral);
		//}
		//{
		//	// Card_WallNut
		//	std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Card_WallNut", L"..\\Resources\\Texture\\MyGame\\Cards\\Card_WallNut.png");
		//	std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
		//	spriteMateiral->FnSetShader(spriteShader);
		//	spriteMateiral->FnSetTexture(texture);
		//	CResources::FnInsert(L"Card_WallNut", spriteMateiral);
		//}
		//{
		//	// Card_CherryBomb
		//	std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Card_CherryBomb", L"..\\Resources\\Texture\\MyGame\\Cards\\Card_CherryBomb.png");
		//	std::shared_ptr<CMaterial> spriteMateiral = std::make_shared<CMaterial>();
		//	spriteMateiral->FnSetShader(spriteShader);
		//	spriteMateiral->FnSetTexture(texture);
		//	CResources::FnInsert(L"Card_CherryBomb", spriteMateiral);
		//}


	}//END-void FnLoadShader

	void FnInitialize()
	{
		// RectMesh
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		FnLoadBuffer();
		FnLoadShader();
		FnSetupState();

		//CTexture* texture = CResources::FnLoad<CTexture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		//std::shared_ptr<CTexture> texture = CResources::FnLoad<CTexture>(L"Smile", L"..\\Resources\\Texture\\Smile.png");
		//texture = CResources::FnLoad<CTexture>(L"Link", L"..\\Resources\\Texture\\Link.png");
		//texture->FnBindShader(eShaderStage::PS, 0);
	}//END-void FnInitialize

	void FnRender()
	{
		for (CCamera* cam : cameras)
		{
			if (cam == nullptr)
				continue;

			cam->FnRender();
		}

		cameras.clear();
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
	}//END-void FnRelease
}
























