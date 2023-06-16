#include "CApplication.h"
#include "CInput.h"
#include "CTime.h"
#include "CRenderer.h"
#include "CSceneManager.h"


namespace yha
{
	CApplication::CApplication()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{

	}

	CApplication::~CApplication()
	{
	}

	void CApplication::FnRun()
	{
		FnUpdate();
		FnLateUpdate();
		FnRender();
	}

	void CApplication::FnInitialize()
	{
		CTime::FnInitiailize();
		CInput::FnInitialize();

		renderer::FnInitialize();
		CSceneManager::FnInitialize();
	}

	void CApplication::FnUpdate()
	{
		CTime::FnUpdate();
		CInput::FnUpdate();
		CSceneManager::FnUpdate();
	}

	void CApplication::FnLateUpdate()
	{
		CSceneManager::FnLateUpdate();
	}

	void CApplication::FnRender()
	{
		CTime::FnRender();

		graphicDevice->FnClearTarget();
		graphicDevice->FnUpdateViewPort();
		CSceneManager::FnRender();
		//graphicDevice->FnDraw();

		graphicDevice->FnPresent();
	}

	void CApplication::FnSetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<yha::graphics::CGraphicDevice_Dx11>();
			yha::graphics::FnGetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}

}
