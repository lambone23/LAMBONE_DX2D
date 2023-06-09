#include "CSceneEnding.h"

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
	CSceneEnding::CSceneEnding()
	{
	}
	CSceneEnding::~CSceneEnding()
	{
	}
	void CSceneEnding::FnInitialize()
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
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Ending"));

		BG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
		BG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));
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
		//std::wstring name = CSceneManager::FnGetActiveSceneName();
		//if (name == L"Scene_Ending")
		//{
		//	HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		//	TCHAR Temp[256] = { 0, };
		//	_stprintf_s(Temp, L"GAME OVER");
		//	MessageBox(Tmp_mHwnd, Temp, L"END", MB_OK);
		//}
	}

	void CSceneEnding::FnOnExit()
	{

	}
}