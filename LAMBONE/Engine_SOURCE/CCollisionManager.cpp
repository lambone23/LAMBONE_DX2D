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

			iter->second = true;
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

			iter->second = false;
		}
	}//END-void CCollisionManager::FnColliderCollision

	bool CCollisionManager::FnIntersect(CCollider2D* left, CCollider2D* right)
	{
		// ■ TODO : 원 - 원 충돌

		//==================================================================
		// 분리축 이론 (SAT : Separating Axis Theorem)
		//==================================================================
		/*
			두 다면체를 어떤 축에 투영시켰을 때,
			투영 구간이 서로 겹치지 않을 경우
			그 축을 분리축이라 함.

			두 다면체 사이에
			분리축이 하나라도 존재할 경우,
			두 다면체는 서로 겹치지 않은 상태.

			분리축이란? 두 물체를 나눌 수 있는 평행한 선
			어떤 변의 N (Normal vector) 의 수직은 두 물체의 분리축이 될 수 있다.
			충돌 판별할 도형 중 한 변의 수직인 법선 벡터를 구한다.
		*/

		//-------------------------------------
		// Rect (Cf)CRenderer::FnLoadMesh)
		//-------------------------------------
		// Rect vs Rect 
		// 0 --- 1
		// |     |
		// 3 --- 2

		// 로컬 좌표계
		Vector3 arrLocalPos[4] =
		{
		   Vector3{-0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, 0.5f, 0.0f}
		   ,Vector3{0.5f, -0.5f, 0.0f}
		   ,Vector3{-0.5f, -0.5f, 0.0f}
		};

		// 충돌체의 위치 정보
		CTransform* leftTr = left->FnGetOwner()->FnGetComponent<CTransform>();
		CTransform* rightTr = right->FnGetOwner()->FnGetComponent<CTransform>();

		// 로컬 좌표계 -> 월드 좌표계
		Matrix leftMatrix = leftTr->FnGetMatrix();
		Matrix rightMatrix = rightTr->FnGetMatrix();

		//-------------------------------------
		// 분리축 4개 생성
		//-------------------------------------
		Vector3 Axis[4] = {};

		/*
			(Cf)CCollider2D::mSize)
			본 게임 엔진의 충돌체는
			실제 물체보다 크게 그릴 수 있도록
			mSize가 존재하므로
			충돌 시, 그 크기로 계산해야 함.
		*/
		Vector3 leftScale = Vector3(left->FnGetSize().x, left->FnGetSize().y, 1.0f);
		Vector3 rightScale = Vector3(right->FnGetSize().x, right->FnGetSize().y, 1.0f);

		/*
			leftMatrix, rightMatrix 자체로 쓸 수 없다.
			leftScale, rightScale 크기가 적용된 걸로 다시 만들어야 함.
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
		// 분리축 4개의 Z값을 동일선상으로 옮김
		//-------------------------------------
		for (size_t i = 0; i < 4; i++)
			Axis[i].z = 0.0f;

		//-------------------------------------
		// 거리 구하기
		//-------------------------------------
		Vector3 vc = leftTr->FnGetPosition() - rightTr->FnGetPosition();
		vc.z = 0.0f; // 현재 2D지만 앞에 그려질건지 뒤에 그려질건지 정렬용으로 z값을 사용중

		//-------------------------------------
		// 분리축별로 연산
		//-------------------------------------
		Vector3 centerDir = vc;
		
		for (size_t i = 0; i < 4; i++)
		{
			// 분리축을 하나씩 가져와서
			Vector3 vA = Axis[i];

			// 투영시켰을 때의 거리
			float projDistance = 0.0f;

			// 투영시킨 거리를 계산
			for (size_t j = 0; j < 4; j++)
			{
				// 절대값 함수 사용 : 길이만 알면 된다. 양수인지 음수인지 중요하지 않음.
				// 내적 함수 사용 : 분리축 내적 (다른 분리축과의 내적한 것에 2로 나누기)
				projDistance += fabsf(Axis[j].Dot(vA) / 2.0f);
			}

			/*	
				projDistance(4개를 더한 길이) 길이보다
				centerDir 과 분리축하고 내적한 결과값이 더 길다면, 충돌하지 않음.

				4개 중에 하나라도 이 경우가 발생하면, 충돌 X
			*/
			if (projDistance < fabsf(centerDir.Dot(vA)))
				return false;
		}

		// 충돌 O
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
