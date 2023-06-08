#include "CScene.h"

namespace yha
{
	CScene::CScene()
	{
	}
	CScene::~CScene()
	{

	}

	void CScene::FnInitialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅
	}

	void CScene::FnUpdate()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			gameObj->FnUpdate();
		}
	}

	void CScene::FnLateUpdate()
	{
	}
	void CScene::FnRender()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			gameObj->FnRender();
		}
	}
}
