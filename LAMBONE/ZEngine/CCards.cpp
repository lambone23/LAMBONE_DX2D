#include "CCards.h"

#include "CSunLights.h"

extern yha::CApplication MyApplication;

namespace yha
{
	ePlantsType CCards::mPickedCardType = ePlantsType::End;
	int CCards::mCntPickedCard = 0;
	bool CCards::mFlagIsCardSelected = false;
	
	CCards::infoPickedCard CCards::mPickedCardList[MAX_CARDS_PICKED] = {};

	CGameObject* CCards::mCard_SunFlower_Disalbed	= nullptr;
	CGameObject* CCards::mCard_WallNut_Disalbed		= nullptr;
	CGameObject* CCards::mCard_PeaShooter_Disalbed	= nullptr;
	CGameObject* CCards::mCard_Chomper_Disalbed		= nullptr;
	CGameObject* CCards::mCard_Jalapeno_Disalbed	= nullptr;
	CGameObject* CCards::mCard_CherryBomb_Disalbed	= nullptr;

	CGameObject* CCards::mCard_SunFlower	= nullptr;
	CGameObject* CCards::mCard_WallNut		= nullptr;
	CGameObject* CCards::mCard_PeaShooter	= nullptr;
	CGameObject* CCards::mCard_Chomper		= nullptr;
	CGameObject* CCards::mCard_Jalapeno		= nullptr;
	CGameObject* CCards::mCard_CherryBomb	= nullptr;

	CCards::CCards()
	{
	}
	CCards::~CCards()
	{
		//==================================================================
		// Both
		// 0. Choose Plants
		// 1. Play
		//==================================================================
		object::FnDestroy(mCard_SunFlower_Disalbed);
		object::FnDestroy(mCard_WallNut_Disalbed);
		object::FnDestroy(mCard_PeaShooter_Disalbed);
		object::FnDestroy(mCard_Chomper_Disalbed);
		object::FnDestroy(mCard_Jalapeno_Disalbed);
		object::FnDestroy(mCard_CherryBomb_Disalbed);

		object::FnDestroy(mCard_SunFlower);
		object::FnDestroy(mCard_WallNut);
		object::FnDestroy(mCard_PeaShooter);
		object::FnDestroy(mCard_Chomper);
		object::FnDestroy(mCard_Jalapeno);
		object::FnDestroy(mCard_CherryBomb);
	}

	void CCards::FnInitialize()
	{
		//==================================================================
		// Card
		//==================================================================
#pragma region Resource_Card_Plants
		// Card_SunFlower
		mCard_SunFlower = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		CMeshRenderer* mr = mCard_SunFlower->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_WallNut
		mCard_WallNut = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_WallNut->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_WallNut"));
		mCard_WallNut->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_PeaShooter
		mCard_PeaShooter = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_PeaShooter->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_PeaShooter"));
		mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Chomper
		mCard_Chomper = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Chomper->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Chomper"));
		mCard_Chomper->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Jalapeno
		mCard_Jalapeno = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Jalapeno->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Jalapeno"));
		mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_CherryBomb
		mCard_CherryBomb = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_CherryBomb->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_CherryBomb"));
		mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
#pragma endregion

		//==================================================================
		// Card_Disalbed
		//==================================================================
#pragma region Resource_Card_Picked_Disalbed
		// Card_SunFlower_Disalbed
		mCard_SunFlower_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_SunFlower_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower_Disabled"));
		mCard_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_WallNut_Disalbed
		mCard_WallNut_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_WallNut_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_WallNut_Disabled"));
		mCard_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_PeaShooter_Disalbed
		mCard_PeaShooter_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_PeaShooter_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_PeaShooter_Disabled"));
		mCard_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Chomper_Disalbed
		mCard_Chomper_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Chomper_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Chomper_Disabled"));
		mCard_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Jalapeno_Disalbed
		mCard_Jalapeno_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Jalapeno_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Jalapeno_Disabled"));
		mCard_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_CherryBomb_Disalbed
		mCard_CherryBomb_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_CherryBomb_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_CherryBomb_Disabled"));
		mCard_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
#pragma endregion
	}//END-void CCards::FnInitialize

