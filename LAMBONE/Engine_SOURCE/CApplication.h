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
		void FnDestroy();
		void FnPresent();

	public:
		void FnSetWindow(HWND hwnd, UINT width, UINT height);

		UINT FnGetWidth() { return mWidth; }
		UINT FnGetHeight() { return mHeight; }
		HWND FnGetHwnd() { return mHwnd; }

		static float FnGetScaleFullWidth() { return 8.f; }
		static float FnGetScaleFullHeight() { return 4.5f; }

	private:
		bool mbInitialize = false;
		// ������ �Ѱ��� ��ü�� ����� �ִ� ����Ʈ ������
		std::unique_ptr<yha::graphics::CGraphicDevice_Dx11> graphicDevice;

		// HDC mHdc; -> GPU API
		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;

	public:
		bool mFlagMyGame = true;
	};
}
