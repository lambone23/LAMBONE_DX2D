#include "CScenePlayGrassDay.h"

#include "CGameObject.h"
#include "CInput.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CApplication.h"
#include "CGridScript.h"
#include "CObject.h"
#include "CRenderer.h"
#include "CCameraScript.h"
#include "CTime.h"
#include "CComponent.h"
#include "CCollider2D.h"
#include "CPlayerScript.h"
#include "CCollisionManager.h"
#include "CAnimator.h"
#include "CLight.h"
#include "CComputeShader.h"
#include "CPaintShader.h"
#include "CParticleSystem.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CScenePlayGrassDay::CScenePlayGrassDay()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
	{
	}
	CScenePlayGrassDay::~CScenePlayGrassDay()
	{
	}

	void CScenePlayGrassDay::FnDoInitialize()
	{
		CCollisionManager::FnSetLayer(eLayerType::PlayerNearbyAttack, eLayerType::Monster, true);
		CCollisionManager::FnSetLayer(eLayerType::PlayerFarAttack, eLayerType::Monster, true);
		
		std::shared_ptr<CPaintShader> paintShader	= CResources::FnFind<CPaintShader>(L"PaintShader");
		std::shared_ptr<CTexture> paintTexture		= CResources::FnFind<CTexture>(L"PaintTexuture");
		paintShader->FnSetTarget(paintTexture);
		paintShader->FnOnExcute();

		//==================================================================
		// Camera
		//==================================================================
		CCamera* cameraComp = nullptr;

		//-------------------------------------
		// Main Camera
		//-------------------------------------
		mCamera_Main = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
		cameraComp = mCamera_Main->FnAddComponent<CCamera>();
		cameraComp->FnTurnLayerMask(eLayerType::UI, false);
		mCamera_Main->FnAddComponent<CCameraScript>();

		renderer::cameras.push_back(cameraComp);
		renderer::mainCamera = cameraComp;

		//-------------------------------------
		// UI Camera
		//-------------------------------------
		mCamera_UI = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, -10.0f), eLayerType::Camera);
		cameraComp = mCamera_UI->FnAddComponent<CCamera>();
		cameraComp->FnTurnLayerMask(eLayerType::BG, false);
		cameraComp->FnTurnLayerMask(eLayerType::PlayerNearbyAttack, false);
		cameraComp->FnTurnLayerMask(eLayerType::PlayerFarAttack, false);
		cameraComp->FnTurnLayerMask(eLayerType::Monster, false);
		//mCamera_UI->FnAddComponent<CCameraScript>();

		//==================================================================
		// BG
		//==================================================================
		mBG = object::FnInstantiate<CGameObject>(Vector3(1.5f, 0.0f, 0.999f), eLayerType::BG);

		CMeshRenderer* mr = mBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"BG_GrassDay"));

		//mBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.5f, 0.0f, 0.999f));
		mBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(11.f, 33.f / 7.f, 0.f));

		//==================================================================
		// Grid (After Camera Set)
		//==================================================================
		//{
		//	CGameObject* grid = new CGameObject();
		//	grid->FnSetName(L"Grid");
		//	FnAddGameObject(eLayerType::Grid, grid);

		//	CMeshRenderer* mr = grid->FnAddComponent<CMeshRenderer>();
		//	mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		//	mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GridMaterial"));
		//	CGridScript* gridSc = grid->FnAddComponent<CGridScript>();
		//	gridSc->FnSetCamera(cameraComp);
		//}

		//==================================================================
		// Light
		//==================================================================
		{// Light [Directional]
			mlight = new CGameObject();
			mlight->FnSetName(L"Light_Directional");
			FnAddGameObject(eLayerType::Light, mlight);
			CLight* lightComp = mlight->FnAddComponent<CLight>();
			lightComp->FnSetType(eLightType::Directional);
			lightComp->FnSetColor(Vector4(0.8f, 0.8f, 0.8f, 1.0f));
			//lightComp->FnSetColor(Vector4(0.0f, 0.0f, 0.0f, 0.0f));

			mlight->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
			//CCollider2D* cd = light->FnAddComponent<CCollider2D>();
		}

		//{// Light [Point]
		//	CGameObject* light = new CGameObject();
		//	light->FnSetName(L"Light_Point");
		//	FnAddGameObject(eLayerType::Light, light);
		//	CLight* lightComp = light->FnAddComponent<CLight>();
		//	lightComp->FnSetType(eLightType::Point);
		//	lightComp->FnSetColor(Vector4(0.0f, 0.0f, 1.0f, 1.0f));
		//	lightComp->FnSetRadius(3.0f);

		//	light->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.0f, -1.0f, 0.0f));
		//	CCollider2D* cd = light->FnAddComponent<CCollider2D>();
		//}

