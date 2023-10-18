#include "CSceneLoading.h"

#include "CCommon.h"
#include <cmath>

extern yha::CApplication MyApplication;

namespace yha
{
	CSceneLoading::CSceneLoading()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
		, mLight(nullptr)
		, mCntFall(0)
		, mFlagEnterRollGrass(false)
		, mChkSecond(0.f)
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
		// Light
		//==================================================================
		mLight = new CGameObject();
		mLight->FnSetName(L"Light_Directional");
		FnAddGameObject(eLayerType::Light, mLight);
		CLight* lightComp = mLight->FnAddComponent<CLight>();
		lightComp->FnSetType(eLightType::Directional);
		lightComp->FnSetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
		//lightComp->FnSetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));
		mLight->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
		//CCollider2D* cd = light->FnAddComponent<CCollider2D>();

		//==================================================================
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 0.999f), eLayerType::BG);
		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_Loading"));
		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(CApplication::FnGetScaleFullWidth(), CApplication::FnGetScaleFullHeight(), 0.f));

		//==================================================================
		// Loading Progress Bar
		//==================================================================
		mUI_Loading_Floor = object::FnInstantiate<CGameObject>(Vector3(0.f, -1.5f, POS_Z_DEFAULT), eLayerType::UI);
		mr = mUI_Loading_Floor->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Loading_Floor"));
		mUI_Loading_Floor->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (53.f * 3.f) / 320.f, 0.f));

		mUI_Loading_Grass = object::FnInstantiate<CGameObject>(Vector3(0.f, -1.3f, POS_Z_FRONT_1), eLayerType::UI);
		mr = mUI_Loading_Grass->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Loading_Grass"));
		mUI_Loading_Grass->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (27.f * 3.f) / 310.f, 0.f));

		//mUI_Loading_GrassFake = object::FnInstantiate<CGameObject>(Vector3(1.0f, -1.3f, POS_Z_FRONT_1), eLayerType::UI);
		//mr = mUI_Loading_GrassFake->FnAddComponent<CMeshRenderer>();
		//mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Loading_Grass_Fake"));
		//mUI_Loading_GrassFake->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.f, (27.f * 3.f) / 310.f, 0.f));
		//CCollider2D* cd = mUI_Loading_GrassFake->FnAddComponent<CCollider2D>();

		mUI_Loading_Tag = object::FnInstantiate<CGameObject>(Vector3(-1.2f, 2.f, POS_Z_FRONT_2), eLayerType::UI);
		//mUI_Loading_Tag = object::FnInstantiate<CGameObject>(Vector3(-1.2f, -0.9f, POS_Z_FRONT_2), eLayerType::UI);
		mr = mUI_Loading_Tag->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Loading_Tag"));
		mUI_Loading_Tag->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.f, (73.f * 1.f) / 73.f, 0.f));







		//mUI_Loading_Grass = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);

		//mr = mUI_Loading_Grass->FnAddComponent<CMeshRenderer>();
		//mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

		//CAnimator* at = mUI_Loading_Grass->FnAddComponent<CAnimator>();
		//std::shared_ptr<CTexture> atlas_Grass
		//	= CResources::FnLoad<CTexture>(L"Grass", L"..\\Resources\\Texture\\MyGame\\UI\\Loading_Grass.png");
		//at->FnCreate(
		//	// name,				atlas,					leftTop
		//	L"Grass", atlas_Grass, Vector2(0.f, 0.f)
		//	// size,							columnLength,	offset,			duration
		//	, Vector2(310.f / 1.f, 27.f), 1, Vector2(0.f, 0.f), 0.08f
		//);

		//mUI_Loading_Grass->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, -1.3f, POS_Z_FRONT_1));
		//at->FnPlayAnimation(L"Grass", true);

	}

	void CSceneLoading::FnInitialize()
	{
	}

	void CSceneLoading::FnUpdate()
	{
		mChkSecond += CTime::FnDeltaTime();

		//==================================================================
		// Way1 - Load NextScene
		//==================================================================
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_MainMenu");

		if (CInput::FnGetKeyDown(eKeyCode::B))
			CSceneManager::FnLoadScene(L"Scene_Intro");

		//==================================================================
		// ÀÜµð·Ñ ³«ÇÏ
		//==================================================================
		if(!mFlagEnterRollGrass)
			FnFallGrass();

		//==================================================================
		// ÀÜµð·Ñ ±¼¸®±â
		//==================================================================
		if (mFlagEnterRollGrass)
			FnRollGrass();

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
		mCntFall			= 0;
		mFlagEnterRollGrass = false;
		mChkSecond			= 0.f;
		mDegree				= mPi;
		mTagScale			= 1.f;
		mGrassScale			= 1.f;

		FnDoInitialize();
	}

	void CSceneLoading::FnOnExit()
	{
		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
		object::FnDestroy(mLight);

		//object::FnDestroy(mUI_Loading_Floor);
		//object::FnDestroy(mUI_Loading_Grass);
		object::FnDestroy(mUI_Loading_Tag);
	}

	void CSceneLoading::FnFallGrass()
	{
		CTransform* tr = mUI_Loading_Tag->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();
		float jumpPower = 0.4f;

		switch (mCntFall)
		{
		case 0:
		{
			// ³«ÇÏ
			pos.y -= 0.5f * 9.8f * mChkSecond * CTime::FnDeltaTime();

			// rotation
			mDegree = mPi * mChkSecond;
			mUI_Loading_Tag->FnGetComponent<CTransform>()->FnSetRotation(Vector3(0.0f, 0.0f, -mDegree));

			if (-0.9f >= pos.y)
				++mCntFall;
		}
		break;
		case 1:
		{
			// Á¡ÇÁ
			pos.y += (jumpPower * jumpPower) / (2 * 9.8f);

			// rotation
			mDegree = mPi * mChkSecond;
			mUI_Loading_Tag->FnGetComponent<CTransform>()->FnSetRotation(Vector3(0.0f, 0.0f, mDegree));

			if (0.2f <= pos.y)
			{
				mChkSecond = 0.f;
				++mCntFall;
			}
		}	
		break;
		case 2:
		{
			// ³«ÇÏ
			pos.y -= 0.5f * 9.8f * mChkSecond * CTime::FnDeltaTime();

			// rotation
			mDegree = mPi * mChkSecond;
			mUI_Loading_Tag->FnGetComponent<CTransform>()->FnSetRotation(Vector3(0.0f, 0.0f, -mDegree));

			if (-0.9f >= pos.y)
				mFlagEnterRollGrass = true;
		}
		break;
		}

		// ÁÂÇ¥ ¼ÂÆÃ
		tr->FnSetPosition(pos);

	}//END-void CSceneLoading::FnFallGrass

	void CSceneLoading::FnRollGrass()
	{
		CTransform* tr = mUI_Loading_Tag->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		CTransform* trGrass = mUI_Loading_Grass->FnGetComponent<CTransform>();
		Vector3 posGrass = trGrass->FnGetPosition();

		float acceleration = 1.8f;

		//==================================================================
		// ÀÜµð·Ñ
		//==================================================================
		// move : ÁÂÃøÀ¸·Î ¿òÁ÷ÀÓ
		//pos.x += 1.3f * CTime::FnDeltaTime();
		pos.x += 1.f * CTime::FnDeltaTime() + 0.5 * acceleration * mChkSecond * CTime::FnDeltaTime();

		// rotation : ±¸¸£´Â ¹æÇâ
		mDegree = mPi * mChkSecond;
		mUI_Loading_Tag->FnGetComponent<CTransform>()->FnSetRotation(Vector3(0.0f, 0.0f, -mDegree));

		// size : ±¸¸£¸é¼­ ÀÛ¾ÆÁö±â
		if (mTagScale > 0)
		{
			mTagScale -= 0.3f * CTime::FnDeltaTime();
			pos.y -= 0.12f * CTime::FnDeltaTime();
		}
		mUI_Loading_Tag->FnGetComponent<CTransform>()->FnSetScale(Vector3(mTagScale, (73.f * mTagScale) / 73.f, 0.f));

		// ÁÂÇ¥ ¼ÂÆÃ
		tr->FnSetPosition(pos);

		//==================================================================
		// ÀÜµð
		//==================================================================
		//// move : ÁÂÃøÀ¸·Î ¿òÁ÷ÀÓ
		//posGrass.x += 0.85f * CTime::FnDeltaTime();

		//if (mGrassScale <= 3.f)
		//{
		//	mGrassScale += 1.f * CTime::FnDeltaTime();
		//}
		//mUI_Loading_Grass->FnGetComponent<CTransform>()->FnSetScale(Vector3(mGrassScale, (27.f * 3.f) / 310.f, 0.f));

		//// ÁÂÇ¥ ¼ÂÆÃ
		//trGrass->FnSetPosition(posGrass);

		//==================================================================
		// Load NextScene
		//==================================================================
		if (pos.x >= 1.3f)
			CSceneManager::FnLoadScene(L"Scene_MainMenu");

	}//END-void CSceneLoading::FnRollGrass
}