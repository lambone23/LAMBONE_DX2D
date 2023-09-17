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
			// 초기화
			//==================================================================
			mSunLights[_idx].isShow			= true;
			mSunLights[_idx].cycleChkTime	= 0.f;

			// 초기화 - Natural 전용 요소 (쓰레기값 방지)
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
			// 초기화
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
		// 갱신 - 햇빛 포인트 점수 (Natural)
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
						////■TODO-DELETE-DebugPrint
						//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
						//TCHAR Temp[256] = { 0, };
						//_stprintf_s(Temp, L"mSunScore: % d -> %d \nidxSunLight: % d \nidxBoard : %d"
						//	, mSunLightScore, mSunLightScore + 25, idxSunLight_1, _idx);
						//MessageBox(Tmp_mHwnd, Temp, L"짠", MB_OK);

						FnRemove(idxSunLight_1, eSunLightType::Natural);
						FnSetSunLightScore_isAdd(true, 25);
					}
					if (isExistSunLight_2)
					{
						////■TODO-DELETE-DebugPrint
						//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
						//TCHAR Temp[256] = { 0, };
						//_stprintf_s(Temp,L"mSunScore: % d -> %d \nidxSunLight: % d \nidxBoard : %d"
						//	, mSunLightScore, mSunLightScore + 25, idxSunLight_2, _idx);
						//MessageBox(Tmp_mHwnd, Temp, L"짠", MB_OK);

						FnRemove(idxSunLight_2, eSunLightType::Natural);
						FnSetSunLightScore_isAdd(true, 25);
					}
					if (isExistSunLight_3)
					{
						////■TODO-DELETE-DebugPrint
						//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
						//TCHAR Temp[256] = { 0, };
						//_stprintf_s(Temp,L"mSunScore: % d -> %d \nidxSunLight: % d \nidxBoard : %d"
						//	, mSunLightScore, mSunLightScore + 25, idxSunLight_3, _idx);
						//MessageBox(Tmp_mHwnd, Temp, L"짠", MB_OK);

						FnRemove(idxSunLight_3, eSunLightType::Natural);
						FnSetSunLightScore_isAdd(true, 25);
					}
				}//end-if (flagDo_ClickEvent2)
			}//end-if (flagDo)
		}//end-for (int idx2 = 0; idx2 < 5; idx2++)
#pragma endregion

		//==================================================================
		// 갱신 - 햇빛 포인트 점수 (Sunflower)
		//==================================================================
