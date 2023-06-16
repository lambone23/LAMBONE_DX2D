#include "CSceneManager.h"
#include "CPlayScene.h"


namespace yha
{
	CScene* CSceneManager::mActiveScene = nullptr;
	void CSceneManager::FnInitialize()
	{
		//CPlayScene* test = new CPlayScene();

		mActiveScene = new CPlayScene();
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
}
