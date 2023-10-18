#include "CSceneIntro.h"

#include "CCommon.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CSceneIntro::CSceneIntro()
		: mCamera(nullptr)
		, mBG(nullptr)
		, mLight(nullptr)
		, mLightComp(nullptr)
		, mFlagEnterFadeOut(false)
		, mChkSecond(0.f)
		, mBrightValue(0.f)
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
		mLight = new CGameObject();
		mLight->FnSetName(L"Light_Directional");
		FnAddGameObject(eLayerType::Light, mLight);

		mLightComp = mLight->FnAddComponent<CLight>();
		mLightComp->FnSetType(eLightType::Directional);
		//mLightComp->FnSetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		mLightComp->FnSetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));

		mLight->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));

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
		
		if(!mFlagEnterFadeOut)
			FnFadeIn();

		mChkSecond += CTime::FnDeltaTime();

		if (mFlagEnterFadeOut && (mChkSecond > 2.0f))
			FnFadeOut();

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

		mFlagEnterFadeOut	= false;
		mChkSecond			= 0.f;
		mBrightValue		= 0.f;
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
		object::FnDestroy(mLight);
	}

	void CSceneIntro::FnFadeIn()
	{
		if (0.7f <= mBrightValue)
		{
			mChkSecond = 0.f;
			mFlagEnterFadeOut = true;
		}
		else
		{
			mBrightValue += 0.6f * CTime::FnDeltaTime();
			mLightComp->FnSetColor(Vector4(mBrightValue, mBrightValue, mBrightValue, 1.0f));
		}
	}//END-void CSceneIntro::FnFadeIn

	void CSceneIntro::FnFadeOut()
	{
		//==================================================================
		// Way2 - Load NextScene
		//==================================================================
		if (0.0f >= mBrightValue)
		{
			CSceneManager::FnLoadScene(L"Scene_Loading");
		}
		else
		{
			mBrightValue -= 1.8f * CTime::FnDeltaTime();
			mLightComp->FnSetColor(Vector4(mBrightValue, mBrightValue, mBrightValue, 1.0f));
		}
	}//END-void CSceneIntro::FnFadeOut
}