#include "CCherryBomb.h"

#include "CPlants.h"
#include "CCards.h"

namespace yha
{
	float CCherryBomb::mChkSecond = 0.f;
	int CCherryBomb::mCntTmp = 0;

	CCherryBomb::CCherryBomb()
	{
	}
	CCherryBomb::~CCherryBomb()
	{
	}

	void CCherryBomb::FnInitialize(int _idx)
	{
		CPlants::mPlants[_idx].isPlanted = true;
		CPlants::mPlants[_idx].plantsType = CCards::FnGetPickedCardType();

		CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
		CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBomb_0"));
		CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_CHERRYBOMB);

		mChkSecond = 0.f;
		++mCntTmp;
		CPlants::FnChangeStatus(_idx, eStatusType::End);
		CPlants::FnChangeStatus(_idx, eStatusType::Idle);
	}//END-void CCherryBomb::FnInitialize

	void CCherryBomb::FnColliderManager(int _idx)
	{
		//eColliderStateType nowState = CPlants::mPlants[_idx].collider->FnGetColliderState();

		//switch (nowState)
		//{
		//case eColliderStateType::Start:
		//{

		//}
		//break;
		//case eColliderStateType::Ing:
		//{
		//	CPlants::mPlants[_idx].attackedTime += CTime::FnDeltaTime();
		//}
		//break;
		//case eColliderStateType::Fin:// ¡÷¿« - Idle
		//{

		//}
		//break;
		//default:
		//	break;
		//}
	}//END-void CCherryBomb::FnColliderManager

	void CCherryBomb::FnFsmManager(int _idx)
	{
		switch (CPlants::mPlants[_idx].statusType)
		{
		case eStatusType::Idle:
		{
			FnCherryBomb(_idx);
		}
		break;
		case eStatusType::Attack:
			break;
		case eStatusType::Attacked:
			break;
		case eStatusType::Dead:
		{
			CPlants::mPlants[_idx].isPlanted	= false;
			CPlants::mPlants[_idx].plantsType	= ePlantsType::End;
			CPlants::mPlants[_idx].isAttacked	= false;
			CPlants::mPlants[_idx].attackedTime	= 0.f;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
		}
		break;
		}
	}//END-void CCherryBomb::FnFsmManager

	void CCherryBomb::FnCherryBomb(int _idx)
	{
		mChkSecond += CTime::FnDeltaTime();
		CPlants::FnChangeStatus(_idx, eStatusType::End);
		CPlants::FnChangeStatus(_idx, eStatusType::Idle);

		//-------------------------------------
		// CherryBomb
		//-------------------------------------
		if (0.1f <= mChkSecond && 1 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBomb_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_CHERRYBOMB);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 2 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBomb_2"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_CHERRYBOMB);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 3 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBomb_3"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_CHERRYBOMB);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 4 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBomb_4"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_CHERRYBOMB);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 5 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBomb_5"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_CHERRYBOMB);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 6 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBomb_6"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_CHERRYBOMB);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		//-------------------------------------
		// CherryBombExplode
		//-------------------------------------
		else if (0.1f <= mChkSecond && 7 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBombExplode_0"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.8f, (123.f * 1.8f) / 136.f, 0.f));

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (1.f <= mChkSecond && 8 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBombExplode_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (80.f * 3.f) / 80.f, 0.f));

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 9 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBombExplode_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(Vector3(2.5f, (80.f * 2.5f) / 80.f, 0.f));

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.07f <= mChkSecond && 10 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBombExplode_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(Vector3(2.f, (80.f * 2.f) / 80.f, 0.f));

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.07f <= mChkSecond && 11 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBombExplode_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.f, (80.f * 1.f) / 80.f, 0.f));

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.07f <= mChkSecond && 12 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_CherryBombExplode_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.3f, (80.f * 0.3f) / 80.f, 0.f));

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.07f <= mChkSecond && 13 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			mChkSecond = 0.f;
			mCntTmp = 0;

			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Dead);
		}
	}//END-void CCherryBomb::FnCherryBomb
	
}