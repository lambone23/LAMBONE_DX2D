#include "CSceneMainMenu.h"

#include "CGameObject.h"
#include "CInput.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CApplication.h"
#include "CObject.h"
#include "CRenderer.h"
#include "CCameraScript.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CSceneMainMenu::CSceneMainMenu()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
		, mUI_btn_StartAdventure(nullptr)
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
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 0.999f), eLayerType::BG);

		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_MainMenu"));

		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));

		//==================================================================
		// UI
		//==================================================================
		mUI_btn_StartAdventure = object::FnInstantiate<CGameObject>(Vector3(1.6f, 0.5f, 0.f), eLayerType::UI);

		mr = mUI_btn_StartAdventure->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_StartAdventure"));

		mUI_btn_StartAdventure->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (146.f * 3.f) / 331.f, 0.f));
	}

	void CSceneMainMenu::FnInitialize()
	{
	}

	void CSceneMainMenu::FnUpdate()
	{
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_PlayGrassDay");

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
		FnDoInitialize();
	}

	void CSceneMainMenu::FnOnExit()
	{
		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
		object::FnDestroy(mUI_btn_StartAdventure);
	}
}