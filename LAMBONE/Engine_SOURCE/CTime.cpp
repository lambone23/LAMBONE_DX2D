#include "CTime.h"
#include "CApplication.h"
#include "CSceneManager.h"
#include "CFontWrapper.h"

extern yha::CApplication MyApplication;
extern yha::CSceneManager MySceneManager;

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
		//wchar_t szFloat[50] = L"Sample_Time";

		if (mSecond > 1.0f)
		{
			HWND hWnd = MyApplication.FnGetHwnd();
			wchar_t szFloat[200] = {};
			float FPS = 1.0f / (float)mDeltaTime;

			std::wstring activeSceneName = CSceneManager::FnGetActiveSceneName();

			if (activeSceneName == L"PlayScene")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [PlayScene]", (UINT)FPS);
			else if (activeSceneName == L"Scene_Intro")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [Intro]", (UINT)FPS);
			else if (activeSceneName == L"Scene_Loading")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [Loading]", (UINT)FPS);
			else if (activeSceneName == L"Scene_MainMenu")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [MainMenu]", (UINT)FPS);
			else if (activeSceneName == L"Scene_Ending")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [Ending]", (UINT)FPS);
			else if (activeSceneName == L"Scene_PlayGrassDay")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [PlayGrassDay]", (UINT)FPS);
			else if (activeSceneName == L"Scene_PlayGrassNight")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [PlayGrassNight]", (UINT)FPS);
			else if (activeSceneName == L"Scene_PlayPoolDay")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [PlayPoolDay]", (UINT)FPS);
			else if (activeSceneName == L"Scene_PlayPoolNight")
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d, [PlayPoolNight]", (UINT)FPS);
			else
				swprintf_s(szFloat, 200, L"PvZ By LAMBONE -- #FPS : %d", (UINT)FPS);
			
			//int iLen = wcsnlen_s(szFloat, 50);
			SetWindowText(hWnd, szFloat);

			//TextOut(hdc, 0, 0, szFloat, 20);
			mSecond = 0.0f;
		}

		//CFontWrapper::FnDrawFont(szFloat, 10.f, 30.f, 20, FONT_RGBA(255, 0, 255, 255));
	}
}