#pragma region Resource_UI
		//==================================================================
		// UI
		//==================================================================
		// UI_SeedChooserBG
		mUI_SeedChooserBG = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mUI_SeedChooserBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SeedChooserBG"));
		mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, 28.f / 7.f, 0.f));

		// UI_btn_Play
		mUI_btn_Play = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mUI_btn_Play->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Play"));
		mUI_btn_Play->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (80.f * 0.8f) / 180.f, 0.f));

		// mUI_SunPointChk
		mUI_SunPointChk = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mUI_SunPointChk->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SunPointChk"));
		mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.5f, (34.f * 1.5f) / 123.f, 0.f));

		// UI_ShovelBG
		mUI_ShovelBG = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mUI_ShovelBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_ShovelBG"));
		mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (72.f * 0.4f) / 70.f, 0.f));

		// UI_Shovel
		mUI_Shovel = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.009f), eLayerType::UI);
		mr = mUI_Shovel->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Shovel"));
		mUI_Shovel->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.35f, (125.f * 0.35f) / 116.f, 0.f));

		// UI_btn_Menu
		mUI_btn_Menu = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mUI_btn_Menu->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Menu"));
		mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.33f, (48.f * 1.33f) / 120.f, 0.f));

		// UI_FlagMeterEmpty
		mUI_FlagMeterEmpty = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mUI_FlagMeterEmpty->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterEmpty"));
		mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetScale(Vector3(2.5f, (21.f * 2.5f) / 157.f, 0.f));

		// UI_FlagMeterParts_Zombie
		mUI_FlagMeterParts_Zombie = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.008f), eLayerType::UI);
		mr = mUI_FlagMeterParts_Zombie->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Zombie"));
		mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (25.f * 0.4f) / 25.f, 0.f));

		// UI_FlagMeterParts_Flag
		mUI_FlagMeterParts_Flag = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.009f), eLayerType::UI);
		mr = mUI_FlagMeterParts_Flag->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// UI_FlagMeterParts_FlagFin
		mUI_FlagMeterParts_FlagFin = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.009f), eLayerType::UI);
		mr = mUI_FlagMeterParts_FlagFin->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// Card_SunFlower
		mCard_SunFlower = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower2 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower2->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower2->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower3 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower3->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower3->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower4 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower4->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower4->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower5 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower5->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower5->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower6 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower6->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower6->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower7 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower7->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower7->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		mCard_SunFlower8 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.010f), eLayerType::UI);
		mr = mCard_SunFlower8->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower8->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (60.f * 0.8f) / 100.f, 0.f));

		//mCard_Peashooter = new CGameObject();
		//FnAddGameObject(eLayerType::UI, mCard_Peashooter);

		//mCard_WallNut = new CGameObject();
		//FnAddGameObject(eLayerType::UI, mCard_WallNut);

		//mCard_CherryBomb = new CGameObject();
		//FnAddGameObject(eLayerType::UI, mCard_CherryBomb);
