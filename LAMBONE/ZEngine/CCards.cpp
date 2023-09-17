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
		// mPickedList ��� ä���
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
					Ȯ���Ϸ��� ī�� �ѹ���(_idx)��
					���õ� ī�� ���(mPickedCardList)�� ���Ͽ�
					�ѹ���(_idx)�� ��Ͽ� �����ϴ� ���

					��, �ش�ī�尡 �̹� ���õ� ���
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
				���õ� ī�� ��� ���� ���Ͽ�,
				���� idx�� �ش��ϴ� ī�尡 ���õ� ī������ Ȯ��
			*/
			bool FlagChkPickedBefore = FnChkPickedBefore(idx);

			//==================================================================
			// ���õ� ī���� ��� - Disalbed�� ǥ��
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
			// ���õ��� ���� ī���� ��� - Disalbed�� �ƴ� ī��� ǥ��
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
		// �ʱ�ȭ - ���� Card���
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
		// mPickedList�� ����, Player�� ����� Card��� �׸���
		//==================================================================
		/*
			- ī�� ���� ����� ���
			�޺�����Ʈ�� ��Ÿ�ӿ� �������
			������ Ȱ��ȭ���·�
			��� �׸���

			- �÷��� ����� ���
			�޺� ����Ʈ�� ��Ÿ���� �ݿ��Ͽ�
			Ȱ��ȭ���� �Ǵ� ��Ȱ��ȭ ���·�
			��� �׸���
		*/
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			//-------------------------------------
			/// ���� ������ �׸��� �н�
			//-------------------------------------
			if (ePlantsType::End == mPickedCardList[idx].plantsType)
				continue;

			//-------------------------------------
			/// �׸���
			//-------------------------------------
			// ���� - ���ؽð�(ī�� ��Ÿ��) counting
			mPickedCardList[idx].coolTime += CTime::FnDeltaTime();

			// ī�� disabled ó�� ����
			bool flagMakeNotDisabled = false;

			int nowSunLightScore = CSunLights::FnGetSunLightScore();
			bool flagIsCoolTimeActive = mPickedCardList[idx].isCoolTimeActive;
			bool flagCoolTimeEnd = 10.f <= mPickedCardList[idx].coolTime ? true : false;
			
			// ���õ� ī�� Ÿ������ card_Picked_Tmp ����
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

			// ���õ� ī���� �׸���
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

			// ���� - ī�� Ȱ��ȭ ����, ���ؽð�(ī�� ��Ÿ��)End
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
			// ��ȿ���� ���ý�
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
			// ��ü ī�� ��Ͽ��� Card ���ý�, ���õ� ī�� ��Ͽ� Card �߰�
			//==================================================================
			/*
				������ ī�尡
				����ī���Ͽ� �����ϴ��� Ȯ�� ��,

				�������� ������
				����ī���Ͽ� �߰�

				�����ϸ�
				�ƹ��۾��� ���� ����
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
			// ��ȿ���� ���ý�
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
			// ���� ���� - ���õ� ī�� ��Ͽ��� Card ���ý�
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
			// ��ȿ���� ���ý�
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
				// ���� ���� - �̱��
				if (true == CCommonObjects::FnGetFlagIsShovelSelected())
					CCommonObjects::FnRelease_Shovel();

				if ((true == mFlagIsCardSelected)
					&& (mPickedCardType == mPickedCardList[idx].plantsType))
				{
					//==================================================================
					// ��Ȱ��ȭ - �̹���(������ ī�� ǥ��)
					//==================================================================
					/*
						ī�尡 ���õ� ���¿���
						�⼱�ð� ������ ī��� ��Ŭ����
					*/
					flagDoRelease_CardSelected = true;
				}
				else if (false == mPickedCardList[idx].isDisabled)
				{
					//==================================================================
					// Ȱ��ȭ - �̹���(������ ī�� ǥ��)
					//==================================================================
					/*
						��Ȱ���� �ƴ� ������ ī�带 Ŭ����
						(ī�尡 ���õ� ���¿��� �⼱�ð� �ٸ� ī�带 ������ ��쵵 �ش�)
					*/
					mPickedCardType = mPickedCardList[idx].plantsType;
					mFlagIsCardSelected = true;

					// �̹���(������ ī�� ǥ��)�� ������ idx�� �ش��ϴ� Position�� �̵�
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
			// ��Ȱ��ȭ - �̹���(������ ī�� ǥ��)
			//==================================================================
			/* (Exception)���� ���� - ī�尡 ���õ� ���¿���

				||
				- ī�尡 ���õ� ���¿��� �⼱�ð� ������ ī��� ��Ŭ����

				&&
				- ī���� ������ ����� ��
				- ���Ӻ���(�ܵ��) ���Կ��� Ȯ���Ͽ� �׿� ����ģ ������ ��
				- ī�尡 ���õ� ������ ��
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