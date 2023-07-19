#include "CApplication.h"
#include "CInput.h"
#include "CTime.h"
#include "CRenderer.h"
#include "CSceneManager.h"
#include <windowsx.h>

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
		FnDestroy();
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

		//====================================================================
		// 마우스 LBUTTON 클릭시, 윈도우 상의 좌표 위치 출력
		//====================================================================
		//if (CInput::FnGetKey(eKeyCode::LBUTTON))
		//{
		//	HWND Tmp_mHwnd = FnGetHwnd();

		//	//VectorXY MousePos = CInput::FnGetMousePos();
		//	::POINT MousePos = {};
		//	::GetCursorPos(&MousePos);
		//	::ScreenToClient(Tmp_mHwnd, &MousePos);


		//	TCHAR Temp[256] = { 0, };
		//	_stprintf_s(Temp, L"x: %d, y: %d", MousePos.x, MousePos.y);
		//	MessageBox(Tmp_mHwnd, Temp, L"좌표", MB_OK);
		//}
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

		//CSceneManager::FnRender();
		renderer::FnRender();
		//graphicDevice->FnDraw();

		//graphicDevice->FnPresent();
	}

	void CApplication::FnDestroy()
	{
		CSceneManager::FnDestroy();
	}

	void CApplication::FnPresent()
	{
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
