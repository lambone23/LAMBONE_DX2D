#include "CScenePlayGrassDay.h"

#include "CCommon.h"

#include "CCommonObjects.h"
#include "CCards.h"
#include "CSunLights.h"
#include "CPlants.h"
#include "CZombies.h"
#include "CBoard.h"

#include "CJalapeno.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CScenePlayGrassDay::CScenePlayGrassDay()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
		, mlight(nullptr)
		, mChkSecond_MoveCamera(0)
	{		
	}

	CScenePlayGrassDay::~CScenePlayGrassDay()
	{
	}

	void CScenePlayGrassDay::FnDoInitialize()
	{
		CCollisionManager::FnSetLayer(eLayerType::Player, eLayerType::Monster, true);

		std::shared_ptr<CPaintShader> paintShader	= CResources::FnFind<CPaintShader>(L"PaintShader");
		std::shared_ptr<CTexture> paintTexture		= CResources::FnFind<CTexture>(L"PaintTexuture");
		paintShader->FnSetTarget(paintTexture);
		paintShader->FnOnExcute();

		//==================================================================
		// Camera
		//==================================================================
		CCamera* cameraComp = nullptr;

		//-------------------------------------
		// Main Camera
		//-------------------------------------
		mCamera_Main = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
		cameraComp = mCamera_Main->FnAddComponent<CCamera>();
		cameraComp->FnTurnLayerMask(eLayerType::UI, false);
		cameraComp->FnTurnLayerMask(eLayerType::UI2, false);
		mCamera_Main->FnAddComponent<CCameraScript>();
		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

		//-------------------------------------
		// UI Camera
		//-------------------------------------
		mCamera_UI = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
		cameraComp = mCamera_UI->FnAddComponent<CCamera>();
		cameraComp->FnTurnLayerMask(eLayerType::BG, false);
		cameraComp->FnTurnLayerMask(eLayerType::Player, false);
		cameraComp->FnTurnLayerMask(eLayerType::Monster, false);
		cameraComp->FnTurnLayerMask(eLayerType::SunLight, false);
		cameraComp->FnTurnLayerMask(eLayerType::SunLightNatural, false);
		//mCamera_UI->FnAddComponent<CCameraScript>();

		//==================================================================
		// Light [Directional]
		//==================================================================
		mlight = new CGameObject();
		mlight->FnSetName(L"Light_Directional");
		FnAddGameObject(eLayerType::Light, mlight);
		CLight* lightComp = mlight->FnAddComponent<CLight>();
		lightComp->FnSetType(eLightType::Directional);
		lightComp->FnSetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		//lightComp->FnSetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		mlight->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//CCollider2D* cd = light->FnAddComponent<CCollider2D>();

		//{// Light [Point]
		//	CGameObject* light = new CGameObject();
		//	light->FnSetName(L"Light_Point");
		//	FnAddGameObject(eLayerType::Light, light);
		//	CLight* lightComp = light->FnAddComponent<CLight>();
		//	lightComp->FnSetType(eLightType::Point);
		//	lightComp->FnSetColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		//	lightComp->FnSetRadius(3.0f);

		//	light->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.0f, -1.0f, 0.0f));
		//	CCollider2D* cd = light->FnAddComponent<CCollider2D>();
		//}

		//==================================================================
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(1.5f, 0.0f, 0.999f), eLayerType::BG);
		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_GrassDay"));
		//mBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.5f, 0.0f, 0.999f));
		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(11.f, 33.f / 7.f, 0.f));

		//==================================================================
		// Grid (After Camera Set)
		//==================================================================
		//{
		//	CGameObject* grid = new CGameObject();
		//	grid->FnSetName(L"Grid");
		//	FnAddGameObject(eLayerType::Grid, grid);

		//	CMeshRenderer* mr = grid->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GridMaterial"));
		//	CGridScript* gridSc = grid->FnAddComponent<CGridScript>();
		//	gridSc->FnSetCamera(cameraComp);
		//}

		//==================================================================
		// Initialize - All GameObject
		//==================================================================
		//CSunLightScore* sunLightScore = object::FnInstantiate<CSunLightScore>(eLayerType::UI);
		//sunLightScore->FnInitialize();

		CCommonObjects::FnInitialize();
		CCards::FnInitialize();

		CZombies::FnInitialize();
	}//END-void CScenePlayGrassDay::FnDoInitialize
	
	void CScenePlayGrassDay::FnInitialize()
	{
	}//END-void CScenePlayGrassDay::FnInitialize

	void CScenePlayGrassDay::FnUpdate()
	{
		//==================================================================
		// Load NextScene
		//==================================================================
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_PlayGrassNight");

		//==================================================================
		// Cheat Key
		//==================================================================
		if (CInput::FnGetKeyDown(eKeyCode::P))
			CSunLights::FnSetSunLightScore_isAdd(true, 25);

		if (CInput::FnGetKeyDown(eKeyCode::O))
			for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
				CCards::mPickedCardList[idx].isCoolTimeActive = false;

		//==================================================================
		// 0. Main Camera Move to RIGHT
		//==================================================================
		if (true == CCommonObjects::FnGetFlagChkEnter()
			&& true == FnMoveCamera(eDirection::Right))
		{
			CCommonObjects::FnSetFlagChkEnter(false);
		}

		//==================================================================
		// 1. Choose Plants
		//==================================================================
		if (false == CCommonObjects::FnGetFlagChkEnter()
			&& false == CCommonObjects::FnGetFlagPlayEnter())
		{
			FnChoosePlants();
		}

		//==================================================================
		// 2. Main Camera Move to LEFT
		// 3. Play
		//==================================================================
		if (true == CCommonObjects::FnGetFlagPlayEnter()
			&& true == FnMoveCamera(eDirection::Left))
		{
			FnPlay();
		}
		
		CScene::FnUpdate();
	}//END-void CScenePlayGrassDay::FnUpdate

	void CScenePlayGrassDay::FnLateUpdate()
	{
		Vector3 pos(600, 450, 0.0f);
		Vector3 pos2(600, 450, 1000.0f);
		Viewport viewport;
		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, CCamera::FnGetGpuProjectionMatrix(), CCamera::FnGetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, CCamera::FnGetGpuProjectionMatrix(), CCamera::FnGetGpuViewMatrix(), Matrix::Identity);

		CScene::FnLateUpdate();
	}//END-void CScenePlayGrassDay::FnLateUpdate

	void CScenePlayGrassDay::FnRender()
	{
		CScene::FnRender();
	}//END-void CScenePlayGrassDay::FnRender

	void CScenePlayGrassDay::FnRender_Font()
	{
		//==================================================================
		// 햇빛 포인트 점수
		//==================================================================
		if(true == CCommonObjects::FnGetFlagPlay())
		{
			TCHAR Temp[10] = { 0, };
			_stprintf_s(Temp, L"%5d ", CSunLights::FnGetSunLightScore());
			CFontWrapper::FnDrawFont(Temp, POS_XY_SUNLIGHTSCORE, FONT_SIZE_SUNLIGHTSCORE, FONT_RGBA(33, 33, 33, 255));
		}

		//==================================================================
		// 카드 쿨타임
		//==================================================================
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			if (true == CCards::mPickedCardList[idx].isCoolTimeActive)
			{
				TCHAR Temp[5] = { 0, };
				_stprintf_s(Temp, L"%02i ", 10 - (int)CCards::mPickedCardList[idx].coolTime);

				switch (idx)
				{
				case 0:
					CFontWrapper::FnDrawFont(Temp, POS_XY_COOLTIME_1, FONT_SIZE_COOLTIME, FONT_RGBA(95, 0, 255, 255));
					break;
				case 1:
					CFontWrapper::FnDrawFont(Temp, POS_XY_COOLTIME_2, FONT_SIZE_COOLTIME, FONT_RGBA(95, 0, 255, 255));
					break;
				case 2:
					CFontWrapper::FnDrawFont(Temp, POS_XY_COOLTIME_3, FONT_SIZE_COOLTIME, FONT_RGBA(95, 0, 255, 255));
					break;
				case 3:
					CFontWrapper::FnDrawFont(Temp, POS_XY_COOLTIME_4, FONT_SIZE_COOLTIME, FONT_RGBA(95, 0, 255, 255));
					break;
				case 4:
					CFontWrapper::FnDrawFont(Temp, POS_XY_COOLTIME_5, FONT_SIZE_COOLTIME, FONT_RGBA(95, 0, 255, 255));
					break;
				}
			}
		}
	}//END-void CScenePlayGrassDay::FnRender_Font

	void CScenePlayGrassDay::FnOnEnter()
	{
		CSunLights::FnSetSunLightScore_isAdd(true, 0);
		CSunLights::FnSetChkSecond(0);

		mChkSecond_MoveCamera = 0.f;

		CCommonObjects::FnSetFlagChkEnter(true);
		CCommonObjects::FnSetFlagPlayEnter(false);
		CCommonObjects::FnSetFlagPlay(false);
		CCommonObjects::FnSetFlagIsShovelSelected(false);

		CCards::FnSetCntPickedCard(0);
		CCards::FnSetFlagIsCardSelected(false);

		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			CCards::mPickedCardList[idx].plantsType			= ePlantsType::End;
			CCards::mPickedCardList[idx].isDisabled			= false;
			CCards::mPickedCardList[idx].isCoolTimeActive	= false;
			CCards::mPickedCardList[idx].coolTime			= 0.f;
		}

		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			CPlants::mPlants[idx].isPlanted				= false;
			CPlants::mPlants[idx].plantsType			= ePlantsType::End;

			CSunLights::mSunLights[idx].isShow			= false;
			CSunLights::mSunLights[idx].isRemove		= false;
			CSunLights::mSunLights[idx].cycleChkTime	= 0.f;
			CSunLights::mSunLights[idx].position		= POSITION_CLEAR;
			CSunLights::mSunLights[idx].isArrived		= false;
			CSunLights::mSunLights[idx].destination		= POSITION_CLEAR;

			if (idx < 25)
			{
				CSunLights::mSunLights_Natural[idx].isShow			= false;
				CSunLights::mSunLights_Natural[idx].isRemove		= false;
				CSunLights::mSunLights_Natural[idx].cycleChkTime	= 0.f;
				CSunLights::mSunLights_Natural[idx].position		= POSITION_CLEAR;
				CSunLights::mSunLights_Natural[idx].isArrived		= false;
				CSunLights::mSunLights_Natural[idx].destination		= POSITION_CLEAR;
			}
		}

		FnDoInitialize();
	}//END-void CScenePlayGrassDay::FnOnEnter

	void CScenePlayGrassDay::FnOnExit()
	{
		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
		object::FnDestroy(mlight);

	}//END-void CScenePlayGrassDay::FnOnExit

	bool CScenePlayGrassDay::FnMoveCamera(eDirection _dir)
	{
		bool returnValue = false;

		CTransform* tr = mCamera_Main->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		if (_dir == eDirection::Right)
		{// 화면 이동 ( -->> )
			while (pos.x <= 3.f)
			{
				mChkSecond_MoveCamera += CTime::FnDeltaTime();
				if (mChkSecond_MoveCamera > 1.0f)
				{
					pos.x += 2.0f * CTime::FnDeltaTime();
					tr->FnSetPosition(pos);
					break;
				}
			}

			if (pos.x > 3.f)
				returnValue = true;
		}
		else if (_dir == eDirection::Left)
		{// 화면 이동 ( <<-- )
			while (pos.x >= 0.f)
			{
				mChkSecond_MoveCamera += CTime::FnDeltaTime();
				if (mChkSecond_MoveCamera > 1.0f)
				{
					pos.x -= 2.0f * CTime::FnDeltaTime();
					tr->FnSetPosition(pos);
					break;
				}
			}

			if (pos.x < 0.f)
				returnValue = true;
		}

		return returnValue;
	}//END-bool CScenePlayGrassDay::FnMoveCamera

	void CScenePlayGrassDay::FnChoosePlants()
	{
		//==================================================================
		// 셋팅
		//==================================================================
		// UI
		CCommonObjects::FnReady(eStepMode::Choose);

		// 전체 카드 목록 배치
		CCards::FnDrawWholeCardList();

		// Player로 사용할 목록 그리기
		CCards::FnDrawPickedCardList(eStepMode::Choose);

		//==================================================================
		// 선택시 (*****순서 중요*****)
		//==================================================================
		//-------------------------------------
		// Card 선택시
		//-------------------------------------
		// 전체 카드 목록에서
		CCards::FnClickEvent_WholeCardList();

		// 선택한 카드 목록에서
		CCards::FnClickEvent_PickedCardList();

		//-------------------------------------
		// 버튼 클릭시
		//-------------------------------------
		// Reset버튼
		CCommonObjects::FnClickEvent_BtnResetChoose();

		// 버튼 클릭시 - Play버튼
		CCommonObjects::FnClickEvent_BtnPlay();
	}//END-void CScenePlayGrassDay::FnChoosePlants

	void CScenePlayGrassDay::FnPlay()
	{
		CCommonObjects::FnSetFlagPlay(true);

		//==================================================================
		// 셋팅
		//==================================================================
		// UI
		CCommonObjects::FnReady(eStepMode::Play);

		// Cards
		CCards::FnDrawPickedCardList(eStepMode::Play);

		//==================================================================
		// 선택시
		//==================================================================
		// Cards
		CCards::FnClickEvent();

		// 뽑기삽
		CCommonObjects::FnClickEvent_Shovel();

		// 게임보드(잔디밭)
		CBoard::FnClickEvent();

		//==================================================================
		// 햇빛
		//==================================================================
		// made by Sunflower
		CSunLights::FnManager_Sunflower();

		// made by Natural
		float secTmp = CSunLights::FnGetChkSecond();
		CSunLights::FnSetChkSecond(secTmp += CTime::FnDeltaTime());
		CSunLights::FnManager_Natural();

		//==================================================================
		// 그리기
		//==================================================================
		// 햇빛
		CSunLights::FnDraw();

		//CCommonObjects::mChkSecond += CTime::FnDeltaTime();
		//CJalapeno::mChkSecond += CTime::FnDeltaTime();

		// 식물
		CBoard::FnDraw();


		CZombies::FnManageFSM();
		CZombies::FnManageCollider();

	}//END-void CScenePlayGrassDay::FnPlay
}