#pragma endregion
#pragma region Resource_Plants
		//==================================================================
		// Plants
		//==================================================================
		//-------------------------------------
		// SunFlower
		//-------------------------------------
		mPl_SunFlower = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::PlayerNearbyAttack);
		mPl_SunFlower->FnSetName(L"GrassDay_SunFlower");

		//CCollider2D* cd = mPl_SunFlower->FnAddComponent<CCollider2D>();
		//cd->FnSetSize(Vector2(1.f, 1.f));

		mr = mPl_SunFlower->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));
		//mPl_SunFlower->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, 28.f / 7.f, 0.f));

		std::shared_ptr<CTexture> atlas_SunFlower = CResources::FnLoad<CTexture>(L"SunFlower", L"..\\Resources\\Texture\\MyGame\\Plants\\SunFlower\\SunFlower.png");
		CAnimator* at_SunFlower = mPl_SunFlower->FnAddComponent<CAnimator>();
		// name, atlas, leftTop, size, columnLength, offset, duration
		at_SunFlower->FnCreate(
			L"Idle"						// name
			, atlas_SunFlower			// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(1314.0f / 18.f, 74.0f)		// size
			, 18						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		//CAnimator* at = mPl_SunFlower->FnAddComponent<CAnimator>();
		//at->FnCreateAnimations(L"..\\Resources\\Texture\\MyGame\\Plants\\SunFlower", 0.1f);

		at_SunFlower->FnPlayAnimation(L"Idle", true);
		//mPl_SunFlower->FnAddComponent<CPlayerScript>();

		//-------------------------------------
		// Peashooter
		//-------------------------------------
		mPl_Peashooter1 = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::PlayerNearbyAttack);
		mPl_Peashooter1->FnSetName(L"GrassDay_Peashooter");

		mr = mPl_Peashooter1->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

		std::shared_ptr<CTexture> atlas_Peashooter = CResources::FnLoad<CTexture>(L"Peashooter", L"..\\Resources\\Texture\\MyGame\\Plants\\Peashooter\\Peashooter.png");
		CAnimator* at_Peashooter = mPl_Peashooter1->FnAddComponent<CAnimator>();
		at_Peashooter->FnCreate(
			L"Idle"						// name
			, atlas_Peashooter			// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(923.0f / 13.f, 71.0f)		// size
			, 13						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);
		at_Peashooter->FnPlayAnimation(L"Idle", true);

		cd_Peashooter1 = mPl_Peashooter1->FnAddComponent<CCollider2D>();
		cd_Peashooter1->FnSetSize(Vector2(0.3f, 0.3f));
		cd_Peashooter1->FnSetCenter(Vector2(0.f, 0.f));
		cd_Peashooter1->FnSetAttackType(eAttackType::Nearby);

		//-------------------------------------
		// Chomper
		//-------------------------------------
		mPl_Chomper = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::PlayerNearbyAttack);
		mPl_Chomper->FnSetName(L"GrassDay_Chomper");

		cd_Chomper = mPl_Chomper->FnAddComponent<CCollider2D>();
		cd_Chomper->FnSetSize(Vector2(0.5f, 0.5f));
		cd_Chomper->FnSetCenter(Vector2(-0.1f, -0.05f));

		mr = mPl_Chomper->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

		// Animation
		at_Chomper = mPl_Chomper->FnAddComponent<CAnimator>();

		// Idle
		std::shared_ptr<CTexture> atlas_Chomper_Idle = CResources::FnLoad<CTexture>(L"Chomper_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Idle.png");
		at_Chomper->FnCreate(
			L"Idle"						// name
			, atlas_Chomper_Idle		// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(1690.0f / 13.f, 114.0f)		// size
			, 13						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);
		
		// Attack
		std::shared_ptr<CTexture> atlas_Chomper_Attack = CResources::FnLoad<CTexture>(L"Chomper_Attack", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Attack.png");
		at_Chomper->FnCreate(
			L"Attack"					// name
			, atlas_Chomper_Attack		// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(1170.0f / 9.f, 114.0f)		// size
			, 9							// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		at_Chomper->FnPlayAnimation(L"Idle", true);
		//at_Chomper->FnPlayAnimation(L"Attack", true);
		//mPl_Chomper->FnAddComponent<CPlayerScript>();

		//-------------------------------------
		// WallNut
		//-------------------------------------
		mPl_WallNut = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::PlayerNearbyAttack);
		mPl_WallNut->FnSetName(L"GrassDay_WallNut");

		cd_WallNut = mPl_WallNut->FnAddComponent<CCollider2D>();
		cd_WallNut->FnSetSize(Vector2(0.3f, 0.35f));

		mr = mPl_WallNut->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

		// Animation
		at_WallNut = mPl_WallNut->FnAddComponent<CAnimator>();

		// Idle
		std::shared_ptr<CTexture> atlas_WallNut_Idle = CResources::FnLoad<CTexture>(L"WallNut_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\WallNut_Idle.png");
		at_WallNut->FnCreate(
			L"Idle"			// name
			, atlas_WallNut_Idle		// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(1040.0f / 16.f, 73.0f)		// size
			, 16						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		// Cracked1
		std::shared_ptr<CTexture> atlas_WallNut_Cracked1 = CResources::FnLoad<CTexture>(L"WallNut_Cracked1", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\WallNut_Cracked1.png");
		at_WallNut->FnCreate(
			L"Cracked1"		// name
			, atlas_WallNut_Cracked1	// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(715.0f / 11.f, 73.0f)		// size
			, 11						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		// Cracked2
		std::shared_ptr<CTexture> atlas_Chomper_Cracked2 = CResources::FnLoad<CTexture>(L"WallNut_Cracked2", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\WallNut_Cracked2.png");
		at_WallNut->FnCreate(
			L"Cracked2"		// name
			, atlas_Chomper_Cracked2		// atlas
			, Vector2(0.0f, 0.0f)			// leftTop
			, Vector2(975.0f / 15.f, 73.0f)		// size
			, 15						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		at_WallNut->FnPlayAnimation(L"Idle", true);

#pragma endregion
#pragma region Resource_Zombies
		//==================================================================
		// Zombies
		//==================================================================
		//-------------------------------------
		// NormalZombie
		//-------------------------------------
		mZb_NormalZombie = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.2f), eLayerType::Monster);
		mZb_NormalZombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.0f, -1.0f, 0.2f));
		
		mZb_NormalZombie->FnSetName(L"GrassDay_NormalZombie");

		cd_NormalZombie = mZb_NormalZombie->FnAddComponent<CCollider2D>();
		cd_NormalZombie->FnSetSize(Vector2(0.2f, 0.53f));
		//cd_NormalZombie->FnSetCenter(Vector2(0.09f, -0.05f));

		mr = mZb_NormalZombie->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

		// Animation
		at_NormalZombie = mZb_NormalZombie->FnAddComponent<CAnimator>();

		// Idle
		std::shared_ptr<CTexture> atlas_NormalZombie_Idle = CResources::FnLoad<CTexture>(L"NormalZombie_Idle", L"..\\Resources\\Texture\\MyGame\\Zombies\\NormalZombie\\NormalZombie_Idle.png");
		at_NormalZombie->FnCreate(
			L"Idle"						// name
			, atlas_NormalZombie_Idle	// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(3652.0f / 22.f, 144.0f)		// size
			, 22						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		// Attack
		std::shared_ptr<CTexture> atlas_NormalZombie_Attack = CResources::FnLoad<CTexture>(L"NormalZombie_Attack", L"..\\Resources\\Texture\\MyGame\\Zombies\\NormalZombie\\NormalZombie_Attack.png");
		at_NormalZombie->FnCreate(
			L"Attack"					// name
			, atlas_NormalZombie_Attack	// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(3486.0f / 21.f, 144.0f)		// size
			, 21						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		at_NormalZombie->FnPlayAnimation(L"Idle", true);
		mZb_NormalZombie->FnAddComponent<CPlayerScript>();
#pragma endregion
	}//END-void CScenePlayGrassDay::FnDoInitialize

	void CScenePlayGrassDay::FnInitialize()
	{
	}

	void CScenePlayGrassDay::FnUpdate()
	{
		//==================================================================
		// Main Camera Move
		//==================================================================
		CTransform* tr = mCamera_Main->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		// 화면 이동 ( -->> )
		while (MyApplication.mFlagChkFirst)
		{
			mChkSecond += CTime::FnDeltaTime();

			if (mChkSecond > 1.0f)
			{
				pos.x += 2.0f * CTime::FnDeltaTime();
				tr->FnSetPosition(pos);
				break;
			}
		}

		// 화면 고정
		if (pos.x > 3.f)
			MyApplication.mFlagChkFirst = false;

		//==================================================================
		// Choose Plants
		//==================================================================
		if (!MyApplication.mFlagChkFirst)
		{
			if (mFlagShowSeedChooser)
			{
				// UI_SeedChooserBG
				mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, 0.2f, 0.010f));

				// UI_btn_Play
				mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, 0.010f));
			}

			// UI_btn_Play 클릭하면
			if (CInput::FnGetKey(eKeyCode::LBUTTON))
			{
				HWND Tmp_mHwnd = MyApplication.FnGetHwnd();

				//VectorXY MousePos = CInput::FnGetMousePos();
				::POINT MousePos = {};
				::GetCursorPos(&MousePos);
				::ScreenToClient(Tmp_mHwnd, &MousePos);

				if ((MousePos.x >= 520.f) && (MousePos.x <= 675.f)
					&& (MousePos.y >= 819.f) && (MousePos.y <= 880.f))
				{
					mFlagClickEvent_BtnPlay = true;
					mFlagShowSeedChooser = false;

					mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, 0.010f));
					mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.f, 0.f, 0.f));
					mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, 0.010f));
					mUI_btn_Play->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.f, 0.f, 0.f));
				}
			}

			// 화면 이동 ( <<-- )
			while (!MyApplication.mFlagChkFirst && mFlagClickEvent_BtnPlay)
			{
				mChkSecond += CTime::FnDeltaTime();

				if (mChkSecond > 1.0f)
				{
					pos.x -= 2.0f * CTime::FnDeltaTime();
					tr->FnSetPosition(pos);
					break;
				}
			}

			// 화면 고정
			if (pos.x < 0.f)
			{
				mFlagClickEvent_BtnPlay = false;
				mFlagPlay = true;
			}
		}

		//==================================================================
		// Play
		//==================================================================
		if (mFlagPlay && mFlagChkEnterScene)
		{
#pragma region Resource_UI
			//==================================================================
			// UI
			//==================================================================
			// mUI_SunPointChk
			mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.7f, 2.f, 0.010f));

			// UI_ShovelBG
			mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, 0.010f));

			// UI_Shovel
			mUI_Shovel->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, 0.009f));

			// UI_btn_Menu
			mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetPosition(Vector3(3.3f, 1.98f, 0.010f));

			// UI_FlagMeterEmpty
			mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, 0.010f));

			// UI_FlagMeterParts_Zombie
			mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.45f, 2.05f, 0.008f));

			// UI_FlagMeterParts_Flag
			mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, 0.009f));

			// UI_FlagMeterParts_FlagFin
			mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.33f, 2.05f, 0.009f));
