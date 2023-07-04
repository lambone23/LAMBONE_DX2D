#pragma once
#include "ZEngine.h"
#include "CGraphicDevice_Dx11.h"
#include "CScene.h"
#include <tchar.h>

namespace yha
{
	class CApplication
	{
	public:
		CApplication();
		~CApplication();

	public:
		void FnRun();

		void FnInitialize();
		void FnUpdate();
		void FnLateUpdate();
		void FnRender();

	public:
		void FnSetWindow(HWND hwnd, UINT width, UINT height);

		UINT FnGetWidth() { return mWidth; }
		UINT FnGetHeight() { return mHeight; }
		HWND FnGetHwnd() { return mHwnd; }

	private:
		bool mbInitialize = false;
		// 오로지 한개의 객체만 만들수 있는 스마트 포인터
		std::unique_ptr<yha::graphics::CGraphicDevice_Dx11> graphicDevice;

		// HDC mHdc; -> GPU API
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;

	public:
		bool mFlagMyGame = true;
		float ScaleWidth = 8.0f;
		float ScaleHeight = 4.5f;

		bool mFlagChkFirst = true;
	};
}
