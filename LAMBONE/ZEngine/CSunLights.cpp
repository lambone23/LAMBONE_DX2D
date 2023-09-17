#include "CSunLights.h"

#include "CCards.h"
#include "CPlants.h"
#include "CBoard.h"

extern yha::CApplication MyApplication;

namespace yha
{
	int CSunLights::mSunLightScore = 0;
	float CSunLights::mChkSecond = 0;
	int CSunLights::mPrevRandomIdx_SunLightNatural = 999;

	CSunLights::infoSunLight CSunLights::mSunLights[MAX_PLANTS] = {};
	CSunLights::infoSunLight CSunLights::mSunLights_Natural[MAX_SUNLIGHT_NATURAL] = {};

	CSunLights::CSunLights()
	{
	}
	CSunLights::~CSunLights()
	{
	}

	void CSunLights::FnInitialize(int _idx, eSunLightType _inType)
	{
		if (eSunLightType::Sunflower == _inType)
		{
			//==================================================================
			// infoSunLight - sunLight
			//==================================================================
			mSunLights[_idx].sunLight = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::SunLight);

			CMeshRenderer* mr = mSunLights[_idx].sunLight->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			//==================================================================
			// animator
			//==================================================================
			CAnimator* at_SunLight = mSunLights[_idx].sunLight->FnAddComponent<CAnimator>();

			std::shared_ptr<CTexture> atlas_SunLight
				= CResources::FnLoad<CTexture>(L"SunLight", L"..\\Resources\\Texture\\MyGame\\Plants\\SunLight.png");
			at_SunLight->FnCreate(
				L"Idle"						// name
				, atlas_SunLight			// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(2574.f / 22.f, 117.f)	// size
				, 22						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);
			at_SunLight->FnPlayAnimation(L"Idle", true);

			//==================================================================
			// �ʱ�ȭ
			//==================================================================
			mSunLights[_idx].isShow			= true;
			mSunLights[_idx].cycleChkTime	= 0.f;

			// �ʱ�ȭ - Natural ���� ��� (�����Ⱚ ����)
			mSunLights[_idx].isArrived		= false;
			mSunLights[_idx].position		= POSITION_CLEAR;
			mSunLights[_idx].destination	= POSITION_CLEAR;
		}
		else if (eSunLightType::Natural == _inType)
		{
			//==================================================================
			// infoSunLight - sunLight
			//==================================================================
			mSunLights_Natural[_idx].sunLight = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::SunLightNatural);

			CMeshRenderer* mr = mSunLights_Natural[_idx].sunLight->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			//==================================================================
			// animator
			//==================================================================
			CAnimator* at_SunLight_Natural = mSunLights_Natural[_idx].sunLight->FnAddComponent<CAnimator>();

			std::shared_ptr<CTexture> atlas_SunLight_Natural
				= CResources::FnLoad<CTexture>(L"SunLight", L"..\\Resources\\Texture\\MyGame\\Plants\\SunLight.png");
			at_SunLight_Natural->FnCreate(
				L"Idle"						// name
				, atlas_SunLight_Natural	// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(2574.f / 22.f, 117.f)	// size
				, 22						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);
			at_SunLight_Natural->FnPlayAnimation(L"Idle", true);

