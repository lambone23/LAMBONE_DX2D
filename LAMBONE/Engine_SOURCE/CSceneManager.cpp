#include "CSceneManager.h"

//#include "CPlayScene.h"

#include "CApplication.h"
//#include "../ZEngine/CSceneIntro.h"
//#include "../ZEngine/CSceneLoading.h"
//#include "../ZEngine/CSceneMainMenu.h"
//#include "../ZEngine/CSceneEnding.h"
//#include "../ZEngine/CScenePlayGrassDay.h"
//#include "../ZEngine/CScenePlayGrassNight.h"
//#include "../ZEngine/CScenePlayPoolDay.h"
//#include "../ZEngine/CScenePlayPoolNight.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CScene* CSceneManager::mActiveScene = nullptr;
	std::map<std::wstring, CScene*> CSceneManager::mScenes;
	std::wstring CSceneManager::mActiveSceneName = L"ABC";

	void CSceneManager::FnInitialize()
	{
		//if (MyApplication.mFlagMyGame)
		//{
		//	mScenes.insert(std::make_pair(L"Scene_Intro", new CSceneIntro()));
		//	mScenes.insert(std::make_pair(L"Scene_Loading", new CSceneLoading()));
		//	mScenes.insert(std::make_pair(L"Scene_MainMenu", new CSceneMainMenu()));
		//	mScenes.insert(std::make_pair(L"Scene_Ending", new CSceneEnding()));

		//	mScenes.insert(std::make_pair(L"Scene_PlayGrassDay", new CScenePlayGrassDay()));
		//	mScenes.insert(std::make_pair(L"Scene_PlayGrassNight", new CScenePlayGrassNight()));
		//	mScenes.insert(std::make_pair(L"Scene_PlayPoolDay", new CScenePlayPoolDay()));
		//	mScenes.insert(std::make_pair(L"Scene_PlayPoolNight", new CScenePlayPoolNight()));

		//	std::map<std::wstring, CScene*>::iterator iter = mScenes.begin();

		//	for (auto itr = mScenes.begin(); itr != mScenes.end(); itr++)
		//	{
		//		if (nullptr != iter->second)
		//			itr->second->FnInitialize();
		//	}

		//	mActiveScene = FnLoadScene(L"Scene_Intro");
		// 
		//}
		//else
		//{
		//	mActiveScene = new CPlayScene();
		//	mScenes.insert(std::make_pair(L"PlayScene", mActiveScene));
		//	mActiveScene->FnInitialize();
		//}
	}
	void CSceneManager::FnUpdate()
	{
		mActiveScene->FnUpdate();
	}
	void CSceneManager::FnLateUpdate()
	{
		mActiveScene->FnLateUpdate();
	}
	void CSceneManager::FnRender()
	{
		mActiveScene->FnRender();
	}
	void CSceneManager::FnRender_Font()
	{
		mActiveScene->FnRender_Font();
	}
	void CSceneManager::FnDestroy()
	{
		mActiveScene->FnDestroy();
	}
	void CSceneManager::FnRelease()
	{
		for (auto& iter : mScenes)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	CScene* CSceneManager::FnLoadScene(std::wstring name)
	{
		std::map<std::wstring, CScene*>::iterator iter = mScenes.find(name);

		if (iter == mScenes.end())
			return nullptr;

		if (nullptr != mActiveScene)
		{
			mActiveScene->FnOnExit();
			mActiveScene = iter->second;
			mActiveSceneName = name;
			mActiveScene->FnOnEnter();
		}

		return iter->second;
	}
}
