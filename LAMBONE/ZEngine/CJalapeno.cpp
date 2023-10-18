#include "CJalapeno.h"

#include "CPlants.h"
#include "CCards.h"

namespace yha
{
	//CGameObject* CJalapeno::mJalapeno[MAX_JALAPENO] = {};

	CGameObject* CJalapeno::mJalapeno_0 = nullptr;
	CGameObject* CJalapeno::mJalapeno_1 = nullptr;
	CGameObject* CJalapeno::mJalapeno_2 = nullptr;
	CGameObject* CJalapeno::mJalapeno_3 = nullptr;
	CGameObject* CJalapeno::mJalapeno_4 = nullptr;
	CGameObject* CJalapeno::mJalapeno_5 = nullptr;
	CGameObject* CJalapeno::mJalapeno_6 = nullptr;
	CGameObject* CJalapeno::mJalapeno_7 = nullptr;

	CGameObject* CJalapeno::mJalapenoExplode_0 = nullptr;
	CGameObject* CJalapeno::mJalapenoExplode_1 = nullptr;
	CGameObject* CJalapeno::mJalapenoExplode_2 = nullptr;
	CGameObject* CJalapeno::mJalapenoExplode_3 = nullptr;
	CGameObject* CJalapeno::mJalapenoExplode_4 = nullptr;
	CGameObject* CJalapeno::mJalapenoExplode_5 = nullptr;
	CGameObject* CJalapeno::mJalapenoExplode_6 = nullptr;
	CGameObject* CJalapeno::mJalapenoExplode_7 = nullptr;

	float CJalapeno::mChkSecond = 0.f;
	int CJalapeno::mCntTmp = 0;

	CJalapeno::CJalapeno()
	{
	}
	CJalapeno::~CJalapeno()
	{
	}

	void CJalapeno::FnInitialize(int _idx)
	{
		//CPlants::mPlants[_idx].plants->FnSetName(L"GrassDay_Jalapeno_" + _idx);

		//-------------------------------------
		// infoPlants - collider
		//-------------------------------------
		//CPlants::mPlants[_idx].collider->FnSetSize(Vector2(5.f, 5.f));

		CPlants::mPlants[_idx].isPlanted = true;
		CPlants::mPlants[_idx].plantsType = CCards::FnGetPickedCardType();

		CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
		CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_0"));
		CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

		mChkSecond = 0.f;
		++mCntTmp;
		CPlants::FnChangeStatus(_idx, eStatusType::End);
		CPlants::FnChangeStatus(_idx, eStatusType::Idle);

	}//END-void CJalapeno::FnInitialize

	void CJalapeno::FnColliderManager(int _idx)
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
		//case eColliderStateType::Fin:// 주의 - Idle
		//{

		//}
		//break;
		//default:
		//	break;
		//}
	}//END-void CJalapeno::FnColliderManager

	void CJalapeno::FnFsmManager(int _idx)
	{
		switch (CPlants::mPlants[_idx].statusType)
		{
		case eStatusType::Idle:
		{
			//CPlants::mPlants[_idx].animator->FnPlayAnimation(L"Jalapeno_Explode", true);
			//bool flagComplete = CPlants::mPlants[_idx].animator->FnFindAnimation(L"Jalapeno_Explode")->FnIsComplete();

			//if (flagComplete)
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			
			FnJalapeno(_idx);
		}
		break;
		case eStatusType::Attack:
		{
		}
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
	}//END-void CJalapeno::FnFsmManager

	void CJalapeno::FnJalapeno(int _idx)
	{
		mChkSecond += CTime::FnDeltaTime();
		CPlants::FnChangeStatus(_idx, eStatusType::End);
		CPlants::FnChangeStatus(_idx, eStatusType::Idle);

		//float limitTime = 0.1f;
		//CGameObject* nowJalapenoTmp = nullptr;

		int y = 0;
		// 인덱스 값으로 폭발할 행을 찾기 위한 y
		if (0 <= _idx && 8 >= _idx)
			y = 1;
		else if (9 <= _idx && 17 >= _idx)
			y = 2;
		else if (18 <= _idx && 26 >= _idx)
			y = 3;
		else if (27 <= _idx && 35 >= _idx)
			y = 4;
		else if (36 <= _idx && 44 >= _idx)
			y = 5;

		//-------------------------------------
		// Jalapeno
		//-------------------------------------
		if (0.1f <= mChkSecond && 1 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

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
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_2"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

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
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_3"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

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
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_4"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

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
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_5"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

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
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_6"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 7 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_7"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		//-------------------------------------
		// JalapenoExplode
		//-------------------------------------
		else if (0.2f <= mChkSecond && 8 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::Player);
			//nowJalapenoTmp = mJalapenoExplode_0;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}

			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_0"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 9 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//nowJalapenoTmp = mJalapenoExplode_1;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}

			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_1"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 10 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//nowJalapenoTmp = mJalapenoExplode_2;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_2"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 11 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//nowJalapenoTmp = mJalapenoExplode_3;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_3"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 12 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//nowJalapenoTmp = mJalapenoExplode_4;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_4"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 13 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//nowJalapenoTmp = mJalapenoExplode_5;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_5"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 14 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//nowJalapenoTmp = mJalapenoExplode_6;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_6"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (0.1f <= mChkSecond && 15 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			//nowJalapenoTmp = CPlants::mPlants[_idx].plants;
			switch (y)
			{
			case 1:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::Player);
				break;
			case 2:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::Player);
				break;
			case 3:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::Player);
				break;
			case 4:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::Player);
				break;
			case 5:
				CPlants::mPlants[_idx].plants = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::Player);
				break;
			}
			CMeshRenderer* mr = CPlants::mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_7"));
			CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			mChkSecond = 0.f;
			++mCntTmp;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		}
		else if (16 == mCntTmp)
		{
			object::FnDestroy(CPlants::mPlants[_idx].plants);

			mChkSecond = 0.f;
			mCntTmp = 0;

			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Dead);
		}
	}//END-void CJalapeno::FnJalapeno
	
}