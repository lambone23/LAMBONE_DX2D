#include "CCommonObjects.h"

#include "CCards.h"
#include "CSunLights.h"
#include "CPlants.h"

extern yha::CApplication MyApplication;

namespace yha
{
	bool CCommonObjects::mFlagChkEnter			= false;
	bool CCommonObjects::mFlagPlayEnter			= false;
	bool CCommonObjects::mFlagPlay				= false;
	bool CCommonObjects::mFlagIsShovelSelected	= false;

	CGameObject* CCommonObjects::mUI_SelectedCardBG1 = nullptr;
	CGameObject* CCommonObjects::mUI_SelectedCardBG2 = nullptr;
	CGameObject* CCommonObjects::mUI_SelectedCardBG3 = nullptr;
	CGameObject* CCommonObjects::mUI_SelectedCardBG4 = nullptr;
	CGameObject* CCommonObjects::mUI_SelectedCardBG5 = nullptr;

	Vector3 CCommonObjects::positonList[MAX_PLANTS] // Chomper 별도
		= {
			Vector3(-1.7f,	1.3f, 0.010f), // 0
			Vector3(-1.1f,	1.3f, 0.010f), // 1
			Vector3(-0.4f,	1.3f, 0.010f), // 2
			Vector3(0.2f,	1.3f, 0.010f), // 3
			Vector3(0.8f,	1.3f, 0.010f), // 4
			Vector3(1.5f,	1.3f, 0.010f), // 5
			Vector3(2.1f,	1.3f, 0.010f), // 6
			Vector3(2.7f,	1.3f, 0.010f), // 7
			Vector3(3.3f,	1.3f, 0.010f), // 8

			Vector3(-1.7f,	0.6f, 0.010f), // 9
			Vector3(-1.1f,	0.6f, 0.010f), // 10
			Vector3(-0.4f,	0.6f, 0.010f), // 11
			Vector3(0.2f,	0.6f, 0.010f), // 12
			Vector3(0.8f,	0.6f, 0.010f), // 13
			Vector3(1.5f,	0.6f, 0.010f), // 14
			Vector3(2.1f,	0.6f, 0.010f), // 15
			Vector3(2.7f,	0.6f, 0.010f), // 16
			Vector3(3.3f,	0.6f, 0.010f), // 17

			Vector3(-1.7f,	-0.2f, 0.010f), // 18
			Vector3(-1.1f,	-0.2f, 0.010f), // 19
			Vector3(-0.4f,	-0.2f, 0.010f), // 20
			Vector3(0.2f,	-0.2f, 0.010f), // 21
			Vector3(0.8f,	-0.2f, 0.010f), // 22
			Vector3(1.5f,	-0.2f, 0.010f), // 23
			Vector3(2.1f,	-0.2f, 0.010f), // 24
			Vector3(2.7f,	-0.2f, 0.010f), // 25
			Vector3(3.3f,	-0.2f, 0.010f), // 26

			Vector3(-1.7f,	-1.f, 0.010f), // 27
			Vector3(-1.1f,	-1.f, 0.010f), // 28
			Vector3(-0.4f,	-1.f, 0.010f), // 29
			Vector3(0.2f,	-1.f, 0.010f), // 30
			Vector3(0.8f,	-1.f, 0.010f), // 31
			Vector3(1.5f,	-1.f, 0.010f), // 32
			Vector3(2.1f,	-1.f, 0.010f), // 33
			Vector3(2.7f,	-1.f, 0.010f), // 34
			Vector3(3.3f,	-1.f, 0.010f), // 35

			Vector3(-1.7f,	-1.7f, 0.010f), // 36
			Vector3(-1.1f,	-1.7f, 0.010f), // 37
			Vector3(-0.4f,	-1.7f, 0.010f), // 38
			Vector3(0.2f,	-1.7f, 0.010f), // 39
			Vector3(0.8f,	-1.7f, 0.010f), // 40
			Vector3(1.5f,	-1.7f, 0.010f), // 41
			Vector3(2.1f,	-1.7f, 0.010f), // 42
			Vector3(2.7f,	-1.7f, 0.010f), // 43
			Vector3(3.3f,	-1.7f, 0.010f), // 44
	};

