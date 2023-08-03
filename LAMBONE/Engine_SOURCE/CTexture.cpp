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

	bool CTexture::FnCreate(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag)
	{
		if (mTexture == nullptr)
		{
			mDesc.BindFlags			= bindFlag;
			mDesc.Usage				= D3D11_USAGE_DEFAULT;
			mDesc.CPUAccessFlags	= 0;
			mDesc.Format			= format;
			mDesc.Width				= width;
			mDesc.Height			= height;
			mDesc.ArraySize			= 1;

			mDesc.SampleDesc.Count		= 1;
			mDesc.SampleDesc.Quality	= 0;

			mDesc.MipLevels	= 0;
			mDesc.MiscFlags	= 0;

			mWidth			= width;
			mHeight			= height;

			if (!FnGetDevice()->FnCreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!FnGetDevice()->FnCraeteDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format						= mDesc.Format;
			tSRVDesc.Texture2D.MipLevels		= 1;
			tSRVDesc.Texture2D.MostDetailedMip	= 0;
			tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

			if (!FnGetDevice()->FnCreateShaderResourceView(mTexture.Get(), &tSRVDesc, mSRV.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format				= mDesc.Format;
			tSRVDesc.Texture2D.MipSlice	= 0;
			tSRVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

			if (!FnGetDevice()->FnCreateRenderTargetView(mTexture.Get(), nullptr, mRTV.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
			tUAVDesc.Format				= mDesc.Format;
			tUAVDesc.Texture2D.MipSlice	= 0;
			tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

			if (!FnGetDevice()->FnCreateUnordedAccessView(mTexture.Get(), &tUAVDesc, mUAV.GetAddressOf()))
				return false;
		}

		return true;
	}//END-bool CTexture::FnCreate

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

		mWidth	= mImage.GetMetadata().width;
		mHeight	= mImage.GetMetadata().height;

		return S_OK;
	}//END-HRESULT CTexture::FnLoad

	//void CTexture::FnBindShader(eShaderStage stage, UINT startSlot)
	void CTexture::FnBindShaderResource(eShaderStage stage, UINT startSlot)
	{
		FnGetDevice()->FnBindShaderResource(stage, startSlot, mSRV.GetAddressOf());
	}//END-void CTexture::FnBindShaderResource

	void CTexture::FnBindUnorderedAccessViews(UINT slot)
	{
		UINT i = -1;
		FnGetDevice()->FnBindUnorderedAccess(slot, mUAV.GetAddressOf(), &i);
	}//END-void CTexture::FnBindUnorderedAccessViews

	void CTexture::FnClearUnorderedAccessViews(UINT slot)
	{
		ID3D11UnorderedAccessView* p = nullptr;
		UINT i = -1;
		FnGetDevice()->FnBindUnorderedAccess(slot, &p, &i);
	}//END-void CTexture::FnClearUnorderedAccessViews

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

    HRESULT CTexture::FnCreateTex(const std::wstring& path, UINT filecnt, size_t imageMaxWidth, size_t imageMaxHeight)
    {
        ScratchImage atlasImage;
        HRESULT hr = S_OK;

        wchar_t ext[_MAX_EXT] = {};
        _wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, ext, _MAX_EXT);
        ScratchImage image;
        int idx = 0;
        std::filesystem::path fs(path);

        bool isMake = false;
        for (const auto& p : std::filesystem::recursive_directory_iterator(path))
        {
            std::wstring fileName = p.path().filename();
            std::wstring fullName = p.path().wstring(); // Use the full path from the iterator
            if (_wcsicmp(ext, L".dds") == 0)
            {
                hr = LoadFromDDSFile(fullName.c_str(), DDS_FLAGS_NONE, nullptr, image);
            }
            else if (_wcsicmp(ext, L".tga") == 0)
            {
                hr = LoadFromTGAFile(fullName.c_str(), nullptr, image);
            }
            else if (_wcsicmp(ext, L".hdr") == 0)
            {
                hr = LoadFromHDRFile(fullName.c_str(), nullptr, image);
            }
            else
            {
                hr = LoadFromWICFile(fullName.c_str(), WIC_FLAGS_NONE, nullptr, image);
            }

            if (SUCCEEDED(hr))
            {
                // Convert the image to a different format if needed (e.g., to DXGI_FORMAT_R8G8B8A8_UNORM)
                ScratchImage convertedImage;
                hr = Convert(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DXGI_FORMAT_R8G8B8A8_UNORM, TEX_FILTER_DEFAULT, TEX_THRESHOLD_DEFAULT, convertedImage);
                if (FAILED(hr))
                {
                    // Handle the conversion error if necessary
                    return hr;
                }
                if (isMake == false)
                {
                    hr = atlasImage.Initialize2D(DXGI_FORMAT_R8G8B8A8_UNORM, imageMaxWidth * filecnt, imageMaxHeight * 2, 1, 1);
                    isMake = true;
                }
                if (FAILED(hr))
                {
                    // Handle the atlas image initialization error if necessary
                    return hr;
                }

                // Copy the converted image data to the atlas image
                hr = CopyRectangle(*convertedImage.GetImage(0, 0, 0), Rect(0, 0, convertedImage.GetMetadata().width, convertedImage.GetMetadata().height),
                    *atlasImage.GetImage(0, 0, 0), TEX_FILTER_DEFAULT, (imageMaxWidth)*idx, 0);
                if (FAILED(hr))
                {
                    // Handle the copy rectangle error if necessary
                    return hr;
                }
            }
            idx++;
        }
        if (FAILED(hr))
        {
            // Error handling if image loading, conversion, or copy rectangle fails
            return hr;
        }

        if (FAILED(hr))
        {
            // Error handling if the texture creation failed
            return hr;
        }

        CreateShaderResourceView
        (
            FnGetDevice()->FnGetID3D11Device()
            , atlasImage.GetImages()
            , atlasImage.GetImageCount()
            , atlasImage.GetMetadata()
            , mSRV.GetAddressOf()
        );
        mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

        // Create an atlas texture object
        // Assign the DirectX 11 texture and SRV to the atlasTexture

        // Copy the image data from atlasImage to atlasTexture->mImage
        this->mImage.Initialize2D(
            atlasImage.GetMetadata().format,
            atlasImage.GetMetadata().width,
            atlasImage.GetMetadata().height,
            atlasImage.GetMetadata().arraySize,
            atlasImage.GetMetadata().mipLevels
        );

        return S_OK;
    }
}