#pragma endregion
#pragma region Resource_Cards
			//==================================================================
			// Cards
			//==================================================================
			// Card_SunFlower
			mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 2.f, 0.010f));
			mCard_SunFlower2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 1.5f, 0.010f));
			mCard_SunFlower3->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 1.f, 0.010f));
			mCard_SunFlower4->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 0.5f, 0.010f));
			mCard_SunFlower5->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, 0.f, 0.010f));
			mCard_SunFlower6->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -0.5f, 0.010f));
			mCard_SunFlower7->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -1.f, 0.010f));
			mCard_SunFlower8->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -1.5f, 0.010f));
#pragma endregion
#pragma region Resource_Plants
			//==================================================================
			// Plants
			//==================================================================
			mPl_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.1f, 0.5f, 0.3f));

			//-------------------------------------
			// Peashooter Status
			//-------------------------------------
			mPl_Peashooter1->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.1f, -0.2f, 0.3f));

			if (eColliderStateType::Start == cd_Peashooter1->FnGetColliderState())
				if(eColliderStateType::Ing == cd_Peashooter1->FnGetColliderState())
				 int a = 0;
			
			//-------------------------------------
			// Chomper Status
			//-------------------------------------
			mPl_Chomper->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -1.0f, 0.3f));

			if (eColliderStateType::Start == cd_Chomper->FnGetColliderState())
			{
				at_Chomper->FnPlayAnimation(L"Attack", true);
				FlagChomperOnceIdleDid = false;
			}
			else if(eColliderStateType::Fin == cd_Chomper->FnGetColliderState() && false == FlagChomperOnceIdleDid)
			{
				FlagChomperOnceIdleDid = true;
				at_Chomper->FnPlayAnimation(L"Idle", true);
			}

			//-------------------------------------
			// WallNut Status
			//-------------------------------------
			if (false == FlagWallNut)
				mPl_WallNut->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.5f, 0.5f, 0.3f));

			if (eColliderStateType::Start == cd_WallNut->FnGetColliderState())
				at_WallNut->FnPlayAnimation(L"Cracked1", true);

			mChkSecond += (float)CTime::FnDeltaTime();

			if ((mChkSecond >= 10.0f)
				&& (eColliderStateType::Ing == cd_WallNut->FnGetColliderState()))
			{
				at_WallNut->FnPlayAnimation(L"Cracked2", true);
				FlagWallNut = true;
				mChkSecond = 0.f;
			}

			if ((mChkSecond >= 2.0f)
				&& true == FlagWallNut
				&& eColliderStateType::Ing == cd_WallNut->FnGetColliderState())
			{
				mPl_WallNut->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, 0.3f));
			}
