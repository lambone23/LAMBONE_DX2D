#pragma once
#include "CResource.h"
#include "CShader.h"
#include "CTexture.h"

namespace yha::graphics
{
	class CMaterial : public CResource
	{
	public:
		CMaterial();
		~CMaterial();

	public:

		virtual HRESULT FnLoad(const std::wstring& path) override;

		void FnBinds();

		void FnSetShader(CShader* shader) { mShader = shader; }
		void FnSetTexture(CTexture* texture) { mTexture = texture; }

	private:
		CShader* mShader;
		CTexture* mTexture;
	};
}
