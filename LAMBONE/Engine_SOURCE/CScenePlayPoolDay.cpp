#include "CScenePlayPoolDay.h"

#include "CGameObject.h"
#include "CInput.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CCamera.h"
#include "CCameraScript.h"
#include "CSceneManager.h"
#include "CApplication.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CScenePlayPoolDay::CScenePlayPoolDay()
	{
	}
	CScenePlayPoolDay::~CScenePlayPoolDay()
	{
	}
	void CScenePlayPoolDay::FnInitialize()
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
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_PoolDay"));

		BG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
		BG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));

	}
	void CScenePlayPoolDay::FnUpdate()
	{
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_PlayPoolNight");

		CScene::FnUpdate();
	}
	void CScenePlayPoolDay::FnLateUpdate()
	{
		CScene::FnLateUpdate();
	}
	void CScenePlayPoolDay::FnRender()
	{
		CScene::FnRender();
	}
}