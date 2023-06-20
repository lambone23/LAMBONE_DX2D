#include "CGraphicDevice_Dx11.h"
#include "CApplication.h"
#include "CRenderer.h"

extern yha::CApplication MyApplication;

namespace yha::graphics
{
	CGraphicDevice_Dx11::CGraphicDevice_Dx11()
	{
		// 1. graphic device, context 생성

		// 2. 화면에 렌더링 할수 있게 도와주는 swapchain 생성

		// 3. rendertarget, view 생성
		// 4. 깊이버퍼와 깊이버퍼 뷰 생성

		// 5. 렌더타겟 클리어 (화면 지우기)
		// 6. present 함수로 렌더타겟에 있는 텍스쳐를 모니터에 그려준다.

		//=================================================================================================
		// #1. graphic device, context 생성
		//=================================================================================================
		HWND hWnd = MyApplication.FnGetHwnd();
		UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
		D3D_FEATURE_LEVEL featureLevel = (D3D_FEATURE_LEVEL)0;

		D3D11CreateDevice
		(
			nullptr
			, D3D_DRIVER_TYPE_HARDWARE
			, nullptr
			, deviceFlag, nullptr, 0
			, D3D11_SDK_VERSION
			, mDevice.GetAddressOf(), &featureLevel
			, mContext.GetAddressOf()
		);

		//=================================================================================================
		// #2. 화면에 렌더링 할수 있게 도와주는 swapchain 생성
		//=================================================================================================
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferDesc.Width = MyApplication.FnGetWidth();
		swapChainDesc.BufferDesc.Height = MyApplication.FnGetHeight();

		if (!FnCreateSwapChain(&swapChainDesc, hWnd))
			return;

		//=================================================================================================
		// #3. rendertarget, view 생성
		//=================================================================================================
		// get rendertarget by swapchain
		if(FAILED
			(
				mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mRenderTarget.GetAddressOf())
			))
			return;

		// create rendertarget view
		mDevice->CreateRenderTargetView((ID3D11Resource*)mRenderTarget.Get(), nullptr, mRenderTargetView.GetAddressOf());

