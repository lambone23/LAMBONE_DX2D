#include "CSceneManager.h"
#include "CPlayScene.h"

namespace yha
{
	CScene* CSceneManager::mActiveScene = nullptr;
	std::map<std::wstring, CScene*> CSceneManager::mScenes;

	void CSceneManager::FnInitialize()
	{
		//CPlayScene* test = new CPlayScene();

		mActiveScene = new CPlayScene();
		mScenes.insert(std::make_pair(L"PlayScene", mActiveScene));

		mActiveScene->FnInitialize();
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

	void CSceneManager::FnRelease()
	{
		for (auto iter : mScenes)
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

		mActiveScene->FnOnExit();
		mActiveScene = iter->second;
		mActiveScene->FnOnEnter();

		return iter->second;
	}
}