#pragma region SunLight_Sunflower
		if ((true == mSunLights[_idx].isShow)
			&& (false == CCards::FnGetFlagIsCardSelected())
			&& (false == CCommonObjects::FnGetFlagIsShovelSelected()))
		{
			////■TODO-DELETE-DebugPrint
			//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			//TCHAR Temp[256] = { 0, };
			//_stprintf_s(Temp, L"mSunScore: % d -> %d", mSunLightScore, mSunLightScore + 25);
			//MessageBox(Tmp_mHwnd, Temp, L"짠", MB_OK);

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
			// 갱신 - 햇빛 생성주기 시간
			//-------------------------------------
			mSunLights[idx].cycleChkTime += (float)CTime::FnDeltaTime();

			//==================================================================
			// A : 생성되어 있는 경우 (활성화 -> 비활성화)
			//==================================================================
			if ((true == mSunLights[idx].isShow)
				&& (7.f <= mSunLights[idx].cycleChkTime))
			{
				//-------------------------------------
				// 비활성화 - 햇빛
				//-------------------------------------
				/*
					기존에 생성된 햇빛 포인트가 있는 경우
					&& 기준 시간이 7초 이상
				*/
				FnRemove(idx, eSunLightType::Sunflower);
			}
			//==================================================================
			// B : 생성되지 않았고, 해바라기가 심어진 경우 (비활성화 -> 활성화)
			//==================================================================
			else if ((false == mSunLights[idx].isShow)
				&& (true == CPlants::mPlants[idx].isPlanted)
				&& (ePlantsType::Sunflower == CPlants::mPlants[idx].plantsType))
			{
				//-------------------------------------
				// 갱신 - 햇빛 생성 주기시간
				//-------------------------------------
				/*
					햇빛 포인트 점수에 따라
					생성 주기 시간을 변경
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
				// B-a : 햇빛 생성 직전 (기준 시간 2초 전)
				//==================================================================
				if ((limitTime - 2.f <= mSunLights[idx].cycleChkTime)
					&& (limitTime > mSunLights[idx].cycleChkTime)
					&& (false == CPlants::mPlants[idx].isAttacked))
				{
					//-------------------------------------
					// 갱신 - Status (SunFlower)
					//-------------------------------------
					CPlants::FnChangeStatus(idx, eStatusType::Bright_OnlySunflower);
				}
				//==================================================================
				// B-b : 햇빛 생성 (기준 시간 도달)
				//==================================================================
				else if (limitTime <= mSunLights[idx].cycleChkTime)
				{
					//-------------------------------------
					// 활성화 - 햇빛
					//-------------------------------------
					FnInitialize(idx, eSunLightType::Sunflower);

					//-------------------------------------
					// 갱신 - Status (SunFlower)
					//-------------------------------------
					if (false == CPlants::mPlants[idx].isAttacked)
						CPlants::FnChangeStatus(idx, eStatusType::Idle);
				}
			}
		}//end-for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
	}//END-void CSunLights::FnManageSunLight_Sunflower

	void CSunLights::FnManageSunLight_Natural()
	{
		int cntFlagDo = 0; // 생성 여부 결정

		//==================================================================
		// 확인 - 생성 여부
		//==================================================================
		/*
			햇빛(Natural) 최대 개수, MAX_SUNLIGHT_NATURAL만큼 기존재시
			더이상 생성하지 않음
		*/
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
			if (true == mSunLights_Natural[idx].isShow)
				++cntFlagDo;

		//==================================================================
		// 생성
		//==================================================================
		if (cntFlagDo < MAX_SUNLIGHT_NATURAL)
		{
			//-------------------------------------
			// 갱신 - 햇빛 생성 주기시간
			//-------------------------------------
			/*
				햇빛 포인트 점수에 따라
				생성 주기 시간을 변경
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
				// 랜덤 좌표 선정
				//-------------------------------------
				//srand((unsigned int)CTime::FnDeltaTime());
				srand((unsigned int)time(NULL));
				int random = rand();		// 버리기용
				int idx = 0;				// 랜덤 좌표 //(최대 - 최소 + 1) + 최소
				int conversionIdx = 0;		// 전환된 좌표

				//-------------------------------------
				// 기존재 여부 확인
				//-------------------------------------
				while (true)
				{
					idx = rand() % MAX_SUNLIGHT_NATURAL;

					if ((false == mSunLights_Natural[idx].isShow)
						&& (mPrevRandomIdx_SunLightNatural != idx))
						break;
				}

				//-------------------------------------
				// 생성
				//-------------------------------------
				FnInitialize(idx, eSunLightType::Natural);

				//-------------------------------------
				// 좌표 전환 (3*5) -> (5*9)
				//-------------------------------------
				if (5 > idx)
					conversionIdx = idx;
				else if ((5 <= idx) && (9 >= idx))
					conversionIdx = idx + 4;
				else if ((10 <= idx) && (14 >= idx))
					conversionIdx = idx + 8;

				//-------------------------------------
				// 좌표(도달점) 셋팅
				//-------------------------------------
				Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
				posNumbSet = CCommonObjects::FnGetPosition(conversionIdx);
				posNumbSet.x -= 0.2f;
				posNumbSet.y -= 0.2f;
				posNumbSet.z = POS_Z_FRONT_2;
				mSunLights_Natural[idx].destination = posNumbSet;

				posNumbSet.y = 2.f;	// 게임화면상 맨 위
				mSunLights_Natural[idx].position = posNumbSet;

				//-------------------------------------
				// 초기화 - 초 카운팅(햇빛 생성용)
				//-------------------------------------
				FnSetChkSecond(0);

				//-------------------------------------
				// 갱신 - 좌표 과거값
				//-------------------------------------
				mPrevRandomIdx_SunLightNatural = idx;
			}
		}//end-if (flagDo)

		//==================================================================
		// 갱신 - 좌표
		//==================================================================
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
		{
			if (true == mSunLights_Natural[idx].isShow)
			{
				float now = mSunLights_Natural[idx].position.y;
				float destination = mSunLights_Natural[idx].destination.y;

				if ((false == mSunLights_Natural[idx].isArrived)
					&& (destination >= now))
				{// 도달점 도착한 경우
					mSunLights_Natural[idx].isArrived = true;
					mSunLights_Natural[idx].cycleChkTime = 0.f;
				}
				else if (false == mSunLights_Natural[idx].isArrived)
				{// 도달점 도착 못한 경우
					// 낙하
					mSunLights_Natural[idx].position.y -= 0.5f * CTime::FnDeltaTime();
				}
			}
		}

		//==================================================================
		// 비활성화 - 햇빛
		//==================================================================
		/*
			기존에 생성된 햇빛 포인트가 있는 경우
			&& 기준 시간이 7초 이상
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
	{// 햇빛 생성여부에 따라 활성화

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