	CGameObject* CCommonObjects::mUI_SeedChooserBG			= nullptr;
	CGameObject* CCommonObjects::mUI_btn_Play				= nullptr;
	CGameObject* CCommonObjects::mUI_btn_Play_Disabled		= nullptr;
	CGameObject* CCommonObjects::mUI_btn_ResetChoose		= nullptr;

	CGameObject* CCommonObjects::mUI_SunPointChk			= nullptr;
	CGameObject* CCommonObjects::mUI_ShovelBG				= nullptr;
	CGameObject* CCommonObjects::mUI_Shovel					= nullptr;

	CGameObject* CCommonObjects::mUI_FlagMeterEmpty			= nullptr;
	CGameObject* CCommonObjects::mUI_FlagMeterParts_Zombie	= nullptr;
	CGameObject* CCommonObjects::mUI_FlagMeterParts_Flag	= nullptr;
	CGameObject* CCommonObjects::mUI_FlagMeterParts_FlagFin	= nullptr;

	CGameObject* CCommonObjects::mUI_btn_Menu				= nullptr;

	CGameObject* CCommonObjects::mUI_SelectedCard			= nullptr;
	CGameObject* CCommonObjects::mUI_SelectedShovel			= nullptr;

	CCommonObjects::CCommonObjects()
	{
	}
	CCommonObjects::~CCommonObjects()
	{
	}

	void CCommonObjects::FnInitialize()
	{
		//==================================================================
		// Choose Plants
		//==================================================================
#pragma region Resource_UI_Choose Plants
		// UI_SeedChooserBG
		mUI_SeedChooserBG = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		CMeshRenderer* mr = mUI_SeedChooserBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SeedChooserBG"));
		mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, 28.f / 7.f, 0.f));

		// UI_btn_Play
		mUI_btn_Play = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_Play->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Play"));
		mUI_btn_Play->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (80.f * 0.8f) / 180.f, 0.f));

		// UI_btn_Play_Disabled
		mUI_btn_Play_Disabled = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_Play_Disabled->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Play_Disabled"));
		mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (80.f * 0.8f) / 180.f, 0.f));

		// UI_btn_ResetChoose
		mUI_btn_ResetChoose = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_ResetChoose->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_ResetChoose"));
		mUI_btn_ResetChoose->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.25f, (53.f * 0.25f) / 55.f, 0.f));

		// UI_SelectedCardBG
		mUI_SelectedCardBG1 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SelectedCardBG1->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCardBG"));
		mUI_SelectedCardBG1->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mUI_SelectedCardBG2 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SelectedCardBG2->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCardBG"));
		mUI_SelectedCardBG2->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mUI_SelectedCardBG3 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SelectedCardBG3->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCardBG"));
		mUI_SelectedCardBG3->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mUI_SelectedCardBG4 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SelectedCardBG4->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCardBG"));
		mUI_SelectedCardBG4->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mUI_SelectedCardBG5 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SelectedCardBG5->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCardBG"));
		mUI_SelectedCardBG5->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));
#pragma endregion

		//==================================================================
		// Play
		//==================================================================
