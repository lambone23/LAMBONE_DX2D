#include "CSceneLoading.h"

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
	CSceneLoading::CSceneLoading()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
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
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 0.0f), eLayerType::BG);

		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Loading"));

		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));
	}

	void CSceneLoading::FnInitialize()
	{
	}

	void CSceneLoading::FnUpdate()
	{
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_MainMenu");

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
		FnDoInitialize();
	}

	void CSceneLoading::FnOnExit()
	{
		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
	}
}