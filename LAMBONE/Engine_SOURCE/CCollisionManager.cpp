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

			iter->second = true;
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

			iter->second = false;
		}
	}//END-void CCollisionManager::FnColliderCollision

	bool CCollisionManager::FnIntersect(CCollider2D* left, CCollider2D* right)
	{
		// �� TODO : �� - �� �浹

		//==================================================================
		// �и��� �̷� (SAT : Separating Axis Theorem)
		//==================================================================
		/*
			�� �ٸ�ü�� � �࿡ ���������� ��,
			���� ������ ���� ��ġ�� ���� ���
			�� ���� �и����̶� ��.

			�� �ٸ�ü ���̿�
			�и����� �ϳ��� ������ ���,
			�� �ٸ�ü�� ���� ��ġ�� ���� ����.

			�и����̶�? �� ��ü�� ���� �� �ִ� ������ ��
			� ���� N (Normal vector) �� ������ �� ��ü�� �и����� �� �� �ִ�.
			�浹 �Ǻ��� ���� �� �� ���� ������ ���� ���͸� ���Ѵ�.
		*/

		//-------------------------------------
		// Rect (Cf)CRenderer::FnLoadMesh)
		//-------------------------------------
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2

		// ���� ��ǥ��
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};

		// �浹ü�� ��ġ ����
		CTransform* leftTr = left->FnGetOwner()->FnGetComponent<CTransform>();
		CTransform* rightTr = right->FnGetOwner()->FnGetComponent<CTransform>();

		// ���� ��ǥ�� -> ���� ��ǥ��
		Matrix leftMatrix = leftTr->FnGetMatrix();
		Matrix rightMatrix = rightTr->FnGetMatrix();

		//-------------------------------------
		// �и��� 4�� ����
		//-------------------------------------
		Vector3 Axis[4] = {};

		/*
			(Cf)CCollider2D::mSize)
			�� ���� ������ �浹ü��
			���� ��ü���� ũ�� �׸� �� �ֵ���
			mSize�� �����ϹǷ�
			�浹 ��, �� ũ��� ����ؾ� ��.
		*/
		Vector3 leftScale = Vector3(left->FnGetSize().x, left->FnGetSize().y, 1.0f);
		Vector3 rightScale = Vector3(right->FnGetSize().x, right->FnGetSize().y, 1.0f);

		/*
			leftMatrix, rightMatrix ��ü�� �� �� ����.
			leftScale, rightScale ũ�Ⱑ ����� �ɷ� �ٽ� ������ ��.
		*/
		Matrix finalLeft = Matrix::CreateScale(leftScale);
		finalLeft *= leftMatrix;
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

		//-------------------------------------
		// �и��� 4���� Z���� ���ϼ������� �ű�
		//-------------------------------------
		for (size_t i = 0; i < 4; i++)
			Axis[i].z = 0.0f;

		//-------------------------------------
		// �Ÿ� ���ϱ�
		//-------------------------------------
		Vector3 vc = leftTr->FnGetPosition() - rightTr->FnGetPosition();
		vc.z = 0.0f; // ���� 2D���� �տ� �׷������� �ڿ� �׷������� ���Ŀ����� z���� �����

		//-------------------------------------
		// �и��ະ�� ����
		//-------------------------------------
		Vector3 centerDir = vc;
		
		for (size_t i = 0; i < 4; i++)
		{
			// �и����� �ϳ��� �����ͼ�
			Vector3 vA = Axis[i];

			// ���������� ���� �Ÿ�
			float projDistance = 0.0f;

			// ������Ų �Ÿ��� ���
			for (size_t j = 0; j < 4; j++)
			{
				// ���밪 �Լ� ��� : ���̸� �˸� �ȴ�. ������� �������� �߿����� ����.
				// ���� �Լ� ��� : �и��� ���� (�ٸ� �и������ ������ �Ϳ� 2�� ������)
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}

			/*	
				projDistance(4���� ���� ����) ���̺���
				centerDir �� �и����ϰ� ������ ������� �� ��ٸ�, �浹���� ����.

				4�� �߿� �ϳ��� �� ��찡 �߻��ϸ�, �浹 X
			*/
			if (projDistance < fabsf(centerDir.Dot(vA)))
				return false;
		}

		// �浹 O
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
