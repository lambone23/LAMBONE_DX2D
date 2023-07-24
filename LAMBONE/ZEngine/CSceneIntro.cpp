#include "CSceneIntro.h"

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
#include "CTime.h"
#include "CComponent.h"
#include "CCollider2D.h"
#include "CPlayerScript.h"
#include "CCollisionManager.h"
#include "CAnimator.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CSceneIntro::CSceneIntro()
		: mCamera(nullptr)
		, mBG(nullptr)
	{
	}
	CSceneIntro::~CSceneIntro()
	{
	}

	void CSceneIntro::FnDoInitialize()
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
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 0.0f), eLayerType::BG);

		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Intro"));

		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(MyApplication.ScaleWidth, MyApplication.ScaleHeight, 0.f));
	}

	void CSceneIntro::FnInitialize()
	{
	}

	void CSceneIntro::FnUpdate()
	{
		//==================================================================
		// Way1 - Load NextScene
		//==================================================================
		//if (CInput::FnGetKey(eKeyCode::N))
		//if (CInput::FnGetKeyState(eKeyCode::N) == eKeyState::Down)
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_Loading");
		
		//==================================================================
		// Way2 - Load NextScene
		//==================================================================
		//static float chkTime = 0.0f;
		//chkTime += CTime::FnDeltaTime();

		//if (chkTime > 2.0f)
		//{
		//	//object::FnDestroy(mBG);
		//	CSceneManager::FnLoadScene(L"Scene_Loading");
		//}

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
		//==================================================================
		// MessageBox
		//==================================================================
		//std::wstring name = CSceneManager::FnGetActiveSceneName();
		//if (name == L"Scene_Intro")
		//{
		//	HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		//	TCHAR Temp[256] = { 0, };
		//	_stprintf_s(Temp, L"Welcome");
		//	MessageBox(Tmp_mHwnd, Temp, L"START", MB_OK);
		//}

		FnDoInitialize();
	}

	void CSceneIntro::FnOnExit()
	{
		//==================================================================
		// MessageBox
		//==================================================================
		//std::wstring name = CSceneManager::FnGetActiveSceneName();
		//if (name == L"Scene_Intro")
		//{
		//	HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		//	TCHAR Temp[256] = { 0, };
		//	_stprintf_s(Temp, L"Bye");
		//	MessageBox(Tmp_mHwnd, Temp, L"END", MB_OK);
		//}

		object::FnDestroy(mCamera);
		object::FnDestroy(mBG);
	}
}
