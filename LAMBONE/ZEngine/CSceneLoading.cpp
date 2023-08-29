#include "CSceneLoading.h"

#include "CCommon.h"

namespace yha
{
	CSceneLoading::CSceneLoading()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
		, mlight(nullptr)
		, mChkSecond(0.f)
	{
	}
	CSceneLoading::~CSceneLoading()
	{
	}

	void CSceneLoading::FnDoInitialize()
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
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Loading"));
		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(CApplication::FnGetScaleFullWidth(), CApplication::FnGetScaleFullHeight(), 0.f));

		//==================================================================
		// Loading Progress Bar
		//==================================================================
		mUI_Loading_Floor = object::FnInstantiate<CGameObject>(Vector3(0.0f, -1.5f, 0.010f), eLayerType::UI);
		mr = mUI_Loading_Floor->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Loading_Floor"));
		mUI_Loading_Floor->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (53.f * 3.f) / 320.f, 0.f));

		mUI_Loading_Grass = object::FnInstantiate<CGameObject>(Vector3(0.0f, -1.3f, 0.009f), eLayerType::UI);
		mr = mUI_Loading_Grass->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Loading_Grass"));
		mUI_Loading_Grass->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (27.f * 3.f) / 310.f, 0.f));

		mUI_Loading_Tag = object::FnInstantiate<CGameObject>(Vector3(0.0f, -0.9f, 0.008f), eLayerType::UI);
		mr = mUI_Loading_Tag->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Loading_Tag"));
		mUI_Loading_Tag->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.f, (73.f * 1.f) / 73.f, 0.f));
	}

	void CSceneLoading::FnInitialize()
	{
	}

	void CSceneLoading::FnUpdate()
	{
		//==================================================================
		// Way1 - Load NextScene
		//==================================================================
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_MainMenu");

		//==================================================================
		// Way2 - Load NextScene
		//==================================================================
		//mChkSecond += CTime::FnDeltaTime();

		//if (mChkSecond > 2.0f)
		//{
		//	//object::FnDestroy(mBG);
		//	CSceneManager::FnLoadScene(L"Scene_MainMenu");
		//}

		CScene::FnUpdate();
	}
	void CSceneLoading::FnLateUpdate()
	{
		CScene::FnLateUpdate();
	}
	void CSceneLoading::FnRender()
	{
		CScene::FnRender();
	}

	void CSceneLoading::FnOnEnter()
	{
		mChkSecond = 0.f;
		FnDoInitialize();
	}

	void CSceneLoading::FnOnExit()
	{
		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
		object::FnDestroy(mlight);
	}
}