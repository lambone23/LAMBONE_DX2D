#include "CLayer.h"


namespace yha
{
	CLayer::CLayer()
	{
	}
	CLayer::~CLayer()
	{
	}
	void CLayer::FnInitialize()
	{
	}
	void CLayer::FnUpdate()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			gameObj->FnUpdate();
		}
	}
	void CLayer::FnLateUpdate()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			gameObj->FnLateUpdate();
		}
	}
	void CLayer::FnRender()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			//gameObj->LateUpdate();
			gameObj->FnRender();
		}
	}
	void CLayer::FnAddGameObject(CGameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}
