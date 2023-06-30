#include "CMaterial.h"

namespace yha::graphics
{
	CMaterial::CMaterial()
		: CResource(yha::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
		, mMode(eRenderingMode::Opaque)
	{

	}

	CMaterial::~CMaterial()
	{
	}

	HRESULT CMaterial::FnLoad(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	void CMaterial::FnBinds()
	{
		if (mTexture)
			mTexture->FnBindShader(eShaderStage::PS, 0);

		if (mShader)
			mShader->FnBinds();
	}

	void CMaterial::FnClear()
	{
		mTexture->FnClear();
	}
}
