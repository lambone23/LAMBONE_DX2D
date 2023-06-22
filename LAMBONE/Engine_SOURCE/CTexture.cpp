#include "CTexture.h"
#include "CGraphicDevice_Dx11.h"

namespace yha::graphics
{
	CTexture::CTexture()
		//: mImage{}
		: CResource(enums::eResourceType::Texture)
		, mImage{}
		, mTexture(nullptr)
		, mSRV(nullptr)
		, mDesc{}
	{
	}

	CTexture::~CTexture()
	{
	}

	HRESULT CTexture::FnLoad(const std::wstring& path)
	{
		wchar_t szExtension[50] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		CreateShaderResourceView
		(
			FnGetDevice()->FnGetID3D11Device()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);
		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		return S_OK;
	}//END-HRESULT CTexture::FnLoad

	void CTexture::FnBindShader(eShaderStage stage, UINT startSlot)
	{
		FnGetDevice()->FnBindShaderResource(stage, startSlot, mSRV.GetAddressOf());
	}//END-void CTexture::FnBindShader

	void CTexture::FnClear()
	{
		ID3D11ShaderResourceView* srv = nullptr;

		FnGetDevice()->FnBindShaderResource(eShaderStage::VS, 0, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::DS, 0, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::GS, 0, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::HS, 0, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::CS, 0, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::PS, 0, &srv);
	}//END-void CTexture::FnClear
}