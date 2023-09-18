#include "CJalapeno.h"

#include "CPlants.h"
#include "CCards.h"

namespace yha
{
	//CGameObject* CJalapeno::mBG = nullptr;
	CGameObject* CJalapeno::mJalapeno[MAX_JALAPENO] = {};
	//CGameObject* CJalapeno::mJalapenoExplode[MAX_JALAPENO] = {};

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

		////-------------------------------------
		//// infoPlants - animator
		////-------------------------------------
		//// Jalapeno
		//std::shared_ptr<CTexture> atlas_Jalapeno
		//	= CResources::FnLoad<CTexture>(L"Jalapeno", L"..\\Resources\\Texture\\MyGame\\Plants\\Jalapeno\\Jalapeno.png");
		//CPlants::mPlants[_idx].animator->FnCreate(
		//	// name,		atlas,			leftTop
		//	L"Jalapeno",	atlas_Jalapeno,	Vector2(0.0f, 0.0f)
		//	// size,						columnLength,	offset,			duration
		//	, Vector2(816.f / 8.f, 133.f),	8,				Vector2::Zero,	0.08f
		//);

		//// Jalapeno_Explode
		//std::shared_ptr<CTexture> atlas_Jalapeno_Explode
		//	= CResources::FnLoad<CTexture>(L"Jalapeno_Explode", L"..\\Resources\\Texture\\MyGame\\Plants\\Jalapeno\\Jalapeno_Explode.png");
		//CPlants::mPlants[_idx].animator->FnCreate(
		//	// name,				atlas,					leftTop
		//	L"Jalapeno_Explode",	atlas_Jalapeno_Explode, Vector2(0.0f, 0.0f)
		//	// size,							columnLength,	offset,			duration
		//	//, Vector2(9060.0f / 8.f, 196.f),	8,				Vector2::Zero,	0.08f
		//	, Vector2(6040.f / 8.f / 1.f, 131.f / 1.f), 8, Vector2::Zero, 0.08f //6040.f * 131.f
		//);

		////CPlants::mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.f, (131.f * 5.f) / 6040.f, 0.f)); //1990 * 1309

		//-------------------------------------
		// infoPlants - collider
		//-------------------------------------
		//CPlants::mPlants[_idx].collider->FnSetSize(Vector2(5.f, 5.f));

		CPlants::mPlants[_idx].isPlanted = true;
		CPlants::mPlants[_idx].plantsType = CCards::FnGetPickedCardType();

		mJalapeno_0 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
		CMeshRenderer* mr = mJalapeno_0->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_0"));
		mJalapeno_0->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

		CJalapeno::mChkSecond = 0.f;
		++mCntTmp;
		CPlants::FnChangeStatus(_idx, eStatusType::End);
		CPlants::FnChangeStatus(_idx, eStatusType::Idle);

		//if (0 == mCntTmp)
		//{
		//	mJalapeno_0 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
		//	CMeshRenderer* mr = mJalapeno_0->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_0"));
		//	mJalapeno_0->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

		//	CCommonObjects::mChkSecond = 0.f;
		//	++mCntTmp;
		//	//CPlants::FnChangeStatus(_idx, eStatusType::End);
		//	//CPlants::FnChangeStatus(_idx, eStatusType::Idle);
		//}
		//else if (0.2f <= mChkSecond && 1 == mCntTmp)
		//{
		//	object::FnDestroy(mJalapeno_0);

