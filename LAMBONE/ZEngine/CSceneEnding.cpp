#include "CSceneEnding.h"

#include "CCommon.h"

namespace yha
{
	CSceneEnding::CSceneEnding()
		: mCamera(nullptr)
		, mBG(nullptr)
		, mlight(nullptr)
	{
	}
	CSceneEnding::~CSceneEnding()
	{
	}

	void CSceneEnding::FnDoInitialize()
	{
		//==================================================================
		// Camera
		//==================================================================
		mCamera = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Player);
		CCamera* cameraComp = mCamera->FnAddComponent<CCamera>();
		mCamera->FnAddComponent<CCameraScript>();

		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

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
		// 
		//==================================================================
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 0.0f), eLayerType::BG);

		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Ending_Win"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Ending_Lose"));

		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(CApplication::FnGetScaleFullWidth(), CApplication::FnGetScaleFullHeight(), 0.f));
	}

	void CSceneEnding::FnInitialize()
	{
	}

	void CSceneEnding::FnUpdate()
	{
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_Intro");

		CScene::FnUpdate();
	}
	void CSceneEnding::FnLateUpdate()
	{
		CScene::FnLateUpdate();
	}
	void CSceneEnding::FnRender()
	{
		CScene::FnRender();
	}

	void CSceneEnding::FnOnEnter()
	{
		FnDoInitialize();
	}

	void CSceneEnding::FnOnExit()
	{
		object::FnDestroy(mCamera);
		object::FnDestroy(mBG);
		object::FnDestroy(mlight);
	}
}