			//==================================================================
			// �ʱ�ȭ
			//==================================================================
			mSunLights_Natural[_idx].isShow			= true;
			mSunLights_Natural[_idx].cycleChkTime	= 0.f;
			mSunLights_Natural[_idx].isArrived		= false;
			mSunLights_Natural[_idx].position		= POSITION_CLEAR;
			mSunLights_Natural[_idx].destination	= POSITION_CLEAR;
		}
	}//END-void CSunLights::FnInitialize

	void CSunLights::FnStart(int _idx)
	{
		mSunLights[_idx].isShow = false;
		mSunLights[_idx].cycleChkTime = 0.f;
	}//END-void CSunLights::FnStart

	void CSunLights::FnRemove(int _idx, eSunLightType _inType)
	{
		if (eSunLightType::Sunflower == _inType)
		{
			mSunLights[_idx].isShow			= false;
			mSunLights[_idx].cycleChkTime	= 0.f;
			mSunLights[_idx].isArrived		= false;
			mSunLights[_idx].position		= POSITION_CLEAR;
			mSunLights[_idx].destination	= POSITION_CLEAR;
			object::FnDestroy(mSunLights[_idx].sunLight);
		}
		else if (eSunLightType::Natural == _inType)
		{
			mSunLights_Natural[_idx].isShow			= false;
			mSunLights_Natural[_idx].cycleChkTime	= 0.f;
			mSunLights_Natural[_idx].isArrived		= false;
			mSunLights_Natural[_idx].position		= POSITION_CLEAR;
			mSunLights_Natural[_idx].destination	= POSITION_CLEAR;
			object::FnDestroy(mSunLights_Natural[_idx].sunLight);
		}
	}//END-void CSunLights::FnRemove

	void CSunLights::FnClickEvent(int _idx, POINT _MousePos)
	{
		//==================================================================
		// ���� - �޺� ����Ʈ ���� (Natural)
		//==================================================================
#pragma region SunLight_Natural
		for (int idx2 = 0; idx2 < 5; idx2++)
		{
			bool flagDo_ClickEvent = false;
			bool flagDo_ClickEvent2 = false;

			int idxBoard_1 = idx2;
			int idxBoard_2 = idx2 + 9;
			int idxBoard_3 = idx2 + 9 * 2;

			if (idxBoard_1 == _idx || idxBoard_2 == _idx || idxBoard_3 == _idx)
				flagDo_ClickEvent = true;

			if (flagDo_ClickEvent)
			{
				int idxSunLight_1 = idx2;
				int idxSunLight_2 = idx2 + 5;
				int idxSunLight_3 = idx2 + 5 * 2;

				bool isExistSunLight_1 = mSunLights_Natural[idxSunLight_1].isShow;
				bool isExistSunLight_2 = mSunLights_Natural[idxSunLight_2].isShow;
				bool isExistSunLight_3 = mSunLights_Natural[idxSunLight_3].isShow;

				if ((isExistSunLight_1 || isExistSunLight_2 || isExistSunLight_3)
					&& (false == CCards::FnGetFlagIsCardSelected())
					&& (false == CCommonObjects::FnGetFlagIsShovelSelected()))
				{
					switch (idx2)
					{
					case 0:
						if ((400.f <= _MousePos.x) && (465.f >= _MousePos.x))
							flagDo_ClickEvent2 = true;
						break;
					case 1:
						if ((530.f <= _MousePos.x) && (590.f >= _MousePos.x))
							flagDo_ClickEvent2 = true;
						break;
					case 2:
						if ((650.f <= _MousePos.x) && (715.f >= _MousePos.x))
							flagDo_ClickEvent2 = true;
						break;
					case 3:
						if ((780.f <= _MousePos.x) && (845.f >= _MousePos.x))
							flagDo_ClickEvent2 = true;
						break;
					case 4:
						if ((910.f <= _MousePos.x) && (975.f >= _MousePos.x))
							flagDo_ClickEvent2 = true;
						break;
					}
				}

				if (flagDo_ClickEvent2)
				{
					if (isExistSunLight_1)
					{
						////��TODO-DELETE-DebugPrint
						//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
						//TCHAR Temp[256] = { 0, };
						//_stprintf_s(Temp, L"mSunScore: % d -> %d \nidxSunLight: % d \nidxBoard : %d"
						//	, mSunLightScore, mSunLightScore + 25, idxSunLight_1, _idx);
						//MessageBox(Tmp_mHwnd, Temp, L"§", MB_OK);

						FnRemove(idxSunLight_1, eSunLightType::Natural);
						FnSetSunLightScore_isAdd(true, 25);
					}
					if (isExistSunLight_2)
					{
						////��TODO-DELETE-DebugPrint
						//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
						//TCHAR Temp[256] = { 0, };
						//_stprintf_s(Temp,L"mSunScore: % d -> %d \nidxSunLight: % d \nidxBoard : %d"
						//	, mSunLightScore, mSunLightScore + 25, idxSunLight_2, _idx);
						//MessageBox(Tmp_mHwnd, Temp, L"§", MB_OK);

						FnRemove(idxSunLight_2, eSunLightType::Natural);
						FnSetSunLightScore_isAdd(true, 25);
					}
					if (isExistSunLight_3)
					{
						////��TODO-DELETE-DebugPrint
						//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
						//TCHAR Temp[256] = { 0, };
						//_stprintf_s(Temp,L"mSunScore: % d -> %d \nidxSunLight: % d \nidxBoard : %d"
						//	, mSunLightScore, mSunLightScore + 25, idxSunLight_3, _idx);
						//MessageBox(Tmp_mHwnd, Temp, L"§", MB_OK);

						FnRemove(idxSunLight_3, eSunLightType::Natural);
						FnSetSunLightScore_isAdd(true, 25);
					}
				}//end-if (flagDo_ClickEvent2)
			}//end-if (flagDo)
		}//end-for (int idx2 = 0; idx2 < 5; idx2++)
#pragma endregion

		//==================================================================
		// ���� - �޺� ����Ʈ ���� (Sunflower)
		//==================================================================
#pragma region SunLight_Sunflower
		if ((true == mSunLights[_idx].isShow)
			&& (false == CCards::FnGetFlagIsCardSelected())
			&& (false == CCommonObjects::FnGetFlagIsShovelSelected()))
		{
			////��TODO-DELETE-DebugPrint
			//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			//TCHAR Temp[256] = { 0, };
			//_stprintf_s(Temp, L"mSunScore: % d -> %d", mSunLightScore, mSunLightScore + 25);
			//MessageBox(Tmp_mHwnd, Temp, L"§", MB_OK);

			FnRemove(_idx, eSunLightType::Sunflower);
			FnSetSunLightScore_isAdd(true, 25);
		}
#pragma endregion
	}//END-void CSunLights::FnClickEvent

	void CSunLights::FnManageSunLight_Sunflower()
	{
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			//-------------------------------------
			// ���� - �޺� �����ֱ� �ð�
			//-------------------------------------
			mSunLights[idx].cycleChkTime += (float)CTime::FnDeltaTime();

			//==================================================================
			// A : �����Ǿ� �ִ� ��� (Ȱ��ȭ -> ��Ȱ��ȭ)
			//==================================================================
			if ((true == mSunLights[idx].isShow)
				&& (7.f <= mSunLights[idx].cycleChkTime))
			{
				//-------------------------------------
				// ��Ȱ��ȭ - �޺�
				//-------------------------------------
				/*
					������ ������ �޺� ����Ʈ�� �ִ� ���
					&& ���� �ð��� 7�� �̻�
				*/
				FnRemove(idx, eSunLightType::Sunflower);
			}
			//==================================================================
			// B : �������� �ʾҰ�, �عٶ�Ⱑ �ɾ��� ��� (��Ȱ��ȭ -> Ȱ��ȭ)
			//==================================================================
			else if ((false == mSunLights[idx].isShow)
				&& (true == CPlants::mPlants[idx].isPlanted)
				&& (ePlantsType::Sunflower == CPlants::mPlants[idx].plantsType))
			{
				//-------------------------------------
				// ���� - �޺� ���� �ֱ�ð�
				//-------------------------------------
				/*
					�޺� ����Ʈ ������ ����
					���� �ֱ� �ð��� ����
				*/
				float limitTime = 0.f;
				int nowSunLightScore = FnGetSunLightScore();

				if (100 > nowSunLightScore)
					limitTime = 10.f;
				else if (100 <= nowSunLightScore && 200 > nowSunLightScore)
					limitTime = 15.f;
				else if (200 <= nowSunLightScore)
					limitTime = 20.f;

				//==================================================================
				// B-a : �޺� ���� ���� (���� �ð� 2�� ��)
				//==================================================================
				if ((limitTime - 2.f <= mSunLights[idx].cycleChkTime)
					&& (limitTime > mSunLights[idx].cycleChkTime)
					&& (false == CPlants::mPlants[idx].isAttacked))
				{
					//-------------------------------------
					// ���� - Status (SunFlower)
					//-------------------------------------
					CPlants::FnChangeStatus(idx, eStatusType::Bright_OnlySunflower);
				}
				//==================================================================
				// B-b : �޺� ���� (���� �ð� ����)
				//==================================================================
				else if (limitTime <= mSunLights[idx].cycleChkTime)
				{
					//-------------------------------------
					// Ȱ��ȭ - �޺�
					//-------------------------------------
					FnInitialize(idx, eSunLightType::Sunflower);

					//-------------------------------------
					// ���� - Status (SunFlower)
					//-------------------------------------
					if (false == CPlants::mPlants[idx].isAttacked)
						CPlants::FnChangeStatus(idx, eStatusType::Idle);
				}
			}
		}//end-for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
	}//END-void CSunLights::FnManageSunLight_Sunflower

	void CSunLights::FnManageSunLight_Natural()
	{
		int cntFlagDo = 0; // ���� ���� ����

		//==================================================================
		// Ȯ�� - ���� ����
		//==================================================================
		/*
			�޺�(Natural) �ִ� ����, MAX_SUNLIGHT_NATURAL��ŭ �������
			���̻� �������� ����
		*/
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
			if (true == mSunLights_Natural[idx].isShow)
				++cntFlagDo;

		//==================================================================
		// ����
		//==================================================================
		if (cntFlagDo < MAX_SUNLIGHT_NATURAL)
		{
			//-------------------------------------
			// ���� - �޺� ���� �ֱ�ð�
			//-------------------------------------
			/*
				�޺� ����Ʈ ������ ����
				���� �ֱ� �ð��� ����
			*/
			float limitTime = 0.f;
			int nowSunLightScore = FnGetSunLightScore();

			if (100 > nowSunLightScore)
				limitTime = 10.f;
			else if (100 <= nowSunLightScore && 200 > nowSunLightScore)
				limitTime = 15.f;
			else if (200 <= nowSunLightScore)
				limitTime = 20.f;

			if (limitTime <= mChkSecond)
			{
				//-------------------------------------
				// ���� ��ǥ ����
				//-------------------------------------
				//srand((unsigned int)CTime::FnDeltaTime());
				srand((unsigned int)time(NULL));
				int random = rand();		// �������
				int idx = 0;				// ���� ��ǥ //(�ִ� - �ּ� + 1) + �ּ�
				int conversionIdx = 0;		// ��ȯ�� ��ǥ

				//-------------------------------------
				// ������ ���� Ȯ��
				//-------------------------------------
				while (true)
				{
					idx = rand() % MAX_SUNLIGHT_NATURAL;

					if ((false == mSunLights_Natural[idx].isShow)
						&& (mPrevRandomIdx_SunLightNatural != idx))
						break;
				}

				//-------------------------------------
				// ����
				//-------------------------------------
				FnInitialize(idx, eSunLightType::Natural);

				//-------------------------------------
				// ��ǥ ��ȯ (3*5) -> (5*9)
				//-------------------------------------
				if (5 > idx)
					conversionIdx = idx;
				else if ((5 <= idx) && (9 >= idx))
					conversionIdx = idx + 4;
				else if ((10 <= idx) && (14 >= idx))
					conversionIdx = idx + 8;

				//-------------------------------------
				// ��ǥ(������) ����
				//-------------------------------------
				Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
				posNumbSet = CCommonObjects::FnGetPosition(conversionIdx);
				posNumbSet.x -= 0.2f;
				posNumbSet.y -= 0.2f;
				posNumbSet.z = POS_Z_FRONT_2;
				mSunLights_Natural[idx].destination = posNumbSet;

				posNumbSet.y = 2.f;	// ����ȭ��� �� ��
				mSunLights_Natural[idx].position = posNumbSet;

				//-------------------------------------
				// �ʱ�ȭ - �� ī����(�޺� ������)
				//-------------------------------------
				FnSetChkSecond(0);

				//-------------------------------------
				// ���� - ��ǥ ���Ű�
				//-------------------------------------
				mPrevRandomIdx_SunLightNatural = idx;
			}
		}//end-if (flagDo)

		//==================================================================
		// ���� - ��ǥ
		//==================================================================
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
		{
			if (true == mSunLights_Natural[idx].isShow)
			{
				float now = mSunLights_Natural[idx].position.y;
				float destination = mSunLights_Natural[idx].destination.y;

				if ((false == mSunLights_Natural[idx].isArrived)
					&& (destination >= now))
				{// ������ ������ ���
					mSunLights_Natural[idx].isArrived = true;
					mSunLights_Natural[idx].cycleChkTime = 0.f;
				}
				else if (false == mSunLights_Natural[idx].isArrived)
				{// ������ ���� ���� ���
					// ����
					mSunLights_Natural[idx].position.y -= 0.5f * CTime::FnDeltaTime();
				}
			}
		}

		//==================================================================
		// ��Ȱ��ȭ - �޺�
		//==================================================================
		/*
			������ ������ �޺� ����Ʈ�� �ִ� ���
			&& ���� �ð��� 7�� �̻�
		*/
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
		{
			mSunLights_Natural[idx].cycleChkTime += CTime::FnDeltaTime();

			if ((true == mSunLights_Natural[idx].isShow)
				&& (true == mSunLights_Natural[idx].isArrived)
				&& (7.f <= mSunLights_Natural[idx].cycleChkTime))
			{
				FnRemove(idx, eSunLightType::Natural);
			}
		}
	}//END-void CSunLights::FnManageSunLight_Natural

	void CSunLights::FnDraw()
	{// �޺� �������ο� ���� Ȱ��ȭ

		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			// made by Sunflower
			if (true == mSunLights[idx].isShow)
			{
				Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
				posNumbSet = CCommonObjects::FnGetPosition(idx);
				posNumbSet.y -= 0.1f;
				posNumbSet.z = POS_Z_FRONT_1;
				mSunLights[idx].sunLight->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
			}

			// made by Natural
			if ((idx < MAX_SUNLIGHT_NATURAL)
				&& (true == mSunLights_Natural[idx].isShow))
			{
				mSunLights_Natural[idx].sunLight->FnGetComponent<CTransform>()->FnSetPosition(mSunLights_Natural[idx].position);
			}
		}
	}//END-void CSunLights::FnDrawSunLights
}