	void CCards::FnMakePickedCardList()
	{
		// mPickedList 목록 채우기
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			if (ePlantsType::End == mPickedCardList[idx].plantsType)
			{
				mPickedCardList[idx].plantsType = mPickedCardType;
				++mCntPickedCard;
				break;
			}
		}
	}//END-void CCards::FnMakePickedCardList

	bool CCards::FnChkPickedBefore(int _idx)
	{
		/* <form>
			[0]-SunFlower	[1]-PeaShooter	[2]-WallNut
			[3]-Chomper		[4]-Jalapeno	[5]-CherryBomb
		*/
		bool returnValue = false;

		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			if ((ePlantsType)_idx == mPickedCardList[idx].plantsType)
			{
				/*
					확인하려는 카드 넘버값(_idx)을
					선택된 카드 목록(mPickedCardList)과 비교하여
					넘버값(_idx)이 목록에 존재하는 경우

					즉, 해당카드가 이미 선택된 경우
				*/
				returnValue = true;
				break;
			}
		}

		return returnValue;
	}//END-bool CCards::FnChkPickedBefore

	void CCards::FnDrawWholeCardList()
	{
		for (int idx = 0; idx < MAX_CARDS_WHOLE; idx++)
		{
			/*
				선택된 카드 목록 값과 비교하여,
				현재 idx에 해당하는 카드가 선택된 카드인지 확인
			*/
			bool FlagChkPickedBefore = FnChkPickedBefore(idx);

			//==================================================================
			// 선택된 카드의 경우 - Disalbed로 표시
			//==================================================================
			if (FlagChkPickedBefore)
			{
				switch (idx)
				{
				case (int)ePlantsType::Sunflower:
					mCard_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::WallNut:
					mCard_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::PeaShooter:
					mCard_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Chomper:
					mCard_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Jalapeno:
					mCard_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::CherryBomb:
					mCard_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_1));
					break;
				default:
					break;
				}
			}
			//==================================================================
			// 선택되지 않은 카드의 경우 - Disalbed가 아닌 카드로 표시
			//==================================================================
			else
			{
				switch (idx)
				{
				case (int)ePlantsType::Sunflower:
					mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::WallNut:
					mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::PeaShooter:
					mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Chomper:
					mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Jalapeno:	// 4
					mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::CherryBomb:	// 5
					mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_1));
					break;
				default:
					break;
				}
			}
		}//end-for (int Chkidx = 0; Chkidx < MAXCARDS; Chkidx++)
	}//END-void CCards::FnDrawWholeCardList

	void CCards::FnDrawPickedCardList(eStepMode _step)
	{
		CGameObject* card_Picked_Tmp = nullptr;

		//==================================================================
		// 초기화 - 기존 Card목록
		//==================================================================
		if (eStepMode::Play == _step)
		{
			mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		}

		//==================================================================
		// mPickedList를 통해, Player로 사용할 Card목록 그리기
		//==================================================================
		/*
			- 카드 선택 모드의 경우
			햇빛포인트와 쿨타임에 상관없이
			무조건 활성화상태로
			목록 그리기

			- 플레이 모드의 경우
			햇빛 포인트와 쿨타임을 반영하여
			활성화상태 또는 비활성화 상태로
			목록 그리기
		*/
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			//-------------------------------------
			/// 값이 없으면 그리기 패스
			//-------------------------------------
			if (ePlantsType::End == mPickedCardList[idx].plantsType)
				continue;

			//-------------------------------------
			/// 그리기
			//-------------------------------------
			// 갱신 - 기준시간(카드 쿨타임) counting
			mPickedCardList[idx].coolTime += CTime::FnDeltaTime();

			// 카드 disabled 처리 여부
			bool flagMakeNotDisabled = false;

			int nowSunLightScore = CSunLights::FnGetSunLightScore();
			bool flagIsCoolTimeActive = mPickedCardList[idx].isCoolTimeActive;
			bool flagCoolTimeEnd = 10.f <= mPickedCardList[idx].coolTime ? true : false;
			
			// 선택된 카드 타입으로 card_Picked_Tmp 설정
			switch (mPickedCardList[idx].plantsType)
			{
			case ePlantsType::Sunflower:
			{
				bool falgIsEnoughPoint = 50 <= nowSunLightScore ? true : false;
				if ((eStepMode::Choose == _step)
					|| ((eStepMode::Play == _step) && !flagIsCoolTimeActive && falgIsEnoughPoint)
					|| ((eStepMode::Play == _step) && flagIsCoolTimeActive && flagCoolTimeEnd))
				{
					card_Picked_Tmp = mCard_SunFlower;
					flagMakeNotDisabled = true;
				}
				else
					card_Picked_Tmp = mCard_SunFlower_Disalbed;
			}
			break;
			case ePlantsType::WallNut:
			{
				bool falgIsEnoughPoint = 50 <= nowSunLightScore ? true : false;
				if ((eStepMode::Choose == _step)
					|| ((eStepMode::Play == _step) && !flagIsCoolTimeActive && falgIsEnoughPoint)
					|| ((eStepMode::Play == _step) && flagIsCoolTimeActive && flagCoolTimeEnd))
				{
					card_Picked_Tmp = mCard_WallNut;
					flagMakeNotDisabled = true;
				}
				else
					card_Picked_Tmp = mCard_WallNut_Disalbed;
			}
			break;
			case ePlantsType::PeaShooter:
			{
				bool falgIsEnoughPoint = 100 <= nowSunLightScore ? true : false;
				if ((eStepMode::Choose == _step)
					|| ((eStepMode::Play == _step) && !flagIsCoolTimeActive && falgIsEnoughPoint)
					|| ((eStepMode::Play == _step) && flagIsCoolTimeActive && flagCoolTimeEnd))
				{
					card_Picked_Tmp = mCard_PeaShooter;
					flagMakeNotDisabled = true;
				}
				else
					card_Picked_Tmp = mCard_PeaShooter_Disalbed;
			}
			break;
			case ePlantsType::Chomper:
			{
				bool falgIsEnoughPoint = 150 <= nowSunLightScore ? true : false;
				if ((eStepMode::Choose == _step)
					|| ((eStepMode::Play == _step) && !flagIsCoolTimeActive && falgIsEnoughPoint)
					|| ((eStepMode::Play == _step) && flagIsCoolTimeActive && flagCoolTimeEnd))
				{
					card_Picked_Tmp = mCard_Chomper;
					flagMakeNotDisabled = true;
				}
				else
					card_Picked_Tmp = mCard_Chomper_Disalbed;
			}
			break;
			case ePlantsType::Jalapeno:
			{
				bool falgIsEnoughPoint = 120 <= nowSunLightScore ? true : false;
				if ((eStepMode::Choose == _step)
					|| ((eStepMode::Play == _step) && !flagIsCoolTimeActive && falgIsEnoughPoint)
					|| ((eStepMode::Play == _step) && flagIsCoolTimeActive && flagCoolTimeEnd))
				{
					card_Picked_Tmp = mCard_Jalapeno;
					flagMakeNotDisabled = true;
				}
				else
					card_Picked_Tmp = mCard_Jalapeno_Disalbed;
			}
			break;
			case ePlantsType::CherryBomb:
			{
				bool falgIsEnoughPoint = 150 <= nowSunLightScore ? true : false;
				if ((eStepMode::Choose == _step)
					|| ((eStepMode::Play == _step) && !flagIsCoolTimeActive && falgIsEnoughPoint)
					|| ((eStepMode::Play == _step) && flagIsCoolTimeActive && flagCoolTimeEnd))
				{
					card_Picked_Tmp = mCard_CherryBomb;
					flagMakeNotDisabled = true;
				}
				else
					card_Picked_Tmp = mCard_CherryBomb_Disalbed;
			}
			break;
			}

			// 선택된 카드목록 그리기
			switch (idx)
			{
			case 0:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_1, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 1:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_2, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 2:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_3, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 3:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_4, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 4:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_5, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			}

			// 갱신 - 카드 활성화 여부, 기준시간(카드 쿨타임)End
			if (flagMakeNotDisabled)
			{
				mPickedCardList[idx].isDisabled = false;
				mPickedCardList[idx].isCoolTimeActive = false;
				mPickedCardList[idx].coolTime = 0.f;
			}
			else
				mPickedCardList[idx].isDisabled = true;

		}//end-for (int idx = 0; idx < MAXPICKED; idx++)

		card_Picked_Tmp = nullptr;
	}//END-void CCards::FnDrawPickedCardList

	void CCards::FnClickEvent_WholeCardList()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			bool flagMakeList = false;

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			// Card_SunFlower
			if ((320.f <= MousePos.x) && (480.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::Sunflower;
				flagMakeList = true;
			}

			// Card_WallNut
			if ((520.f <= MousePos.x) && (680.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::WallNut;
				flagMakeList = true;
			}

			// Card_PeaShooter
			if ((720.f <= MousePos.x) && (880.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::PeaShooter;
				flagMakeList = true;
			}

			// Card_Chomper
			if ((320.f <= MousePos.x) && (480.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::Chomper;
				flagMakeList = true;
			}

			// Card_Jalapeno
			if ((520.f <= MousePos.x) && (680.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::Jalapeno;
				flagMakeList = true;
			}

			// Card_CherryBomb
			if ((720.f <= MousePos.x) && (880.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::CherryBomb;
				flagMakeList = true;
			}

			//==================================================================
			// 전체 카드 목록에서 Card 선택시, 선택된 카드 목록에 Card 추가
			//==================================================================
			/*
				선택한 카드가
				선택카드목록에 존재하는지 확인 후,

				존재하지 않으면
				선택카드목록에 추가

				존재하면
				아무작업도 하지 않음
			*/
			if (flagMakeList)
			{
				bool FlagChkPickedBefore = FnChkPickedBefore((int)mPickedCardType);

				if (!FlagChkPickedBefore)
					FnMakePickedCardList();
			}
		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CCards::FnClickEvent_WholeCardList

	void CCards::FnClickEvent_PickedCardList()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			bool flagDoDelete = false;
			int deleteIdx = 0;

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			// 1st Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (180.f <= MousePos.y) && (275.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 0;
			}

			// 2nd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (290.f <= MousePos.y) && (385.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 1;
			}

			// 3rd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (400.f <= MousePos.y) && (495.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 2;
			}

			// 4th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (510.f <= MousePos.y) && (605.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 3;
			}

			// 5th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (620.f <= MousePos.y) && (715.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 4;
			}

			//==================================================================
			// 선택 해제 - 선택된 카드 목록에서 Card 선택시
			//==================================================================
			if (flagDoDelete)
			{
				mPickedCardType = ePlantsType::End;
				mPickedCardList[deleteIdx].plantsType = ePlantsType::End;
				--mCntPickedCard;
			}
		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CCards::FnClickEvent_PickedCardList

	void CCards::FnClickEvent()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			int idx = 0;
			bool flagIsCardSelected = false;
			bool flagDoRelease_CardSelected = false;

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			// 1st Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (180.f <= MousePos.y) && (275.f >= MousePos.y))
			{
				idx = 0;
				flagIsCardSelected = true;
			}

			// 2nd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (290.f <= MousePos.y) && (385.f >= MousePos.y))
			{
				idx = 1;
				flagIsCardSelected = true;
			}

			// 3rd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (400.f <= MousePos.y) && (495.f >= MousePos.y))
			{
				idx = 2;
				flagIsCardSelected = true;
			}

			// 4th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (510.f <= MousePos.y) && (605.f >= MousePos.y))
			{
				idx = 3;
				flagIsCardSelected = true;
			}

			// 5th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (620.f <= MousePos.y) && (715.f >= MousePos.y))
			{
				idx = 4;
				flagIsCardSelected = true;
			}

			if (flagIsCardSelected)
			{
				// 선택 해제 - 뽑기삽
				if (true == CCommonObjects::FnGetFlagIsShovelSelected())
					CCommonObjects::FnRelease_Shovel();

				if ((true == mFlagIsCardSelected)
					&& (mPickedCardType == mPickedCardList[idx].plantsType))
				{
					//==================================================================
					// 비활성화 - 이미지(선택한 카드 표시)
					//==================================================================
					/*
						카드가 선택된 상태에서
						기선택과 동일한 카드로 재클릭시
					*/
					flagDoRelease_CardSelected = true;
				}
				else if (false == mPickedCardList[idx].isDisabled)
				{
					//==================================================================
					// 활성화 - 이미지(선택한 카드 표시)
					//==================================================================
					/*
						비활성이 아닌 상태의 카드를 클릭시
						(카드가 선택된 상태에서 기선택과 다른 카드를 선택한 경우도 해당)
					*/
					mPickedCardType = mPickedCardList[idx].plantsType;
					mFlagIsCardSelected = true;

					// 이미지(선택한 카드 표시)를 선택한 idx에 해당하는 Position에 이동
					switch (idx)
					{
					case 0:
						CCommonObjects::mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_1, 0.003f));
						break;
					case 1:
						CCommonObjects::mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_2, 0.003f));
						break;
					case 2:
						CCommonObjects::mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_3, 0.003f));
						break;
					case 3:
						CCommonObjects::mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_4, 0.003f));
						break;
					case 4:
						CCommonObjects::mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_5, 0.003f));
						break;
					default:
						break;
					}
				}
			}

			//==================================================================
			// 비활성화 - 이미지(선택한 카드 표시)
			//==================================================================
			/* (Exception)선택 해제 - 카드가 선택된 상태에서

				||
				- 카드가 선택된 상태에서 기선택과 동일한 카드로 재클릭시

				&&
				- 카드목록 범위를 벗어났을 때
				- 게임보드(잔디밭) 진입여부 확인하여 그에 못미친 영역일 때
				- 카드가 선택된 상태일 때
			*/
			if ((true == flagDoRelease_CardSelected)
				|| ((true == mFlagIsCardSelected)
					&& !((10.f <= MousePos.x) && (185.f >= MousePos.x) && (180.f <= MousePos.y) && (715.f >= MousePos.y))
					&& (400.f >= MousePos.x)))
			{
				FnReleaseSelect();
			}
		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CCards::FnClickEvent

	void CCards::FnReleaseSelect()
	{
		CCommonObjects::mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mPickedCardType = ePlantsType::End;
		mFlagIsCardSelected = false;
	}//END-void CCards::FnReleaseSelect

	void CCards::FnStartCoolTime()
	{
		int catchidx = 0;
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			if (CCards::FnGetPickedCardType() == CCards::mPickedCardList[idx].plantsType)
			{
				catchidx = idx;
				break;
			}
		}

		CCards::mPickedCardList[catchidx].isCoolTimeActive = true;
		CCards::mPickedCardList[catchidx].coolTime = 0.f;
	}//END-void CCards::FnStartCoolTime
}