#pragma endregion
#pragma region Resource_Zombies
			//==================================================================
			// Zombies
			//==================================================================
			//-------------------------------------
			// NormalZombie Status
			//-------------------------------------
			if (false == FlagNormalZombie)
			{
				mZb_NormalZombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.0f, -1.0f, 0.2f));
				FlagNormalZombie = true;
			}

/*			if (eColliderStateType::Start == cd_NormalZombie->FnGetColliderState())
			{
				if (eColliderStateType::Start == cd_Peashooter1->FnGetColliderState())
				{
					at_NormalZombie->FnPlayAnimation(L"Idle", true);
				}
				else
				{
					at_NormalZombie->FnPlayAnimation(L"Attack", true);
					FlagNormalZombieOnceIdleDid = false;
				}

			}
			else */
			if (eColliderStateType::Ing == cd_NormalZombie->FnGetColliderState() && false == FlagNormalZombieOnceIdleDid)
			{
				FlagNormalZombieOnceIdleDid = true;
				at_NormalZombie->FnPlayAnimation(L"Attack", true);
			}
			else if (eColliderStateType::Fin == cd_NormalZombie->FnGetColliderState() && true == FlagNormalZombieOnceIdleDid)
			{
				FlagNormalZombieOnceIdleDid = false;
				at_NormalZombie->FnPlayAnimation(L"Idle", true);
			}
