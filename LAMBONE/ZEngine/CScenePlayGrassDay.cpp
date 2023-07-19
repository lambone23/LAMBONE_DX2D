#include "CScenePlayGrassDay.h"

#include "CGameObject.h"
#include "CInput.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CApplication.h"
#include "CGridScript.h"
#include "CObject.h"
#include "CRenderer.h"
#include "CCameraScript.h"
#include "CTime.h"
#include "CComponent.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CScenePlayGrassDay::CScenePlayGrassDay()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
	{
	}
	CScenePlayGrassDay::~CScenePlayGrassDay()
	{
	}

	void CScenePlayGrassDay::FnDoInitialize()
	{
		//==================================================================
		// Camera
		//==================================================================
		CCamera* cameraComp = nullptr;

		//-------------------------------------
		// Main Camera
		//-------------------------------------
		mCamera_Main = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
		cameraComp = mCamera_Main->FnAddComponent<CCamera>();
		cameraComp->FnTurnLayerMask(eLayerType::UI, false);
		mCamera_Main->FnAddComponent<CCameraScript>();

		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

		//-------------------------------------
		// UI Camera
		//-------------------------------------
		mCamera_UI = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
		cameraComp = mCamera_UI->FnAddComponent<CCamera>();
		cameraComp->FnTurnLayerMask(eLayerType::BG, false);
		//mCamera_UI->FnAddComponent<CCameraScript>();

		//==================================================================
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(1.5f, 0.0f, 0.999f), eLayerType::BG);

		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_GrassDay"));

		//mBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.5f, 0.0f, 1.0f));
		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(11.f, 33.f / 7.f, 0.f));

		//==================================================================
		// Grid (After Camera Set)
		//==================================================================
		{
			CGameObject* grid = new CGameObject();
			grid->FnSetName(L"Grid");
			FnAddGameObject(eLayerType::Grid, grid);

			CMeshRenderer* mr = grid->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GridMaterial"));
			CGridScript* gridSc = grid->FnAddComponent<CGridScript>();
			gridSc->FnSetCamera(cameraComp);
		}

		//==================================================================
		// UI
		//==================================================================
		// UI_SeedChooserBG
		mUI_SeedChooserBG = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_SeedChooserBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SeedChooserBG"));
		mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, 28.f / 7.f, 0.f));

		// UI_btn_Play
		mUI_btn_Play = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_btn_Play->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Play"));
		mUI_btn_Play->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (80.f * 0.8f) / 180.f, 0.f));

		// mUI_SunPointChk
		mUI_SunPointChk = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_SunPointChk->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SunPointChk"));
		mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.5f, (34.f * 1.5f) / 123.f, 0.f));

		// UI_ShovelBG
		mUI_ShovelBG = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_ShovelBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_ShovelBG"));
		mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (72.f * 0.4f) / 70.f, 0.f));

		// UI_Shovel
		mUI_Shovel = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_Shovel->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Shovel"));
		mUI_Shovel->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.35f, (125.f * 0.35f) / 116.f, 0.f));

		// UI_btn_Menu
		mUI_btn_Menu = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_btn_Menu->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Menu"));
		mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.33f, (48.f * 1.33f) / 120.f, 0.f));

		// UI_FlagMeterEmpty
		mUI_FlagMeterEmpty = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_FlagMeterEmpty->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterEmpty"));
		mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetScale(Vector3(2.5f, (21.f * 2.5f) / 157.f, 0.f));

		// UI_FlagMeterParts_Zombie
		mUI_FlagMeterParts_Zombie = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_FlagMeterParts_Zombie->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Zombie"));
		mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (25.f * 0.4f) / 25.f, 0.f));

		// UI_FlagMeterParts_Flag
		mUI_FlagMeterParts_Flag = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_FlagMeterParts_Flag->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// UI_FlagMeterParts_FlagFin
		mUI_FlagMeterParts_FlagFin = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mUI_FlagMeterParts_FlagFin->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// Card_SunFlower
		mCard_SunFlower = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower2 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower2->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower2->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower3 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower3->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower3->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower4 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower4->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower4->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower5 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower5->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower5->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower6 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower6->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower6->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower7 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower7->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower7->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower8 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 1.01f), eLayerType::UI);
		mr = mCard_SunFlower8->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower8->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		//mCard_Peashooter = new CGameObject();
		//FnAddGameObject(eLayerType::UI, mCard_Peashooter);

		//mCard_WallNut = new CGameObject();
		//FnAddGameObject(eLayerType::UI, mCard_WallNut);

		//mCard_CherryBomb = new CGameObject();
		//FnAddGameObject(eLayerType::UI, mCard_CherryBomb);
	}

	void CScenePlayGrassDay::FnInitialize()
	{
	}

	void CScenePlayGrassDay::FnUpdate()
	{
		//==================================================================
		// Main Camera Move
		//==================================================================
		CTransform* tr = mCamera_Main->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		// 화면 이동 ( -->> )
		while (MyApplication.mFlagChkFirst)
		{
			mChkSecond += CTime::FnDeltaTime();

			if (mChkSecond > 1.0f)
			{
				pos.x += 2.0f * CTime::FnDeltaTime();
				tr->FnSetPosition(pos);
				break;
			}
		}

		// 화면 고정
		if (pos.x > 3.f)
			MyApplication.mFlagChkFirst = false;

		//==================================================================
		// Choose Plants
		//==================================================================
		if (!MyApplication.mFlagChkFirst)
		{
			if (mFlagShowSeedChooser)
			{
				// UI_SeedChooserBG
				mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, 0.2f, 0.0f));

				// UI_btn_Play
				mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, 0.0f));
			}

			// UI_btn_Play 클릭하면
			if (CInput::FnGetKey(eKeyCode::LBUTTON))
			{
				HWND Tmp_mHwnd = MyApplication.FnGetHwnd();

				//VectorXY MousePos = CInput::FnGetMousePos();
				::POINT MousePos = {};
				::GetCursorPos(&MousePos);
				::ScreenToClient(Tmp_mHwnd, &MousePos);

				if ((MousePos.x >= 520.f) && (MousePos.x <= 675.f)
					&& (MousePos.y >= 819.f) && (MousePos.y <= 880.f))
				{
					mFlagClickEvent_BtnPlay = true;
					mFlagShowSeedChooser = false;

					mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, 1.01f));
					mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.f, 0.f, 0.f));
					mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, 1.01f));
					mUI_btn_Play->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.f, 0.f, 0.f));
				}
			}

			// 화면 이동 ( <<-- )
			while (!MyApplication.mFlagChkFirst && mFlagClickEvent_BtnPlay)
			{
				mChkSecond += CTime::FnDeltaTime();

				if (mChkSecond > 1.0f)
				{
					pos.x -= 2.0f * CTime::FnDeltaTime();
					tr->FnSetPosition(pos);
					break;
				}
			}

			// 화면 고정
			if (pos.x < 0.f)
			{
				mFlagClickEvent_BtnPlay = false;
				mFlagPlay = true;
			}
		}

		//==================================================================
		// Play
		//==================================================================
		if (mFlagPlay && mFlagChkEnterScene)
		{
#pragma region Resource_UI
			//==================================================================
			// UI
			//==================================================================
			// mUI_SunPointChk
			mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.7f, 2.f, 0.1f));

			// UI_ShovelBG
			mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, 0.1f));

			// UI_Shovel
			mUI_Shovel->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, 0.05f));

			// UI_btn_Menu
			mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetPosition(Vector3(3.3f, 1.98f, 0.0f));

			// UI_FlagMeterEmpty
			mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, 0.1f));

			// UI_FlagMeterParts_Zombie
			mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.45f, 2.05f, 0.04f));

			// UI_FlagMeterParts_Flag
			mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, 0.05f));

			// UI_FlagMeterParts_FlagFin
			mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.33f, 2.05f, 0.05f));
