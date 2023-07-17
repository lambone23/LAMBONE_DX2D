#include "CSceneEnding.h"

#include "CGameObject.h"
#include "CInput.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CApplication.h"
#include "CObject.h"
#include "CCameraScript.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CSceneEnding::CSceneEnding()
		: mCamera(nullptr)
		, mBG(nullptr)
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

		//==================================================================
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 0.0f), eLayerType::BG);

		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Ending"));

		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));
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
	}
}