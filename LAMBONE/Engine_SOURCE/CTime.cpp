#include "CTime.h"
#include "CApplication.h"

extern yha::CApplication MyApplication;

namespace yha
{
	double CTime::mDeltaTime = 0.0l;
	double CTime::mSecond = 0.0f;
	LARGE_INTEGER CTime::mCpuFrequency = {};
	LARGE_INTEGER CTime::mPrevFrequency = {};
	LARGE_INTEGER CTime::mCurFrequency = {};

	void CTime::FnInitiailize()
	{
		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&mCpuFrequency);

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&mPrevFrequency);
	}

	void CTime::FnUpdate()
	{
		QueryPerformanceCounter(&mCurFrequency);

		double differnceFrequency = mCurFrequency.QuadPart - mPrevFrequency.QuadPart;

		mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void CTime::FnRender()
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			HWND hWnd = MyApplication.FnGetHwnd();

			wchar_t szFloat[50] = {};
			float FPS = 1.0f / (float)mDeltaTime;
			swprintf_s(szFloat, 50, L"PvZ By LAMBONE -- #FPS : %d", (UINT)FPS);
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}
	}
}
