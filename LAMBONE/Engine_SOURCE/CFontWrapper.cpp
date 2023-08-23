#include "CFontWrapper.h"
#include "CGraphicDevice_DX11.h"

namespace yha
{
	IFW1Factory* CFontWrapper::mFW1Factory = nullptr;
	IFW1FontWrapper* CFontWrapper::mFontWrapper = nullptr;

	bool CFontWrapper::FnInitialize()
	{
		if (FAILED(FW1CreateFactory(FW1_VERSION, &mFW1Factory)))
			return false;

		ID3D11Device* pDevice = graphics::FnGetDevice()->FnGetID3D11Device();
		if (FAILED(mFW1Factory->CreateFontWrapper(pDevice, L"Arial", &mFontWrapper)))
			return false;

		return true;
	}

	void CFontWrapper::FnDrawFont(const wchar_t* str, float x, float y, float size, UINT rgb)
	{
		//RGB();
		ID3D11DeviceContext* pContext = graphics::FnGetDevice()->FnGetID3D11DeviceContext();
		mFontWrapper->DrawString(
			pContext,
			str,	// String
			size,	// Font size
			x,		// X position
			y,		// Y position
			rgb,	// Text color, 0xAaBbGgRr
			FW1_RESTORESTATE      // Flags (for example FW1_RESTORESTATE to keep context states unchanged)
		);
	}

	void CFontWrapper::FnRelease()
	{
		mFW1Factory->Release();
		mFW1Factory = nullptr;

		mFontWrapper->Release();
		mFontWrapper = nullptr;
	}
}
