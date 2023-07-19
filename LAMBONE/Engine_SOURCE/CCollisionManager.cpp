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
				if (mMatrix[column][row] == true)
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
		// 두 충돌체의 ID bool값을 확인
		ColliderID id = {};
		id.left = left->FnGetColliderID();
		id.right = right->FnGetColliderID();

		// 충돌정보를 가져온다
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(id.id);

		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(id.id, false));
			iter = mCollisionMap.find(id.id);
		}

		if (FnIntersect(left, right))
		{
			// 충돌
			if (iter->second == false)
			{
				// 최초 충돌
				left->FnOnCollisionEnter(right);
				right->FnOnCollisionEnter(left);
			}
			else
			{
				// 충돌 중
				left->FnOnCollisionStay(right);
				right->FnOnCollisionStay(left);
			}
		}
		else
		{
			// 충돌 X
			if (iter->second == true)
			{
				// 충돌하고 있다가 나갈떄
				left->FnOnCollisionExit(right);
				right->FnOnCollisionExit(left);
			}
		}
	}//END-void CCollisionManager::FnColliderCollision

	bool CCollisionManager::FnIntersect(CCollider2D* left, CCollider2D* right)
	{
		// TODO : 분리축, 원 - 원 충돌

		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};

		CTransform* leftTr = left->FnGetOwner()->FnGetComponent<CTransform>();
		CTransform* rightTr = right->FnGetOwner()->FnGetComponent<CTransform>();

		Matrix leftMatrix = leftTr->FnGetMatrix();
		Matrix rightMatrix = rightTr->FnGetMatrix();

		Vector3 Axis[4] = {};

		Vector3 leftScale = Vector3(left->FnGetSize().x, left->FnGetSize().y, 1.0f);
		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMatrix;

		Vector3 rightScale = Vector3(right->FnGetSize().x, right->FnGetSize().y, 1.0f);
		Matrix finalRight = Matrix::CreateScale(rightScale);
		finalRight *= rightMatrix;

		Axis[0] = Vector3::Transform(arrLocalPos[1], finalLeft);
		Axis[1] = Vector3::Transform(arrLocalPos[3], finalLeft);
		Axis[2] = Vector3::Transform(arrLocalPos[1], finalRight);
		Axis[3] = Vector3::Transform(arrLocalPos[3], finalRight);

		Axis[0] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[1] -= Vector3::Transform(arrLocalPos[0], finalLeft);
		Axis[2] -= Vector3::Transform(arrLocalPos[0], finalRight);
		Axis[3] -= Vector3::Transform(arrLocalPos[0], finalRight);

		for (size_t i = 0; i < 4; i++)
			Axis[i].z = 0.0f;

		Vector3 vc = leftTr->FnGetPosition() - rightTr->FnGetPosition();
		vc.z = 0.0f;

		Vector3 centerDir = vc;
		for (size_t i = 0; i < 4; i++)
		{
			Vector3 vA = Axis[i];

			float projDistance = 0.0f;
			for (size_t j = 0; j < 4; j++)
			{
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}

			if (projDistance < fabsf(centerDir.Dot(vA)))
				return false;
		}

		return true;
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
