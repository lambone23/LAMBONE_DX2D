#pragma once
#include "..\Engine_SOURCE\CSceneManager.h"
#include "CPlayScene.h"

#include "..\Engine_SOURCE\CApplication.h"
#include "CSceneIntro.h"
#include "CSceneLoading.h"
#include "CSceneMainMenu.h"
#include "CSceneEnding.h"
#include "CScenePlayGrassDay.h"
#include "CScenePlayGrassNight.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\ZEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\ZEngine.lib")
#endif

extern yha::CApplication MyApplication;

namespace yha
{
	void FnInitializeScenes()
	{
		if (MyApplication.mFlagMyGame)
		{
			CSceneManager::FnCreateScene<CSceneIntro>(L"Scene_Intro");
			CSceneManager::FnCreateScene<CSceneLoading>(L"Scene_Loading");
			CSceneManager::FnCreateScene<CSceneMainMenu>(L"Scene_MainMenu");
			CSceneManager::FnCreateScene<CSceneEnding>(L"Scene_Ending");
			
			CSceneManager::FnCreateScene<CScenePlayGrassDay>(L"Scene_PlayGrassDay");

			//��TODO-Chk
			CSceneManager::FnCreateScene<CScenePlayGrassNight>(L"Scene_PlayGrassNight");

			CSceneManager::FnLoadScene(L"Scene_Intro");
			//CSceneManager::FnLoadScene(L"Scene_PlayGrassDay");
		}
		else
			CSceneManager::FnCreateScene<CPlayScene>(L"PlayScene");
	}
}
