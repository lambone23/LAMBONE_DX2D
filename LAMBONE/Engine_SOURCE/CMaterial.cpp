#include "CMaterial.h"

namespace yha::graphics
{
	CMaterial::CMaterial()
		: CResource(yha::enums::eResourceType::Material)
		, mShader(nullptr)
		, mTexture(nullptr)
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
		mTexture->FnBindShader(eShaderStage::PS, 0);
		mShader->FnBinds();
	}
}
