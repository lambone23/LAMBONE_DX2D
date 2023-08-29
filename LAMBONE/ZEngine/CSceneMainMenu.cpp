#include "CSceneMainMenu.h"

#include "CCommon.h"

namespace yha
{
	CSceneMainMenu::CSceneMainMenu()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
		, mlight(nullptr)
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
		// Light
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
		object::FnDestroy(mlight);

		object::FnDestroy(mUI_btn_StartAdventure);
	}
}