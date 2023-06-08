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
		// ���⼭ �ʱ� ���� �ʵ����͸� ����
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
