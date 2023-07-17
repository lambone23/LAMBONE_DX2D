#include "CCollisionManager.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CLayer.h"
#include "CCollider2D.h"

namespace yha
{
	std::bitset<LAYER_MAX> CCollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CCollisionManager::mCollisionMap = {};

	void CCollisionManager::FnInitialize()
	{
	}

	void CCollisionManager::FnUpdate()
	{
		for (UINT column = 0; column < (UINT)eLayerType::End; column++)
		{
			for (UINT row = 0; row < (UINT)eLayerType::End; row++)
			{
				if (mMatrix[row] == true)
				{
					FnLayerCollision((eLayerType)column, (eLayerType)row);
				}
			}
		}
	}//END-void CCollisionManager::FnUpdate

	void CCollisionManager::FnLayerCollision(eLayerType left, eLayerType right)
	{
		CScene* activeScene = CSceneManager::FnGetActiveScene();

		const std::vector<CGameObject*>& lefts = activeScene->FnGetLayer(left).FnGetGameObjects();
		const std::vector<CGameObject*>& rights = activeScene->FnGetLayer(right).FnGetGameObjects();

		for (CGameObject* leftObj : lefts)
		{
			CCollider2D* leftCol = leftObj->FnGetComponent<CCollider2D>();
			
			if (leftCol == nullptr)
				continue;

			if (leftObj->FnGetState() != CGameObject::eState::Active)
				continue;

			for (CGameObject* rightObj : rights)
			{
				CCollider2D* rightCol = rightObj->FnGetComponent<CCollider2D>();
				
				if (rightCol == nullptr)
					continue;

				if (leftObj == rightObj)
					continue;

				if (rightObj->FnGetState() != CGameObject::eState::Active)
					continue;

				FnColliderCollision(leftCol, rightCol);
			}
		}
	}//END-void CCollisionManager::FnLayerCollision

	void CCollisionManager::FnColliderCollision(CCollider2D* left, CCollider2D* right)
	{
		// �� �浹ü�� ID bool���� Ȯ��
		ColliderID id = {};
		id.left = left->FnGetColliderID();
		id.right = right->FnGetColliderID();

		// �浹������ �����´�
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (FnIntersect(left, right))
		{
			// �浹
			if (iter->second == false)
			{
				// ���� �浹
				left->FnOnCollisionEnter(right);
				right->FnOnCollisionEnter(left);
			}
			else
			{
				// �浹 ��
				left->FnOnCollisionStay(right);
				right->FnOnCollisionStay(left);
			}
		}
		else
		{
			// �浹 X
			if (iter->second == true)
			{
				// �浹�ϰ� �ִٰ� ������
				left->FnOnCollisionExit(right);
				right->FnOnCollisionExit(left);
			}
		}
	}//END-void CCollisionManager::FnColliderCollision

	bool CCollisionManager::FnIntersect(CCollider2D* left, CCollider2D* right)
	{
		// TODO : �и���, �� - �� �浹

		return false;
	}//END-bool CCollisionManager::FnIntersect

	void CCollisionManager::FnSetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT row = -1;
		UINT col = -1;

		UINT iLeft = (UINT)left;
		UINT iRight = (UINT)right;

		if (iLeft <= iRight)
		{
			row = iLeft;
			col = iRight;
		}
		else
		{
			row = iRight;
			col = iLeft;
		}

		mMatrix[col][row] = enable;
	}//END-void CCollisionManager::FnSetLayer

	void CCollisionManager::FnClear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}//END-void CCollisionManager::FnClear
}
