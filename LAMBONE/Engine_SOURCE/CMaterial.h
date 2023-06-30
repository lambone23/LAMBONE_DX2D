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
		void FnClear();

		void FnSetShader(std::shared_ptr<CShader> shader) { mShader = shader; }
		void FnSetTexture(std::shared_ptr<CTexture> texture) { mTexture = texture; }

		void FnSetRenderingMode(eRenderingMode mode) { mMode = mode; }
		eRenderingMode FnGetRenderingMode() { return mMode; }

	private:
		std::shared_ptr<CShader> mShader;
		std::shared_ptr<CTexture> mTexture;

		eRenderingMode mMode;
	};
}
