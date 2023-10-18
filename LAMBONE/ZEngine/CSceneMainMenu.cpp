#include "CSceneMainMenu.h"

#include "CCommon.h"
#include <cmath>

extern yha::CApplication MyApplication;

namespace yha
{
	CSceneMainMenu::CSceneMainMenu()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
		, mLight(nullptr)
		, mLightComp(nullptr)
		, mLambone(nullptr)
		, mUI_btn_Start(nullptr)
		, mUI_btn_Start2(nullptr)
		, mFlagFinFadeIn(nullptr)
		, mFlagMouseOver(false)
		, mChkSecond(0.f)
		, mBrightValue(0.f)
	{
	}
	CSceneMainMenu::~CSceneMainMenu()
	{
	}

	void CSceneMainMenu::FnDoInitialize()
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
		// Light
		//==================================================================
		mLight = new CGameObject();
		mLight->FnSetName(L"Light_Directional");
		FnAddGameObject(eLayerType::Light, mLight);

		mLightComp = mLight->FnAddComponent<CLight>();
		mLightComp->FnSetType(eLightType::Directional);
		//mLightComp->FnSetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		mLightComp->FnSetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));

		mLight->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));

		//==================================================================
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 0.999f), eLayerType::BG);
		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_MainMenu"));
		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(CApplication::FnGetScaleFullWidth(), CApplication::FnGetScaleFullHeight(), 0.f));

		//==================================================================
		// UI
		//==================================================================
		mUI_btn_Start = object::FnInstantiate<CGameObject>(Vector3(1.6f, 0.5f, POS_Z_FRONT_2), eLayerType::UI);
		mr = mUI_btn_Start->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_StartAdventure"));
		mUI_btn_Start->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (146.f * 3.f) / 331.f, 0.f));

		mUI_btn_Start2 = object::FnInstantiate<CGameObject>(Vector3(1.6f, 0.5f, POS_Z_DEFAULT), eLayerType::UI);
		mr = mUI_btn_Start2->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_StartAdventure_MouseOver"));
		//mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, (194.f * 3.5f) / 379.f, 0.f));
		mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

		//==================================================================
		// LAMBONE
		//==================================================================
		mLambone = object::FnInstantiate<CGameObject>(Vector3(-2.5f, -1.5f, POS_Z_FRONT_2), eLayerType::UI);
		mr = mLambone->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"LAMBONE"));
		mLambone->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (379.f * 3.f) / 815.f, 0.f));
	}

	void CSceneMainMenu::FnInitialize()
	{
	}

	void CSceneMainMenu::FnUpdate()
	{
		mChkSecond += CTime::FnDeltaTime();

		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_PlayGrassDay");

		if(!mFlagFinFadeIn)
			FnFadeIn();

		if(mFlagFinFadeIn)
			FnMouseOver_btn();

		CScene::FnUpdate();
	}
	void CSceneMainMenu::FnLateUpdate()
	{
		CScene::FnLateUpdate();
	}
	void CSceneMainMenu::FnRender()
	{
		CScene::FnRender();
	}
	void CSceneMainMenu::FnOnEnter()
	{
		mFlagFinFadeIn	= false;
		mChkSecond		= 0.f;
		mBrightValue	= 0.f;

		FnDoInitialize();
	}

	void CSceneMainMenu::FnOnExit()
	{
		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
		object::FnDestroy(mLight);

		object::FnDestroy(mLambone);
		object::FnDestroy(mUI_btn_Start);
		object::FnDestroy(mUI_btn_Start2);
	}

	void CSceneMainMenu::FnFadeIn()
	{
		if (0.7f <= mBrightValue)
		{
			mChkSecond = 0.f;
			mFlagFinFadeIn = true;
		}
		else
		{
			mBrightValue += 0.5f * CTime::FnDeltaTime();
			mLightComp->FnSetColor(Vector4(mBrightValue, mBrightValue, mBrightValue, 1.0f));
		}
	}

	void CSceneMainMenu::FnMouseOver_btn()
	{
		//if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		//{
		//	HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		//	::POINT MousePos = {};
		//	::GetCursorPos(&MousePos);
		//	::ScreenToClient(Tmp_mHwnd, &MousePos);

		//	std::wstring name = CSceneManager::FnGetActiveSceneName();
		//	if (name == L"Scene_MainMenu")
		//	{
		//		//¡áTODO-DELETE-DebugPrint
		//		HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		//		TCHAR Temp[256] = { 0, };
		//		_stprintf_s(Temp, L"x: % d, y: % d", MousePos.x, MousePos.y);
		//		MessageBox(Tmp_mHwnd, Temp, L"Â§", MB_OK);
		//	}
		//}

		std::wstring name = CSceneManager::FnGetActiveSceneName();
		HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		::POINT MousePos = {};
		::GetCursorPos(&MousePos);
		::ScreenToClient(Tmp_mHwnd, &MousePos);

		if ((name == L"Scene_MainMenu")
			&& ((958.f <= MousePos.x) && (1266.f >= MousePos.x) && (250.f <= MousePos.y) && (300.f >= MousePos.y))
			|| ((840.f <= MousePos.x) && (982.f >= MousePos.x) && (281.f <= MousePos.y) && (393.f >= MousePos.y))
			|| ((982.f <= MousePos.x) && (1104.f >= MousePos.x) && (281.f <= MousePos.y) && (408.f >= MousePos.y))
			|| ((1104.f <= MousePos.x) && (1273.f >= MousePos.x) && (304.f <= MousePos.y) && (444.f >= MousePos.y))
			|| ((1273.f <= MousePos.x) && (1399.f >= MousePos.x) && (320.f <= MousePos.y) && (464.f >= MousePos.y))
			)

		{
			mFlagMouseOver = true;

			if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
				CSceneManager::FnLoadScene(L"Scene_PlayGrassDay");
		}
		else
		{
			mFlagMouseOver = false;
		}

		if (mFlagMouseOver)
		{
			mUI_btn_Start->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.6f, 0.5f, POS_Z_DEFAULT));
			mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.6f, 0.5f, POS_Z_FRONT_1));

			//mUI_btn_Start->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (146.f * 3.f) / 331.f, 0.f));
			mUI_btn_Start->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
			mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, (194.f * 3.5f) / 379.f, 0.f));
			//mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
		}
		else
		{
			mUI_btn_Start->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.6f, 0.5f, POS_Z_FRONT_1));
			mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.6f, 0.5f, POS_Z_DEFAULT));

			mUI_btn_Start->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (146.f * 3.f) / 331.f, 0.f));
			//mUI_btn_Start->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
			//mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, (194.f * 3.5f) / 379.f, 0.f));
			mUI_btn_Start2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
		}
	}//END-void CSceneMainMenu::FnMouseOver_btn
}