		//	mJalapeno_1 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapeno_1->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_1"));
		//	mJalapeno_1->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)); //69 * 89

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.2f <= mChkSecond && 2 == mCntTmp)
		//{
		//	mJalapeno_1->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapeno_1->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapeno_2 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapeno_2->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_2"));
		//	mJalapeno_2->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)); //69 * 89

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.2f <= mChkSecond && 3 == mCntTmp)
		//{
		//	mJalapeno_2->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapeno_2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapeno_3 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapeno_3->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_3"));
		//	mJalapeno_3->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)); //69 * 89

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.2f <= mChkSecond && 4 == mCntTmp)
		//{
		//	mJalapeno_3->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapeno_3->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapeno_4 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapeno_4->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_4"));
		//	mJalapeno_4->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)); //69 * 89

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.2f <= mChkSecond && 5 == mCntTmp)
		//{
		//	mJalapeno_4->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapeno_4->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapeno_5 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapeno_5->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_5"));
		//	mJalapeno_5->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)); //69 * 89

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.2f <= mChkSecond && 6 == mCntTmp)
		//{
		//	mJalapeno_5->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapeno_5->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapeno_6 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapeno_6->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_6"));
		//	mJalapeno_6->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)); //69 * 89

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.2f <= mChkSecond && 7 == mCntTmp)
		//{
		//	mJalapeno_6->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapeno_6->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapeno_7 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapeno_7->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_7"));
		//	mJalapeno_7->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)); //69 * 89

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.2f <= mChkSecond && 8 == mCntTmp)
		//{
		//	mJalapeno_7->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapeno_7->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_0->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_0"));
		//	mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.1f <= mChkSecond && 9 == mCntTmp)
		//{
		//	mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_1 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_1->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_1"));
		//	mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.1f <= mChkSecond && 10 == mCntTmp)
		//{
		//	mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_2 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_2->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_2"));
		//	mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.1f <= mChkSecond && 11 == mCntTmp)
		//{
		//	mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_3 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_3->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_3"));
		//	mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.1f <= mChkSecond && 12 == mCntTmp)
		//{
		//	mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_4 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_4->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_4"));
		//	mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.1f <= mChkSecond && 13 == mCntTmp)
		//{
		//	mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_5 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_5->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_5"));
		//	mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.1f <= mChkSecond && 14 == mCntTmp)
		//{
		//	mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_6 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_6->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_6"));
		//	mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (0.1f <= mChkSecond && 15 == mCntTmp)
		//{
		//	mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//	mJalapenoExplode_7 = object::FnInstantiate<CGameObject>(Vector3(0.9f, -0.2f, POS_Z_DEFAULT), eLayerType::UI2);
		//	CMeshRenderer* mr = mJalapenoExplode_7->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_7"));
		//	mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

		//	mChkSecond = 0.f;
		//	++mCntTmp;
		//}
		//else if (16 == mCntTmp)
		//{
		//	mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		//	mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
		//}




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
		//case eColliderStateType::Fin:// ÁÖÀÇ - Idle
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
			
			CJalapeno::mChkSecond;
			int a = 0;

			CJalapeno::mChkSecond += CTime::FnDeltaTime();
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::FnChangeStatus(_idx, eStatusType::Idle);

			int y = 0;
			float limitTime = 0.1f;
			CGameObject* nowJalapenoTmp = nullptr;
			 
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

			if (0.1f <= mChkSecond && 1 == mCntTmp)
			{
				object::FnDestroy(mJalapeno_0);

				mJalapeno_1 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				CMeshRenderer* mr = mJalapeno_1->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_1"));
				mJalapeno_1->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 2 == mCntTmp)
			{
				mJalapeno_1->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapeno_1->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mJalapeno_2 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				CMeshRenderer* mr = mJalapeno_2->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_2"));
				mJalapeno_2->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 3 == mCntTmp)
			{
				mJalapeno_2->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapeno_2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mJalapeno_3 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				CMeshRenderer* mr = mJalapeno_3->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_3"));
				mJalapeno_3->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 4 == mCntTmp)
			{
				mJalapeno_3->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapeno_3->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mJalapeno_4 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				CMeshRenderer* mr = mJalapeno_4->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_4"));
				mJalapeno_4->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 5 == mCntTmp)
			{
				mJalapeno_4->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapeno_4->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mJalapeno_5 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				CMeshRenderer* mr = mJalapeno_5->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_5"));
				mJalapeno_5->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 6 == mCntTmp)
			{
				mJalapeno_5->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapeno_5->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mJalapeno_6 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				CMeshRenderer* mr = mJalapeno_6->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_6"));
				mJalapeno_6->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 7 == mCntTmp)
			{
				mJalapeno_6->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapeno_6->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mJalapeno_7 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				CMeshRenderer* mr = mJalapeno_7->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_Jalapeno_7"));
				mJalapeno_7->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}




			else if (0.2f <= mChkSecond && 8 == mCntTmp)
			{
				mJalapeno_7->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapeno_7->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				//mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
				nowJalapenoTmp = mJalapenoExplode_0;
				switch (y)
				{
				case 1:
					mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}

				CMeshRenderer* mr = mJalapenoExplode_0->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_0"));
				mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 9 == mCntTmp)
			{
				mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				nowJalapenoTmp = mJalapenoExplode_1;
				switch (y)
				{
				case 1:
					mJalapenoExplode_1 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_1 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_1 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_1 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_1 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}

				CMeshRenderer* mr = mJalapenoExplode_1->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_1"));
				mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 10 == mCntTmp)
			{
				mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				nowJalapenoTmp = mJalapenoExplode_2;
				switch (y)
				{
				case 1:
					mJalapenoExplode_2 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_2 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_2 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_2 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_2 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}
				CMeshRenderer* mr = mJalapenoExplode_2->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_2"));
				mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 11 == mCntTmp)
			{
				mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				nowJalapenoTmp = mJalapenoExplode_3;
				switch (y)
				{
				case 1:
					mJalapenoExplode_3 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_3 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_3 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_3 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_3 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}
				CMeshRenderer* mr = mJalapenoExplode_3->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_3"));
				mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 12 == mCntTmp)
			{
				mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				nowJalapenoTmp = mJalapenoExplode_4;
				switch (y)
				{
				case 1:
					mJalapenoExplode_4 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_4 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_4 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_4 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_4 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}
				CMeshRenderer* mr = mJalapenoExplode_4->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_4"));
				mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 13 == mCntTmp)
			{
				mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				nowJalapenoTmp = mJalapenoExplode_5;
				switch (y)
				{
				case 1:
					mJalapenoExplode_5 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_5 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_5 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_5 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_5 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}
				CMeshRenderer* mr = mJalapenoExplode_5->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_5"));
				mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 14 == mCntTmp)
			{
				mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				nowJalapenoTmp = mJalapenoExplode_6;
				switch (y)
				{
				case 1:
					mJalapenoExplode_6 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_6 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_6 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_6 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_6 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}
				CMeshRenderer* mr = mJalapenoExplode_6->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_6"));
				mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (0.1f <= mChkSecond && 15 == mCntTmp)
			{
				mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				nowJalapenoTmp = mJalapenoExplode_7;
				switch (y)
				{
				case 1:
					mJalapenoExplode_7 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
					break;
				case 2:
					mJalapenoExplode_7 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
					break;
				case 3:
					mJalapenoExplode_7 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
					break;
				case 4:
					mJalapenoExplode_7 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
					break;
				case 5:
					mJalapenoExplode_7 = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
					break;
				}
				CMeshRenderer* mr = mJalapenoExplode_7->FnAddComponent<CMeshRenderer>();
				mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
				mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_7"));
				mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

				mChkSecond = 0.f;
				++mCntTmp;
				CPlants::FnChangeStatus(_idx, eStatusType::End);
				//CPlants::FnChangeStatus(_idx, eStatusType::Attack);
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			else if (16 == mCntTmp)
			{
				mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				//object::FnDestroy(mJalapenoExplode_7);

				mChkSecond = 0.f;
				mCntTmp = 0;

				CPlants::FnChangeStatus(_idx, eStatusType::End);
				CPlants::FnChangeStatus(_idx, eStatusType::Dead);
			}
		}
		break;
		case eStatusType::Attack:
		{
			//bool flagDo = false;

			//CGameObject* prevJalapenoTmp = nullptr;
			//CGameObject* nowJalapenoTmp = nullptr;

			//CJalapeno::mChkSecond += CTime::FnDeltaTime();
			//CPlants::FnChangeStatus(_idx, eStatusType::End);
			//CPlants::FnChangeStatus(_idx, eStatusType::Attack);

			//int y = 0;
			//float limitTime = 0.1f;

			//if (0 <= _idx && 8 >= _idx)
			//	y = 1;
			//else if (9 <= _idx && 17 >= _idx)
			//	y = 2;
			//else if (18 <= _idx && 26 >= _idx)
			//	y = 3;
			//else if (27 <= _idx && 35 >= _idx)
			//	y = 4;
			//else if (36 <= _idx && 44 >= _idx)
			//	y = 5;

			//if (0.2f <= mChkSecond && 8 == mCntTmp)
			//{
			//	mJalapeno_7->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapeno_7->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	//mJalapenoExplode_0 = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
			//	nowJalapenoTmp = mJalapenoExplode_0;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}

			//	CMeshRenderer* mr = mJalapenoExplode_0->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_0"));
			//	mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO);

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (0.1f <= mChkSecond && 9 == mCntTmp)
			//{
			//	mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_0->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	nowJalapenoTmp = mJalapenoExplode_1;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}

			//	CMeshRenderer* mr = mJalapenoExplode_1->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_1"));
			//	mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (0.1f <= mChkSecond && 10 == mCntTmp)
			//{
			//	mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_1->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	nowJalapenoTmp = mJalapenoExplode_2;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}
			//	CMeshRenderer* mr = mJalapenoExplode_2->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_2"));
			//	mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (0.1f <= mChkSecond && 11 == mCntTmp)
			//{
			//	mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	nowJalapenoTmp = mJalapenoExplode_3;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}
			//	CMeshRenderer* mr = mJalapenoExplode_3->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_3"));
			//	mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (0.1f <= mChkSecond && 12 == mCntTmp)
			//{
			//	mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_3->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	nowJalapenoTmp = mJalapenoExplode_4;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}
			//	CMeshRenderer* mr = mJalapenoExplode_4->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_4"));
			//	mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (0.1f <= mChkSecond && 13 == mCntTmp)
			//{
			//	mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_4->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	nowJalapenoTmp = mJalapenoExplode_5;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}
			//	CMeshRenderer* mr = mJalapenoExplode_5->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_5"));
			//	mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (0.1f <= mChkSecond && 14 == mCntTmp)
			//{
			//	mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_5->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	nowJalapenoTmp = mJalapenoExplode_6;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}
			//	CMeshRenderer* mr = mJalapenoExplode_6->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_6"));
			//	mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (0.1f <= mChkSecond && 15 == mCntTmp)
			//{
			//	mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_6->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	nowJalapenoTmp = mJalapenoExplode_7;
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}
			//	CMeshRenderer* mr = mJalapenoExplode_7->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_7"));
			//	mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetScale(Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)); //1990 * 1309

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
			//else if (16 == mCntTmp)
			//{
			//	mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	mJalapenoExplode_7->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
			//	//object::FnDestroy(mJalapenoExplode_7);

			//	mChkSecond = 0.f;
			//	mCntTmp = 0;

			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Dead);
			//}



			//if (flagDo)
			//{
			//	//object::FnDestroy(prevJalapenoTmp);
			//	prevJalapenoTmp->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			//	prevJalapenoTmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

			//	//nowJalapenoTmp = object::FnInstantiate<CGameObject>(CCommonObjects::FnGetPosition(_idx), eLayerType::PlayerExplode);
			//	switch (y)
			//	{
			//	case 1:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_1), eLayerType::PlayerExplode);
			//		break;
			//	case 2:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_2), eLayerType::PlayerExplode);
			//		break;
			//	case 3:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_3), eLayerType::PlayerExplode);
			//		break;
			//	case 4:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_4), eLayerType::PlayerExplode);
			//		break;
			//	case 5:
			//		nowJalapenoTmp = object::FnInstantiate<CGameObject>(Vector3(POS_Y_JALAPENO_EXPLODE_5), eLayerType::PlayerExplode);
			//		break;
			//	}

			//	CMeshRenderer* mr = nowJalapenoTmp->FnAddComponent<CMeshRenderer>();
			//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//	//mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_1"));
			//	switch (mCntTmp)
			//	{
			//	case 8:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_0"));
			//		break;
			//	case 9:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_1"));
			//		break;
			//	case 10:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_2"));
			//		break;
			//	case 11:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_3"));
			//		break;
			//	case 12:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_4"));
			//		break;
			//	case 13:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_5"));
			//		break;
			//	case 14:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_6"));
			//		break;
			//	case 15:
			//		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GameObj_JalapenoExplode_7"));
			//		break;
			//	}

			//	nowJalapenoTmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_JALAPENO_EXPLODE);

			//	mChkSecond = 0.f;
			//	++mCntTmp;
			//	CPlants::FnChangeStatus(_idx, eStatusType::End);
			//	CPlants::FnChangeStatus(_idx, eStatusType::Attack);
			//}
		}
		break;
		case eStatusType::Attacked:
			break;
		case eStatusType::Dead:
		{
			CPlants::mPlants[_idx].isPlanted = false;
			CPlants::mPlants[_idx].plantsType = ePlantsType::End;
			CPlants::FnChangeStatus(_idx, eStatusType::End);
			CPlants::mPlants[_idx].isAttacked = false;
			CPlants::mPlants[_idx].attackedTime = 0.f;
		}
		break;
		}
	}//END-void CJalapeno::FnFsmManager
}