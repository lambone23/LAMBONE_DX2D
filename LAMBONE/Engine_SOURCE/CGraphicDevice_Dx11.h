#pragma once
#include "ZEngine.h"
#include "CGraphics.h"
#include "CTexture.h"

namespace yha::graphics
{
	class CGraphicDevice_Dx11
	{
	public:
		CGraphicDevice_Dx11();
		~CGraphicDevice_Dx11();

	public:
		bool FnCreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd);
		//bool FnCreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data);
		bool FnCreateTexture2D(const D3D11_TEXTURE2D_DESC* desc, void* data, ID3D11Texture2D** ppTexture2D);
		bool FnCreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements, ID3DBlob* byteCode, ID3D11InputLayout** ppInputLayout);

		bool FnCreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data);
		
		//bool FnCreateShader();
		bool FnCompileFromfile(const std::wstring& fileName, const std::string& funcName, const std::string& version, ID3DBlob** ppCode);
		bool FnCreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader);
		bool FnCreateGeometryShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11GeometryShader** ppGeometryShader);
		bool FnCreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppPixelShader);
		bool FnCreateComputeShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11ComputeShader** ppComputeShader);

		bool FnCreateSamplerState(const D3D11_SAMPLER_DESC* pSamplerDesc, ID3D11SamplerState** ppSamplerState);
		bool FnCreateRasterizeState(const D3D11_RASTERIZER_DESC* pRasterizerDesc, ID3D11RasterizerState** ppRasterizerState);
		bool FnCreateDepthStencilState(const D3D11_DEPTH_STENCIL_DESC* pDepthStencilDesc, ID3D11DepthStencilState** ppDepthStencilState);
		bool FnCreateBlendState(const D3D11_BLEND_DESC* pBlendStateDesc, ID3D11BlendState** ppBlendState);

		bool FnCraeteDepthStencilView(ID3D11Resource* pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* pDesc, ID3D11DepthStencilView** ppDepthStencilView);
		bool FnCreateShaderResourceView(ID3D11Resource* pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* pDesc, ID3D11ShaderResourceView** ppSRView);
		bool FnCreateRenderTargetView(ID3D11Resource* pResource, const D3D11_RENDER_TARGET_VIEW_DESC* pDesc, ID3D11RenderTargetView** ppRTView);
		bool FnCreateUnordedAccessView(ID3D11Resource* pResource, const D3D11_UNORDERED_ACCESS_VIEW_DESC* pDesc, ID3D11UnorderedAccessView** ppUAView);

		void FnBindInputLayout(ID3D11InputLayout* pInputLayout);
		void FnBindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology);
		
		void FnBindVertexBuffer(UINT StartSlot, ID3D11Buffer* const* ppVertexBuffers, const UINT* pStrides, const UINT* pOffsets);
		void FnBindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT Format, UINT Offset);
		
		void FnBindVertexShader(ID3D11VertexShader* pVetexShader);
		void FnBindHullShader(ID3D11HullShader* pHullShader);
		void FnBindDomainShader(ID3D11DomainShader* pDomainShader);
		void FnBindGeometryShader(ID3D11GeometryShader* pGeometryShader);
		void FnBindPixelShader(ID3D11PixelShader* pPixelShader);
		void FnBindComputeShader(ID3D11ComputeShader* pComputeShader);
		void FnDispatch(UINT ThreadGroupCountX, UINT ThreadGroupCountY, UINT ThreadGroupCountZ);

		// ��� ����
		void FnSetConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size);
		void FnBindConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);
		void FnBindsConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer);

		void FnBindBuffer(ID3D11Buffer* buffer, void* data, UINT size);

		void FnBindShaderResource(eShaderStage stage, UINT startSlot, ID3D11ShaderResourceView** ppSRV);
		void FnBindUnorderedAccess(UINT slot, ID3D11UnorderedAccessView** ppUnorderedAccessViews, const UINT* pUAVInitialCounts);

		void FnBindSampler(eShaderStage stage, UINT StartSlot, ID3D11SamplerState** ppSamplers);	
		void FnBindViewPort(D3D11_VIEWPORT* viewPort);

		void FnBindRasterizeState(ID3D11RasterizerState* pRasterizerState);
		void FnBindDepthStencilState(ID3D11DepthStencilState* pDepthStencilState);
		void FnBindBlendState(ID3D11BlendState* pBlendState);
		void FnCopyResource(ID3D11Resource* pDstResource, ID3D11Resource* pSrcResource);

		void FnDrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation);
		void FnDrawIndexedInstanced(UINT IndexCountPerInstance, UINT InstanceCount, UINT StartIndexLocation, INT BaseVertexLocation, UINT StartInstanceLocation);
		void FnClearTarget();
		void FnUpdateViewPort();
		void FnDraw();
		void FnPresent();

		ID3D11Device* FnGetID3D11Device() { return mDevice.Get(); }
		ID3D11DeviceContext* FnGetID3D11DeviceContext() { return mContext.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;						// ���� �׷���ī�� �ϵ���� ��ü
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;				// dx11���� ���������� ����̽���ü ���������ʰ� �̰�ü�� �̿��Ͽ� ����� ������.
		
		//Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;			// ���������� �׷��� �ؽ�ó(��ȭ��)
		//Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;	// ����Ÿ�ٿ� ������������ �ʰ� ����Ÿ�ٺ並 ���ؼ� ����
		//Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;		// ���̹���
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;	// ���̹��ۿ� �����Ҽ� �ִ� ��
		std::shared_ptr<yha::graphics::CTexture> mRenderTarget;				// ���������� �׷��� �ؽ�ó(��ȭ��)
		std::shared_ptr<yha::graphics::CTexture> mDepthStencil;				// ���̹���
		
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;					// ������۸� �۾��� �������ִ� swapChain

		D3D11_VIEWPORT mViewPort;
	};

	inline CGraphicDevice_Dx11*& FnGetDevice()
	{
		static CGraphicDevice_Dx11* device = nullptr;
		return device;
	}
}
