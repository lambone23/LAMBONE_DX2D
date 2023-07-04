#include "CSceneIntro.h"

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
		{
			CGameObject* camera = new CGameObject();
			FnAddGameObject(eLayerType::Player, camera);
			camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* cameraComp = camera->FnAddComponent<CCamera>();
			cameraComp->FnTurnLayerMask(eLayerType::UI, false);
			camera->FnAddComponent<CCameraScript>();
		}

		//==================================================================
		// UI Camera
		//==================================================================
		{
			CGameObject* camera = new CGameObject();
			FnAddGameObject(eLayerType::Player, camera);

			camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* cameraComp = camera->FnAddComponent<CCamera>();
			cameraComp->FnTurnLayerMask(eLayerType::Player, false);
			//camera->FnAddComponent<CCameraScript>();
		}

		//==================================================================
		// BG
		//==================================================================
		{
			CGameObject* BG = new CGameObject();
			FnAddGameObject(eLayerType::BG, BG);

			CMeshRenderer* mr = BG->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Intro"));

			BG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
			BG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));
		}
	}
	void CSceneIntro::FnUpdate()
	{
		//if (CInput::FnGetKey(eKeyCode::N))
		//if (CInput::FnGetKeyState(eKeyCode::N) == eKeyState::Down)
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_Loading");

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

	void CSceneIntro::FnOnEnter()
	{
		//std::wstring name = CSceneManager::FnGetActiveSceneName();
		//if (name == L"Scene_Intro")
		//{
		//	HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		//	TCHAR Temp[256] = { 0, };
		//	_stprintf_s(Temp, L"Welcome");
		//	MessageBox(Tmp_mHwnd, Temp, L"START", MB_OK);
		//}
	}

	void CSceneIntro::FnOnExit()
	{

	}
}