		//=================================================================================================
		// #4. 깊이버퍼와 깊이버퍼 뷰 생성
		//=================================================================================================
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};
		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.CPUAccessFlags = 0;

		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Width = MyApplication.FnGetWidth();
		depthStencilDesc.Height = MyApplication.FnGetHeight();
		depthStencilDesc.ArraySize = 1;

		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;

		depthStencilDesc.MipLevels = 0;
		depthStencilDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA data;
		if (!FnCreateTexture(&depthStencilDesc, &data))
			return;

		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		mViewPort =
		{ //typedef struct D3D11_VIEWPORT
			0.0f									// FLOAT TopLeftX;
			, 0.0f									// FLOAT TopLeftY;
			, (float)(winRect.right - winRect.left)	// FLOAT Width;
			, (float)(winRect.bottom - winRect.top)	// FLOAT Height;
			, 0.0f									// FLOAT MinDepth;
			, 1.0f									// FLOAT MaxDepth;
		};

		FnBindViewPort(&mViewPort);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());

		//=================================================================================================
		// #5. 렌더타겟 클리어 (화면 지우기)
		// #6. present 함수로 렌더타겟에 있는 텍스쳐를 모니터에 그려준다.
		//=================================================================================================
		//여기에서.. CGraphicDevice_Dx11::FnDraw()
	}

	CGraphicDevice_Dx11::~CGraphicDevice_Dx11()
	{

	}
	bool CGraphicDevice_Dx11::FnCreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd)
	{
		DXGI_SWAP_CHAIN_DESC dxgiDesc = {};

		dxgiDesc.OutputWindow = hWnd;
		dxgiDesc.Windowed = true;
		dxgiDesc.BufferCount = desc->BufferCount;
		dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;

		dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiDesc.BufferDesc.Width = desc->BufferDesc.Width;
		dxgiDesc.BufferDesc.Height = desc->BufferDesc.Height;
		dxgiDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
		dxgiDesc.BufferDesc.RefreshRate.Numerator = 240;
		dxgiDesc.BufferDesc.RefreshRate.Denominator = 1;
		dxgiDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_UNSPECIFIED;
		dxgiDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		dxgiDesc.SampleDesc.Count = 1;
		dxgiDesc.SampleDesc.Quality = 0;

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
			return false;

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
			return false;

		if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
			return false;

		if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &dxgiDesc, mSwapChain.GetAddressOf())))
			return false;

		return true;
	}//END-bool CGraphicDevice_Dx11::FnCreateSwapChain

	bool CGraphicDevice_Dx11::FnCreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data)
	{
		D3D11_TEXTURE2D_DESC dxgiDesc = {};
		dxgiDesc.BindFlags = desc->BindFlags;
		dxgiDesc.Usage = desc->Usage;
		dxgiDesc.CPUAccessFlags = 0;

		dxgiDesc.Format = desc->Format;
		dxgiDesc.Width = desc->Width;
		dxgiDesc.Height = desc->Height;
		dxgiDesc.ArraySize = desc->ArraySize;

		dxgiDesc.SampleDesc.Count = desc->SampleDesc.Count;
		dxgiDesc.SampleDesc.Quality = 0;

		dxgiDesc.MipLevels = desc->MipLevels;
		dxgiDesc.MiscFlags = desc->MiscFlags;

		if (FAILED(mDevice->CreateTexture2D(&dxgiDesc, nullptr, mDepthStencilBuffer.ReleaseAndGetAddressOf())))
			return false;

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
			return false;

		return true;
	}//END-bool CGraphicDevice_Dx11::FnCreateTexture

	bool CGraphicDevice_Dx11::FnCreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs
		, UINT NumElements
		, ID3DBlob* byteCode
		, ID3D11InputLayout** ppInputLayout)
	{
		if (FAILED(mDevice->CreateInputLayout(pInputElementDescs, NumElements
			, byteCode->GetBufferPointer()
			, byteCode->GetBufferSize()
			, ppInputLayout)))
			return false;

		return true;
	}//END-bool CGraphicDevice_Dx11::FnCreateInputLayout

	bool CGraphicDevice_Dx11::FnCreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data)
	{
		if (FAILED(mDevice->CreateBuffer(desc, data, buffer)))
			return false;

		return true;
	}//END-bool CGraphicDevice_Dx11::FnCreateBuffer

	//[230608]별도 분리
	//[S]-------------------------------------------------------------------------------------------
	//bool CGraphicDevice_Dx11::FnCreateShader()
	//{
	//	std::filesystem::path shaderPath
	//		= std::filesystem::current_path().parent_path();
	//	shaderPath += L"\\Shader_SOURCE\\";

	//	std::filesystem::path vsPath(shaderPath.c_str());
	//	vsPath += L"TriangleVS.hlsl";

	//	D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
	//		, "main", "vs_5_0", 0, 0, &yha::renderer::triangleVSBlob, &yha::renderer::errorBlob);

	//	if (yha::renderer::errorBlob)
	//	{
	//		OutputDebugStringA((char*)yha::renderer::errorBlob->GetBufferPointer());
	//		yha::renderer::errorBlob->Release();
	//	}

	//	mDevice->CreateVertexShader(yha::renderer::triangleVSBlob->GetBufferPointer()
	//		, yha::renderer::triangleVSBlob->GetBufferSize()
	//		, nullptr, &yha::renderer::triangleVSShader);

	//	std::filesystem::path psPath(shaderPath.c_str());
	//	psPath += L"TrianglePS.hlsl";

	//	D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
	//		, "main", "ps_5_0", 0, 0, &yha::renderer::trianglePSBlob, &yha::renderer::errorBlob);

	//	if (yha::renderer::errorBlob)
	//	{
	//		OutputDebugStringA((char*)yha::renderer::errorBlob->GetBufferPointer());
	//		yha::renderer::errorBlob->Release();
	//	}

	//	mDevice->CreatePixelShader(yha::renderer::trianglePSBlob->GetBufferPointer()
	//		, yha::renderer::trianglePSBlob->GetBufferSize()
	//		, nullptr, &yha::renderer::trianglePSShader);


	//	// Input layout 정점 구조 정보를 넘겨줘야한다.
	//	D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

	//	arrLayout[0].AlignedByteOffset = 0;
	//	arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	//	arrLayout[0].InputSlot = 0;
	//	arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//	arrLayout[0].SemanticName = "POSITION";
	//	arrLayout[0].SemanticIndex = 0;

	//	arrLayout[1].AlignedByteOffset = 12;
	//	arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	//	arrLayout[1].InputSlot = 0;
	//	arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	//	arrLayout[1].SemanticName = "COLOR";
	//	arrLayout[1].SemanticIndex = 0;

	//	// triangle
	//	mDevice->CreateInputLayout(arrLayout, 2
	//		, renderer::triangleVSBlob->GetBufferPointer()
	//		, renderer::triangleVSBlob->GetBufferSize()
	//		, &renderer::triangleLayout);

	//	return true;
	//}//END-bool CGraphicDevice_Dx11::FnCreateShader
	//[E]-------------------------------------------------------------------------------------------

	bool CGraphicDevice_Dx11::FnCompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode)
	{
		ID3DBlob* errorBlob = nullptr;
		D3DCompileFromFile(fileName.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
			, funcName.c_str(), version.c_str(), 0, 0, ppCode, &errorBlob);

		if (errorBlob)
		{
			OutputDebugStringA((char*)(errorBlob->GetBufferPointer()));
			errorBlob->Release();
			errorBlob = nullptr;
		}

		return false;
	}//END-bool CGraphicDevice_Dx11::FnCompileFromfile

	bool CGraphicDevice_Dx11::FnCreateVertexShader(
		const void* pShaderBytecode
		, SIZE_T BytecodeLength
		, ID3D11VertexShader** ppVertexShader)
	{
		if (FAILED(mDevice->CreateVertexShader(pShaderBytecode, BytecodeLength, nullptr, ppVertexShader)))
			return false;

		return true;
	}//END-bool CGraphicDevice_Dx11::FnCreateVertexShader

	bool CGraphicDevice_Dx11::FnCreatePixelShader(
		const void* pShaderBytecode
		, SIZE_T BytecodeLength
		, ID3D11PixelShader** ppPixelShader)
	{
		if (FAILED(mDevice->CreatePixelShader(pShaderBytecode, BytecodeLength, nullptr, ppPixelShader)))
			return false;

		return true;
	}//END-bool CGraphicDevice_Dx11::FnCreatePixelShader

	bool CGraphicDevice_Dx11::FnCreateSampler(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState)
	{
		if (FAILED(mDevice->CreateSamplerState(pSamplerDesc, ppSamplerState)))
			return false;

		return true;
	}//END-bool CGraphicDevice_Dx11::FnCreateSampler

	void CGraphicDevice_Dx11::FnBindInputLayout(ID3D11InputLayout* pInputLayout)
	{
		mContext->IASetInputLayout(pInputLayout);
	}//END-void CGraphicDevice_Dx11::FnBindInputLayout

	void CGraphicDevice_Dx11::FnBindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
	{
		mContext->IASetPrimitiveTopology(Topology);
	}//END-void CGraphicDevice_Dx11::FnBindPrimitiveTopology

	void CGraphicDevice_Dx11::FnBindVertexBuffer(
		UINT StartSlot
		, ID3D11Buffer* const* ppVertexBuffers
		, const UINT* pStrides
		, const UINT* pOffsets)
	{
		mContext->IASetVertexBuffers(StartSlot, 1, ppVertexBuffers, pStrides, pOffsets);
	}//END-void CGraphicDevice_Dx11::FnBindVertexBuffer

	void CGraphicDevice_Dx11::FnBindIndexBuffer(
		ID3D11Buffer* pIndexBuffer
		, DXGI_FORMAT Format
		, UINT Offset)
	{
		mContext->IASetIndexBuffer(pIndexBuffer, Format, Offset);
	}//END-void CGraphicDevice_Dx11::FnBindIndexBuffer

	void CGraphicDevice_Dx11::FnBindVertexShader(ID3D11VertexShader* pVetexShader)
	{
		mContext->VSSetShader(pVetexShader, 0, 0);
	}//END-void CGraphicDevice_Dx11::FnBindVertexShader

	void CGraphicDevice_Dx11::FnBindPixelShader(ID3D11PixelShader* pPixelShader)
	{
		mContext->PSSetShader(pPixelShader, 0, 0);
	}//END-void CGraphicDevice_Dx11::FnBindPixelShader

	void CGraphicDevice_Dx11::FnSetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
	{
		D3D11_MAPPED_SUBRESOURCE subRes = {};
		mContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subRes);
		memcpy(subRes.pData, data, size);
		mContext->Unmap(buffer, 0);
	}//END-void CGraphicDevice_Dx11::FnSetConstantBuffer

	void CGraphicDevice_Dx11::FnBindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::HS:
			mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::DS:
			mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::GS:
			mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::PS:
			mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::CS:
			mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}//END-void CGraphicDevice_Dx11::FnBindConstantBuffer

	void CGraphicDevice_Dx11::FnBindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
	{
		mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
		mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
	}//END-void CGraphicDevice_Dx11::FnBindsConstantBuffer

	void CGraphicDevice_Dx11::FnBindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::HS:
			mContext->HSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::DS:
			mContext->DSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::GS:
			mContext->GSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::PS:
			mContext->PSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::CS:
			mContext->CSSetShaderResources(startSlot, 1, ppSRV);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}//END-void CGraphicDevice_Dx11::FnBindShaderResource

	void CGraphicDevice_Dx11::FnBindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers)
	{
		switch (stage)
		{
		case eShaderStage::VS:
			mContext->VSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::HS:
			mContext->HSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::DS:
			mContext->DSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::GS:
			mContext->GSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::PS:
			mContext->PSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::CS:
			mContext->CSSetSamplers(StartSlot, 1, ppSamplers);
			break;
		case eShaderStage::End:
			break;
		default:
			break;
		}
	}//END-void CGraphicDevice_Dx11::FnBindSampler

	void CGraphicDevice_Dx11::FnBindViewPort(D3D11_VIEWPORT* viewPort)
	{
		mContext->RSSetViewports(1, viewPort);
	}//END-void CGraphicDevice_Dx11::FnBindViewPort

	void CGraphicDevice_Dx11::FnDrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
	{
		mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
	}//END-void CGraphicDevice_Dx11::FnDrawIndexed

	void CGraphicDevice_Dx11::FnClearTarget()
	{
		// render target clear
		FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
	}//END-void CGraphicDevice_Dx11::FnClearTarget

	void CGraphicDevice_Dx11::FnUpdateViewPort()
	{
		// viewport update
		HWND hWnd = MyApplication.FnGetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);
		mViewPort =
		{
			0.0f, 0.0f
			, (float)(winRect.right - winRect.left)
			, (float)(winRect.bottom - winRect.top)
			, 0.0f, 1.0f
		};

		FnBindViewPort(&mViewPort);
	}//END-void CGraphicDevice_Dx11::FnUpdateViewPort

	void CGraphicDevice_Dx11::FnDraw()
	{
		//[230615]별도 분리
		//[S]-------------------------------------------------------------------------------------------
		//// render target clear
		//FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		//mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		//mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0.0f);

		//// viewport update
		//HWND hWnd = MyApplication.FnGetHwnd();
		//RECT winRect = {};
		//GetClientRect(hWnd, &winRect);
		//mViewPort =
		//{
		//	0.0f, 0.0f
		//	, (float)(winRect.right - winRect.left)
		//	, (float)(winRect.bottom - winRect.top)
		//	, 0.0f, 1.0f
		//};

		//FnBindViewPort(&mViewPort);
		//mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
		//[E]-------------------------------------------------------------------------------------------

		//[230608]별도 분리
		//[S]-------------------------------------------------------------------------------------------
		//// input assembler 정점데이터 정보 지정
		//UINT vertexsize = sizeof(renderer::Vertex);
		//UINT offset = 0;

		//// triangle
		//mContext->IASetVertexBuffers(0, 1, &renderer::triangleBuffer, &vertexsize, &offset);

		////[230531] 인덱스 버퍼, 상수 버퍼 생성 이후
		//mContext->IASetIndexBuffer(renderer::triangleIdxBuffer, DXGI_FORMAT_R32_UINT, 0);
		//mContext->IASetInputLayout(renderer::triangleLayout);

		//mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		////Bind VS, PS 
		//mContext->VSSetShader(renderer::triangleVSShader, 0, 0);
		//mContext->PSSetShader(renderer::trianglePSShader, 0, 0);

		//// Draw Render Target
		////■[HW-230530] - drawing shapes
		////[230531] 인덱스버퍼, 상수버퍼 생성 이후
		//mContext->DrawIndexed(24, 0, 0);  //mContext->DrawIndexed(3, 0, 0); //mContext->Draw(3, 0);

		//// 렌더타겟에 있는 이미지를 화면에 그려준다
		//mSwapChain->Present(0, 0);
		//[E]-------------------------------------------------------------------------------------------
		
		//renderer::mesh->BindBuffer();
		//renderer::shader->Binds();
		//mContext->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);

		//renderer::mesh->BindBuffer();
		//renderer::shader->Binds();
		//mContext->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);

		//renderer::mesh->FnBindBuffer();
		//renderer::shader->FnBinds();
		//mContext->DrawIndexed(renderer::mesh->FnGetIndexCount(), 0, 0);

		//// 렌더타겟에 있는 이미지를 화면에 그려준다
		//mSwapChain->Present(0, 0);

	}//END-void CGraphicDevice_Dx11::FnDraw

	void CGraphicDevice_Dx11::FnPresent()
	{
		mSwapChain->Present(0, 0);
	}//END-void CGraphicDevice_Dx11::FnPresent
}