#pragma endregion

			if (CInput::FnGetKey(eKeyCode::F))
			{
				at_Chomper->FnPlayAnimation(L"Attack", true);
			}
			if (CInput::FnGetKey(eKeyCode::G))
			{
				at_Chomper->FnPlayAnimation(L"Idle", true);
			}

		}

		//==================================================================
		// Load NextScene
		//==================================================================
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_PlayGrassNight");

		CScene::FnUpdate();
	}
	void CScenePlayGrassDay::FnLateUpdate()
	{
		Vector3 pos(600, 450, 0.0f);
		Vector3 pos2(600, 450, 1000.0f);
		Viewport viewport;
		viewport.width = 1600.0f;
		viewport.height = 900.0f;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		pos = viewport.Unproject(pos, CCamera::FnGetGpuProjectionMatrix(), CCamera::FnGetGpuViewMatrix(), Matrix::Identity);
		pos2 = viewport.Unproject(pos2, CCamera::FnGetGpuProjectionMatrix(), CCamera::FnGetGpuViewMatrix(), Matrix::Identity);

		CScene::FnLateUpdate();
	}
	void CScenePlayGrassDay::FnRender()
	{
		CScene::FnRender();
	}
	void CScenePlayGrassDay::FnOnEnter()
	{
		MyApplication.mFlagChkFirst = true;
		mFlagChkEnterScene = true;

		FnDoInitialize();
	}

	void CScenePlayGrassDay::FnOnExit()
	{
		MyApplication.mFlagChkFirst = true;
		mChkSecond = 0.0f;

		mFlagChkEnterScene = false;
		mFlagPlay = false;
		mFlagClickEvent_BtnPlay = false;
		mFlagShowSeedChooser = true;

		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
		object::FnDestroy(mlight);

		object::FnDestroy(mUI_SeedChooserBG);
		object::FnDestroy(mUI_btn_Play);

		object::FnDestroy(mUI_SunPointChk);
		object::FnDestroy(mUI_ShovelBG);
		object::FnDestroy(mUI_Shovel);

		object::FnDestroy(mUI_FlagMeterEmpty);
		object::FnDestroy(mUI_FlagMeterParts_Zombie);
		object::FnDestroy(mUI_FlagMeterParts_Flag);
		object::FnDestroy(mUI_FlagMeterParts_FlagFin);

		object::FnDestroy(mUI_btn_Menu);

		object::FnDestroy(mCard_SunFlower);
		object::FnDestroy(mCard_SunFlower2);
		object::FnDestroy(mCard_SunFlower3);
		object::FnDestroy(mCard_SunFlower4);
		object::FnDestroy(mCard_SunFlower5);
		object::FnDestroy(mCard_SunFlower6);
		object::FnDestroy(mCard_SunFlower7);
		object::FnDestroy(mCard_SunFlower8);

		object::FnDestroy(mPl_SunFlower);
		object::FnDestroy(mPl_Peashooter1);
		object::FnDestroy(mPl_Chomper);
		object::FnDestroy(mPl_WallNut);

		object::FnDestroy(mZb_NormalZombie);
		
	}
}
