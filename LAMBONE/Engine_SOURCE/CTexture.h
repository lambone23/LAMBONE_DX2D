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
		virtual HRESULT FnLoad(const std::wstring& path) override;
		void FnBindShader(eShaderStage stage, UINT startSlot);
		void FnClear();

		size_t FnGetWidth() { return mImage.GetMetadata().width; }
		size_t FnGetHeight() { return mImage.GetMetadata().height; }

		HRESULT FnCreateTex(const std::wstring& path, UINT filecnt, size_t imageMaxWidth, size_t imageMaxHeight);

	private:
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}