#pragma region Resource_UI_Play
		// UI_SunPointChk
		mUI_SunPointChk = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SunPointChk->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SunPointChk"));
		mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.5f, (34.f * 1.5f) / 123.f, 0.f));

		// UI_ShovelBG
		mUI_ShovelBG = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_ShovelBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_ShovelBG"));
		mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (72.f * 0.4f) / 70.f, 0.f));

		// UI_Shovel
		mUI_Shovel = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_Shovel->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Shovel"));
		mUI_Shovel->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.35f, (125.f * 0.35f) / 116.f, 0.f));

		// UI_FlagMeterEmpty
		mUI_FlagMeterEmpty = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterEmpty->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterEmpty"));
		mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetScale(Vector3(2.5f, (21.f * 2.5f) / 157.f, 0.f));

		// UI_FlagMeterParts_Zombie
		mUI_FlagMeterParts_Zombie = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterParts_Zombie->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Zombie"));
		mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (25.f * 0.4f) / 25.f, 0.f));

		// UI_FlagMeterParts_Flag
		mUI_FlagMeterParts_Flag = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterParts_Flag->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// UI_FlagMeterParts_FlagFin
		mUI_FlagMeterParts_FlagFin = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterParts_FlagFin->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// UI_btn_Menu
		mUI_btn_Menu = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_Menu->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Menu"));
		mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.33f, (48.f * 1.33f) / 120.f, 0.f));

		// UI_SelectedCard
		mUI_SelectedCard = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI2);
		mr = mUI_SelectedCard->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCard"));
		mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.f, (177.f * 0.3f) / 108.f, 0.f));

		// UI_SelectedShovel
		mUI_SelectedShovel = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI2);
		mr = mUI_SelectedShovel->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCard"));
		mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (177.f * 0.3f) / 108.f, 0.f));
