#include "CSceneIntro.h"

#include "CCommon.h"

namespace yha
{
	CSceneIntro::CSceneIntro()
		: mCamera(nullptr)
		, mBG(nullptr)
		, mlight(nullptr)
		, mChkSecond(0.f)
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
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Intro"));
		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(CApplication::FnGetScaleFullWidth(), CApplication::FnGetScaleFullHeight(), 0.f));
		//mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(7.5f , (1309.f * 7.5f) / 1990.f, 0.f)); //1990 * 1309
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
		//if (CInput::FnGetKeyDown(eKeyCode::N))
		//	CSceneManager::FnLoadScene(L"Scene_Loading");
		
		//==================================================================
		// Way2 - Load NextScene
		//==================================================================
		mChkSecond += CTime::FnDeltaTime();

		if (mChkSecond > 2.0f)
		{
			//object::FnDestroy(mBG);
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

		mChkSecond = 0.f;
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
		object::FnDestroy(mlight);
	}
}