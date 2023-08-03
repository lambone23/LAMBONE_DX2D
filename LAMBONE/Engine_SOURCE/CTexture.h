#pragma once
#include "CResource.h"
#include "CGraphics.h"

#include "../External/DirectXTex/Include/DirectXTex.h"
#include "../External/DirectXTex/Include/DirectXTex.inl"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\External\\DirectXTex\\Lib\\Release\\DirectXTex.lib")
#endif

namespace yha::graphics
{
	class CTexture : public CResource
	{
	public:
		CTexture();
		~CTexture();

	public:
		bool FnCreate(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag);
		virtual HRESULT FnLoad(const std::wstring& path) override;
		
		//void FnBindShader(eShaderStage stage, UINT startSlot);
		void FnBindShaderResource(eShaderStage stage, UINT startSlot);
		void FnBindUnorderedAccessViews(UINT slot);
		void FnClearUnorderedAccessViews(UINT slot);

		void FnClear();

		//size_t FnGetWidth() { return mImage.GetMetadata().width; }
		//size_t FnGetHeight() { return mImage.GetMetadata().height; }
		size_t FnGetWidth() { return mWidth; }
		size_t FnGetHeight() { return mHeight; }

		HRESULT FnCreateTex(const std::wstring& path, UINT filecnt, size_t imageMaxWidth, size_t imageMaxHeight);

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> FnGetRTV()			{ return  mRTV; }
		void FnSetRTV(Microsoft::WRL::ComPtr<ID3D11RenderTargetView> rtv)	{ mRTV = rtv; }
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> FnGetDSV()			{ return  mDSV; }
		void FnSetDSV(Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv)	{ mDSV = dsv; }
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> FnGetSRV()			{ return  mSRV; }
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> FnGetUAV()		{ return  mUAV; }
		Microsoft::WRL::ComPtr<ID3D11Texture2D> FnGetTexture()				{ return mTexture; }
		void FnSetTexture(Microsoft::WRL::ComPtr<ID3D11Texture2D> texture)	{ mTexture = texture; }

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRTV;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDSV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		UINT mWidth;
		UINT mHeight;

		D3D11_TEXTURE2D_DESC mDesc;
	};
}