#pragma endregion
	}//END-void CCommonObjects::FnInitialize

	void CCommonObjects::FnReady(eStepMode _inMode)
	{
		if (eStepMode::Choose == _inMode)
		{
			//-------------------------------------
			// UI - 전체 카드 목록
			//-------------------------------------
			/* <form>
				[0]-SunFlower	[1]-WallNut		[2]-PeaShooter	
				[3]-Chomper		[4]-Jalapeno	[5]-CherryBomb
			*/
			// 전체 카드 목록 창 배경 셋팅
			mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, 0.2f, 0.010f));

			//-------------------------------------
			// UI - 선택한 카드 목록
			//-------------------------------------
			/* <form>
				1st Selected
				2nd Selected
				3rd Selected
				4th Selected
				5th Selected
			*/
			// 선택카드목록 창 배경 셋팅
			mUI_SelectedCardBG1->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_1, POS_Z_DEFAULT));
			mUI_SelectedCardBG2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_2, POS_Z_DEFAULT));
			mUI_SelectedCardBG3->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_3, POS_Z_DEFAULT));
			mUI_SelectedCardBG4->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_4, POS_Z_DEFAULT));
			mUI_SelectedCardBG5->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_5, POS_Z_DEFAULT));

			//-------------------------------------
			// UI - 버튼
			//-------------------------------------
			// Reset버튼 - 선택목록 초기화 버튼 배치
			mUI_btn_ResetChoose->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -1.5f, POS_Z_DEFAULT));

			// Play버튼 - 활성화 조건 확인 후 배치
			if (MAX_CARDS_PICKED == CCards::FnGetCntPickedCard())
			{
				mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, POS_Z_DEFAULT));
				mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, POS_Z_DEFAULT));
			}
			else
			{
				mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, POS_Z_DEFAULT));
				mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, POS_Z_DEFAULT));
			}
		}
		else if (eStepMode::Play == _inMode)
		{
			mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.7f, 2.f, POS_Z_DEFAULT));
			mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, POS_Z_DEFAULT));
			mUI_Shovel->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, POS_Z_FRONT_1));

			mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, POS_Z_DEFAULT));
			mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.45f, 2.05f, POS_Z_FRONT_2));
			mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, POS_Z_FRONT_1));
			mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.33f, 2.05f, POS_Z_FRONT_1));

			mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetPosition(Vector3(3.3f, 1.98f, POS_Z_DEFAULT));
		}

	}//END-void CCommonObjects::FnReady

	void CCommonObjects::FnClickEvent_BtnResetChoose()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			if ((75.f <= MousePos.x) && (123.f >= MousePos.x)
				&& (728.f <= MousePos.y) && (773.f >= MousePos.y))
			{

				// 초기화 - 선택된 카드 목록
				for (size_t idx = 0; idx < MAX_CARDS_PICKED; idx++)
				{
					CCards::mPickedCardList[idx].plantsType = ePlantsType::End;
					CCards::mPickedCardList[idx].isDisabled = false;
				}

				// 초기화 - 선택된 카드 그림
				CCards::mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				// 초기화 - 선택된 카드 총 개수
				CCards::FnSetCntPickedCard(0);
			}
		}
	}//END-void CCommonObjects::FnClickEvent_BtnResetChoose

	void CCommonObjects::FnClickEvent_BtnPlay()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			if ((520.f <= MousePos.x) && (675.f >= MousePos.x)
				&& (819.f <= MousePos.y) && (880.f >= MousePos.y)
				&& MAX_CARDS_PICKED == CCards::FnGetCntPickedCard())
			{// Play 모드 진입 조건 충족시

				mFlagPlayEnter = true;

				CCards::FnSetPickedCardType(ePlantsType::End);
				CCards::FnSetCntPickedCard(0);

				//==================================================================
				// UI 초기화
				//==================================================================
				//-------------------------------------
				// UI
				//-------------------------------------
				object::FnDestroy(mUI_SeedChooserBG);
				object::FnDestroy(mUI_btn_Play);
				object::FnDestroy(mUI_btn_Play_Disabled);
				object::FnDestroy(mUI_btn_ResetChoose);

				object::FnDestroy(mUI_SelectedCardBG1);
				object::FnDestroy(mUI_SelectedCardBG2);
				object::FnDestroy(mUI_SelectedCardBG3);
				object::FnDestroy(mUI_SelectedCardBG4);
				object::FnDestroy(mUI_SelectedCardBG5);

				//-------------------------------------
				// 카드 목록 (임시로 숨김)
				//-------------------------------------
				CCards::mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				CCards::mCard_SunFlower->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_WallNut->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_Chomper->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				CCards::mCard_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				CCards::mCard_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				CCards::mCard_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				CCards::mCard_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
			}
			else if ((MousePos.x >= 520.f) && (MousePos.x <= 675.f)
				&& (MousePos.y >= 819.f) && (MousePos.y <= 880.f)
				&& MAX_CARDS_PICKED != CCards::FnGetCntPickedCard())
			{// Play 모드 진입 조건 미충족시

				TCHAR Temp[256] = { 0, };
				MessageBox(Tmp_mHwnd, L"사용가능한 플레이어 선택이 완료되지 않았습니다!", L"Warning", MB_OK);
			}
		}
	}//END-void CCommonObjects::FnClickEvent_BtnPlay

	void CCommonObjects::FnClickEvent_Shovel()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			//==================================================================
			// 뽑기삽을 클릭한 경우
			//==================================================================
			if ((610.f <= MousePos.x) && (690.f >= MousePos.x)
				&& (10.f <= MousePos.y) && (90.f >= MousePos.y))
			{
				// 선택 해제 - 카드
				if (true == CCards::FnGetFlagIsCardSelected())
					CCards::FnReleaseSelect();

				if (!mFlagIsShovelSelected)
				{// 뽑기삽이 비활성화였던 경우 - 활성화로 변경
					mFlagIsShovelSelected = true;
					mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, 0.003f));
				}
				else
				{// 뽑기삽 활성화였던 경우 - 비활성화로 변경 (뽑기삽이 이미 선택된 상태에서 다시 뽑기삽이 클릭된 상태)
					mFlagIsShovelSelected = false;
					mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				}
			}
		}
	}//END-void CCommonObjects::FnClickEvent_Shovel

	void CCommonObjects::FnRelease_Shovel()
	{
		mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mFlagIsShovelSelected = false;
	}//END-void CCommonObjects::FnRelease_Shovel
}