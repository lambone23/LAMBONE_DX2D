#include "CSceneIntro.h"

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
	CSceneIntro::CSceneIntro()
	{
	}
	CSceneIntro::~CSceneIntro()
	{
	}
	void CSceneIntro::FnInitialize()
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
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Intro"));

		BG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
		BG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));


	}
	void CSceneIntro::FnUpdate()
	{
		//if (CInput::FnGetKey(eKeyCode::N))
		if (CInput::FnGetKeyDown(eKeyCode::N))
		//if (CInput::FnGetKeyState(eKeyCode::N) == eKeyState::Down)
		{
			CSceneManager::FnLoadScene(L"Scene_Loading");
		}

		CScene::FnUpdate();
	}
	void CSceneIntro::FnLateUpdate()
	{
		CScene::FnLateUpdate();
	}
	void CSceneIntro::FnRender()
	{
		CScene::FnRender();
	}
}