#pragma endregion
#pragma region Resource_Cards
			//==================================================================
			// Cards
			//==================================================================
			// Card_SunFlower
			mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 2.f, 0.f));
			mCard_SunFlower2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 1.5f, 0.f));
			mCard_SunFlower3->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 1.f, 0.f));
			mCard_SunFlower4->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 0.5f, 0.f));
			mCard_SunFlower5->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 0.f, 0.f));
			mCard_SunFlower6->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -0.5f, 0.f));
			mCard_SunFlower7->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -1.f, 0.f));
			mCard_SunFlower8->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -1.5f, 0.f));
#pragma endregion
		}

		//==================================================================
		// Load NextScene
		//==================================================================
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_PlayGrassNight");

		CScene::FnUpdate();
	}
	void CScenePlayGrassDay::FnLateUpdate()
	{
		CScene::FnLateUpdate();
	}
	void CScenePlayGrassDay::FnRender()
	{
		CScene::FnRender();
	}
	void CScenePlayGrassDay::FnOnEnter()
	{
		MyApplication.mFlagChkFirst = true;
		mFlagChkEnterScene = true;

		FnDoInitialize();
	}

	void CScenePlayGrassDay::FnOnExit()
	{
		MyApplication.mFlagChkFirst = true;
		mChkSecond = 0.0f;

		mFlagChkEnterScene = false;
		mFlagPlay = false;
		mFlagClickEvent_BtnPlay = false;
		mFlagShowSeedChooser = true;

		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);

		object::FnDestroy(mUI_SeedChooserBG);
		object::FnDestroy(mUI_btn_Play);

		object::FnDestroy(mUI_SunPointChk);
		object::FnDestroy(mUI_ShovelBG);
		object::FnDestroy(mUI_Shovel);

		object::FnDestroy(mUI_FlagMeterEmpty);
		object::FnDestroy(mUI_FlagMeterParts_Zombie);
		object::FnDestroy(mUI_FlagMeterParts_Flag);
		object::FnDestroy(mUI_FlagMeterParts_FlagFin);

		object::FnDestroy(mUI_btn_Menu);

		object::FnDestroy(mCard_SunFlower);
		object::FnDestroy(mCard_SunFlower2);
		object::FnDestroy(mCard_SunFlower3);
		object::FnDestroy(mCard_SunFlower4);
		object::FnDestroy(mCard_SunFlower5);
		object::FnDestroy(mCard_SunFlower6);
		object::FnDestroy(mCard_SunFlower7);
		object::FnDestroy(mCard_SunFlower8);
	}
}
