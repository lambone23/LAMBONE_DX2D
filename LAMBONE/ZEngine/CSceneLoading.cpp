#include "CSceneLoading.h"

#include "CGameObject.h"
#include "CInput.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CApplication.h"

#include "CCameraScript.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CSceneLoading::CSceneLoading()
	{
	}
	CSceneLoading::~CSceneLoading()
	{
	}
	void CSceneLoading::FnInitialize()
	{
		//==================================================================
		// Main Camera
		//==================================================================
		CGameObject* camera = new CGameObject();
		FnAddGameObject(eLayerType::Player, camera);
		camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
		CCamera* cameraComp = camera->FnAddComponent<CCamera>();
		//camera->FnAddComponent<CCameraScript>();

		//==================================================================
		// BG
		//==================================================================
		CGameObject* BG = new CGameObject();
		FnAddGameObject(eLayerType::BG, BG);

		CMeshRenderer* mr = BG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Loading"));

		BG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
		BG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));
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
}