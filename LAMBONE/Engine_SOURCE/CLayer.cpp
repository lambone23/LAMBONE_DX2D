#include "CLayer.h"

namespace yha
{
	CLayer::CLayer()
	{
	}
	CLayer::~CLayer()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			delete gameObj;
			gameObj = nullptr;
		}
	}
	void CLayer::FnInitialize()
	{
	}
	void CLayer::FnUpdate()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			if (gameObj->FnGetState()
				!= CGameObject::eState::Active)
				continue;

			gameObj->FnUpdate();
		}
	}
	void CLayer::FnLateUpdate()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			if (gameObj->FnGetState()
				!= CGameObject::eState::Active)
				continue;

			gameObj->FnLateUpdate();
		}
	}
	void CLayer::FnRender()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			if (gameObj->FnGetState()
				!= CGameObject::eState::Active)
				continue;

			gameObj->FnRender();
		}
	}
	void CLayer::FnRender_Font()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			if (gameObj->FnGetState()
				!= CGameObject::eState::Active)
				continue;

			gameObj->FnRender_Font();
		}
	}

	void CLayer::FnDestory()
	{
		// dead ������Ʈ ��Ƶα�
		std::set<CGameObject*> deleteGameObj = {};
		for (CGameObject* gameObj : mGameObjects)
		{
			if (gameObj->FnGetState()
				== CGameObject::eState::Dead)
				deleteGameObj.insert(gameObj);
		}

		// daed ������Ʈ ���ܽ�Ű�� layer����
		typedef std::vector<CGameObject*>::iterator GameObjectIter;
		for (GameObjectIter iter = mGameObjects.begin()
			; iter != mGameObjects.end(); )
		{
			std::set<CGameObject*>::iterator deleteIter = deleteGameObj.find(*(iter));

			if (deleteIter != deleteGameObj.end())
			{
				iter = mGameObjects.erase(iter);
				continue;
			}

			iter++;
		}

		//�޸� ����
		for (CGameObject* gameObj : deleteGameObj)
		{
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void CLayer::FnAddGameObject(CGameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}
