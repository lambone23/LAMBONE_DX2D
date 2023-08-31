/* 
	************
	* Flow
	************
	0. Main Camera Move to RIGHT
	1. Choose Plants
	2. Main Camera Move to LEFT
	3. Play
*/

#include "CScenePlayGrassDay.h"

#include "CCommon.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CScenePlayGrassDay::CScenePlayGrassDay()
		: mCamera_Main(nullptr)
		, mCamera_UI(nullptr)
		, mBG(nullptr)
		, mCntPickedCard(0)
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
		cameraComp->FnTurnLayerMask(eLayerType::UI2, false);
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
		// Light [Directional]
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
		// UI
		//==================================================================
#pragma region Resource_UI
		//-------------------------------------
		// Choose Plants
		//-------------------------------------
		// UI_SeedChooserBG
		mUI_SeedChooserBG = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SeedChooserBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SeedChooserBG"));
		mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(3.5f, 28.f / 7.f, 0.f));

		// UI_btn_Play
		mUI_btn_Play = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_Play->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Play"));
		mUI_btn_Play->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (80.f * 0.8f) / 180.f, 0.f));

		// UI_btn_Play_Disabled
		mUI_btn_Play_Disabled = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_Play_Disabled->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Play_Disabled"));
		mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.8f, (80.f * 0.8f) / 180.f, 0.f));

		// UI_btn_ResetChoose
		mUI_btn_ResetChoose = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_ResetChoose->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_ResetChoose"));
		mUI_btn_ResetChoose->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.25f, (53.f * 0.25f) / 55.f, 0.f));

		//-------------------------------------
		// Play
		//-------------------------------------
		// UI_SunPointChk
		mUI_SunPointChk = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_SunPointChk->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SunPointChk"));
		mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.5f, (34.f * 1.5f) / 123.f, 0.f));

		// UI_ShovelBG
		mUI_ShovelBG = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_ShovelBG->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_ShovelBG"));
		mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (72.f * 0.4f) / 70.f, 0.f));

		// UI_Shovel
		mUI_Shovel = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_Shovel->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Shovel"));
		mUI_Shovel->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.35f, (125.f * 0.35f) / 116.f, 0.f));

		// UI_FlagMeterEmpty
		mUI_FlagMeterEmpty = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterEmpty->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterEmpty"));
		mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetScale(Vector3(2.5f, (21.f * 2.5f) / 157.f, 0.f));

		// UI_FlagMeterParts_Zombie
		mUI_FlagMeterParts_Zombie = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterParts_Zombie->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Zombie"));
		mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (25.f * 0.4f) / 25.f, 0.f));

		// UI_FlagMeterParts_Flag
		mUI_FlagMeterParts_Flag = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterParts_Flag->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// UI_FlagMeterParts_FlagFin
		mUI_FlagMeterParts_FlagFin = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_FlagMeterParts_FlagFin->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_FlagMeterParts_Flag"));
		mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.4f, (41.f * 0.4f) / 38.f, 0.f));

		// UI_btn_Menu
		mUI_btn_Menu = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mUI_btn_Menu->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_btn_Menu"));
		mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.33f, (48.f * 1.33f) / 120.f, 0.f));

		// UI_SelectedCard
		mUI_SelectedCard = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI2);
		mr = mUI_SelectedCard->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCard"));
		mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetScale(Vector3(1.f, (177.f * 0.3f) / 108.f, 0.f));

		// UI_SelectedShovel
		mUI_SelectedShovel = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI2);
		mr = mUI_SelectedShovel->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_SelectedCard"));
		mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.5f, (177.f * 0.3f) / 108.f, 0.f));
#pragma endregion

		//==================================================================
		// UI Cards
		//==================================================================
#pragma region Resource_UI_Cards
		//-------------------------------------
		// Card_EmptySpace
		//-------------------------------------
		mCard_EmptySpace1 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_EmptySpace1->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_EmptySpace"));
		mCard_EmptySpace1->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mCard_EmptySpace2 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_EmptySpace2->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_EmptySpace"));
		mCard_EmptySpace2->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mCard_EmptySpace3 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_EmptySpace3->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_EmptySpace"));
		mCard_EmptySpace3->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mCard_EmptySpace4 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_EmptySpace4->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_EmptySpace"));
		mCard_EmptySpace4->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		mCard_EmptySpace5 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_EmptySpace5->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_EmptySpace"));
		mCard_EmptySpace5->FnGetComponent<CTransform>()->FnSetScale(Vector3(0.9f, (96.f * 0.8f) / 153.f, 0.f));

		//-------------------------------------
		// Card_Plants
		//-------------------------------------
		// Card_SunFlower
		mCard_SunFlower = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_SunFlower->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_SunFlower->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_PeaShooter
		mCard_PeaShooter = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_PeaShooter->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_PeaShooter"));
		mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_WallNut
		mCard_WallNut = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_WallNut->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_WallNut"));
		mCard_WallNut->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Chomper
		mCard_Chomper = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Chomper->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Chomper"));
		mCard_Chomper->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Jalapeno
		mCard_Jalapeno = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Jalapeno->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Jalapeno"));
		mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_CherryBomb
		mCard_CherryBomb = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_CherryBomb->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_CherryBomb"));
		mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		//-------------------------------------
		// Card_Picked
		//-------------------------------------
		// Card_SunFlower
		mCard_Picked_SunFlower = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_SunFlower->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower"));
		mCard_Picked_SunFlower->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_PeaShooter
		mCard_Picked_PeaShooter = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_PeaShooter->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_PeaShooter"));
		mCard_Picked_PeaShooter->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_WallNut
		mCard_Picked_WallNut = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_WallNut->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_WallNut"));
		mCard_Picked_WallNut->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Chomper
		mCard_Picked_Chomper = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_Chomper->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Chomper"));
		mCard_Picked_Chomper->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Jalapeno
		mCard_Picked_Jalapeno = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_Jalapeno->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Jalapeno"));
		mCard_Picked_Jalapeno->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_CherryBomb
		mCard_Picked_CherryBomb = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_CherryBomb->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_CherryBomb"));
		mCard_Picked_CherryBomb->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		//-------------------------------------
		// Card_Picked_Disalbed
		//-------------------------------------
		// Card_SunFlower_Disalbed
		mCard_Picked_SunFlower_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_SunFlower_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_SunFlower_Disabled"));
		mCard_Picked_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_PeaShooter_Disalbed
		mCard_Picked_PeaShooter_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_PeaShooter_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_PeaShooter_Disabled"));
		mCard_Picked_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_WallNut_Disalbed
		mCard_Picked_WallNut_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_WallNut_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_WallNut_Disabled"));
		mCard_Picked_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Chomper_Disalbed
		mCard_Picked_Chomper_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_Chomper_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Chomper_Disabled"));
		mCard_Picked_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_Jalapeno_Disalbed
		mCard_Picked_Jalapeno_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_Jalapeno_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_Jalapeno_Disabled"));
		mCard_Picked_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);

		// Card_CherryBomb_Disalbed
		mCard_Picked_CherryBomb_Disalbed = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		mr = mCard_Picked_CherryBomb_Disalbed->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"UI_Card_CherryBomb_Disabled"));
		mCard_Picked_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
#pragma endregion

		//==================================================================
		// Plants
		//==================================================================
		//-------------------------------------
		// SunLight
		//-------------------------------------
		mSunLights.resize(45);
		//mPlants_SunFlowers[0] = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::PlayerNearbyAttack);

		for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
		{
			mSunLights[idx] = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::UI2);
			mr = mSunLights[idx]->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			std::shared_ptr<CTexture> atlas_SunLight = CResources::FnLoad<CTexture>(L"SunLight", L"..\\Resources\\Texture\\MyGame\\Plants\\SunLight.png");
			CAnimator* at_SunLight = mSunLights[idx]->FnAddComponent<CAnimator>();
			// name, atlas, leftTop, size, columnLength, offset, duration
			at_SunLight->FnCreate(
				L"Idle"						// name
				, atlas_SunLight			// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1716.f / 22.f, 78.0f)		// size
				, 22						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);
			at_SunLight->FnPlayAnimation(L"Idle", true);
		}

#pragma region Resource_Plants
		//-------------------------------------
		// SunFlower
		//-------------------------------------
		mPlants_SunFlowers.resize(45);
		//mPlants_SunFlowers[0] = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::PlayerNearbyAttack);

		for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
		{
			mPlants_SunFlowers[idx] = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.3f), eLayerType::PlayerNearbyAttack);
			mr = mPlants_SunFlowers[idx]->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			std::shared_ptr<CTexture> atlas_SunFlower = CResources::FnLoad<CTexture>(L"SunFlower", L"..\\Resources\\Texture\\MyGame\\Plants\\SunFlower\\SunFlower.png");
			CAnimator* at_SunFlower = mPlants_SunFlowers[idx]->FnAddComponent<CAnimator>();
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
			at_SunFlower->FnPlayAnimation(L"Idle", true);
		}


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
	}//END-void CScenePlayGrassDay::FnInitialize

	void CScenePlayGrassDay::FnUpdate()
	{
		//==================================================================
		// Load NextScene
		//==================================================================
		if (CInput::FnGetKeyDown(eKeyCode::N))
			CSceneManager::FnLoadScene(L"Scene_PlayGrassNight");

		//==================================================================
		// 0. Main Camera Move to RIGHT
		//==================================================================
		if (mFlagChkEnter && FnMoveCamera(eDirection::Right))
			mFlagChkEnter = false;

		//==================================================================
		// 1. Choose Plants
		//==================================================================
		if (!mFlagChkEnter && !mFlagPlay)
			FnChoosePlants();

		//==================================================================
		// 2. Main Camera Move to LEFT
		// 3. Play
		//==================================================================
		if (mFlagPlay && FnMoveCamera(eDirection::Left))
			FnPlay();

		CScene::FnUpdate();
	}//END-void CScenePlayGrassDay::FnUpdate

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
	}//END-void CScenePlayGrassDay::FnLateUpdate

	void CScenePlayGrassDay::FnRender()
	{
		CScene::FnRender();
	}//END-void CScenePlayGrassDay::FnRender

	void CScenePlayGrassDay::FnOnEnter()
	{
		mSunScore		= 50;
		mSecond			= 0.f;
		mChkSecondTmp	= 0.f;
		mFlagChkEnter	= true;
		mFlagPlay		= false;
		mCntPickedCard	= 0;

		for (int idx = 0; idx < MAXPICKED; idx++)
		{
			mPickedList[idx] = ePlantsType::End;
		}

		for (int idx = 0; idx < MAXPICKED; idx++)
		{
			mPickedCardIsDisabledList[idx] = false;
		}

		for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
		{
			mBoard[idx].flagIsPlants = false;
			mBoard[idx].plantsType = ePlantsType::End;
			mBoard[idx].IdxPlants = 999;
		}

		for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
		{
			mPlantingTimeList_SunFlowers[idx] = 999;
		}

		for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
		{
			mIdxList_SunLights[idx] = false;
		}

		for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
		{
			mIdxList_SunFlowers[idx] = false;
		}

		FnDoInitialize();
	}//END-void CScenePlayGrassDay::FnOnEnter

	void CScenePlayGrassDay::FnOnExit()
	{
		object::FnDestroy(mCamera_Main);
		object::FnDestroy(mCamera_UI);
		object::FnDestroy(mBG);
		object::FnDestroy(mlight);

		//==================================================================
		// Both
		// 0. Choose Plants
		// 1. Play
		//==================================================================
		object::FnDestroy(mCard_Picked_SunFlower);
		object::FnDestroy(mCard_Picked_PeaShooter);
		object::FnDestroy(mCard_Picked_WallNut);
		object::FnDestroy(mCard_Picked_Chomper);
		object::FnDestroy(mCard_Picked_Jalapeno);
		object::FnDestroy(mCard_Picked_CherryBomb);

		object::FnDestroy(mCard_Picked_SunFlower_Disalbed);
		object::FnDestroy(mCard_Picked_PeaShooter_Disalbed);
		object::FnDestroy(mCard_Picked_WallNut_Disalbed);
		object::FnDestroy(mCard_Picked_Chomper_Disalbed);
		object::FnDestroy(mCard_Picked_Jalapeno_Disalbed);
		object::FnDestroy(mCard_Picked_CherryBomb_Disalbed);

		//==================================================================
		// 0. Choose Plants
		//==================================================================
		object::FnDestroy(mUI_SeedChooserBG);
		object::FnDestroy(mUI_btn_Play);
		object::FnDestroy(mUI_btn_Play_Disabled);
		object::FnDestroy(mUI_btn_ResetChoose);

		object::FnDestroy(mCard_SunFlower);
		object::FnDestroy(mCard_PeaShooter);
		object::FnDestroy(mCard_WallNut);
		object::FnDestroy(mCard_Chomper);
		object::FnDestroy(mCard_Jalapeno);
		object::FnDestroy(mCard_CherryBomb);

		object::FnDestroy(mCard_EmptySpace1);
		object::FnDestroy(mCard_EmptySpace2);
		object::FnDestroy(mCard_EmptySpace3);
		object::FnDestroy(mCard_EmptySpace4);
		object::FnDestroy(mCard_EmptySpace5);

		//==================================================================
		// 1. Play
		//==================================================================
		//-------------------------------------
		// UI
		//-------------------------------------
		object::FnDestroy(mUI_SunPointChk);
		object::FnDestroy(mUI_ShovelBG);
		object::FnDestroy(mUI_Shovel);

		object::FnDestroy(mUI_FlagMeterEmpty);
		object::FnDestroy(mUI_FlagMeterParts_Zombie);
		object::FnDestroy(mUI_FlagMeterParts_Flag);
		object::FnDestroy(mUI_FlagMeterParts_FlagFin);

		object::FnDestroy(mUI_btn_Menu);

		object::FnDestroy(mUI_SelectedCard);

		//-------------------------------------
		// Plants
		//-------------------------------------
		mPlants_SunFlowers.clear();

		object::FnDestroy(mPl_SunFlower);
		object::FnDestroy(mPl_Peashooter1);
		object::FnDestroy(mPl_Chomper);
		object::FnDestroy(mPl_WallNut);

		object::FnDestroy(mZb_NormalZombie);
	}//END-void CScenePlayGrassDay::FnOnExit

	bool CScenePlayGrassDay::FnMoveCamera(eDirection _dir)
	{
		bool returnValue = false;

		CTransform* tr = mCamera_Main->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		if (_dir == eDirection::Right)
		{// 화면 이동 ( -->> )
			while (pos.x <= 3.f)
			{
				mChkSecondTmp += CTime::FnDeltaTime();
				if (mChkSecondTmp > 1.0f)
				{
					pos.x += 2.0f * CTime::FnDeltaTime();
					tr->FnSetPosition(pos);
					break;
				}
			}

			if (pos.x > 3.f)
				returnValue = true;
		}
		else if (_dir == eDirection::Left)
		{// 화면 이동 ( <<-- )
			while (pos.x >= 0.f)
			{
				mChkSecondTmp += CTime::FnDeltaTime();
				if (mChkSecondTmp > 1.0f)
				{
					pos.x -= 2.0f * CTime::FnDeltaTime();
					tr->FnSetPosition(pos);
					break;
				}
			}

			if (pos.x < 0.f)
				returnValue = true;
		}

		return returnValue;
	}//END-bool CScenePlayGrassDay::FnMoveCamera

	void CScenePlayGrassDay::FnChoosePlants()
	{
		//==================================================================
		// 셋팅
		//==================================================================
		//-------------------------------------
		// UI - 전체 카드 목록
		//-------------------------------------
		/* <form>
			SunFlower	PeaShooter	WallNut
			Chomper		Jalapeno	CherryBomb
		*/
		// 전체 카드 목록 창 배경 셋팅
		mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, 0.2f, 0.010f));

		// 전체 카드 목록 배치
		FnDrawWholeCardList();
		
		//-------------------------------------
		// UI - 선택한 카드 목록
		//-------------------------------------
		/* <form>
			1st Selected
			2nd Selected
			3rd Selected
			4th Selected
			5th Selected
		*/
		// 선택카드목록 창 배경 셋팅
		mCard_EmptySpace1->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_1, POS_Z_DEFAULT));
		mCard_EmptySpace2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_2, POS_Z_DEFAULT));
		mCard_EmptySpace3->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_3, POS_Z_DEFAULT));
		mCard_EmptySpace4->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_4, POS_Z_DEFAULT));
		mCard_EmptySpace5->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_5, POS_Z_DEFAULT));

		//-------------------------------------
		// UI - 버튼
		//-------------------------------------
		// Play버튼 - 활성화 조건 확인 후 배치
		if (mCntPickedCard == MAXPICKED)
		{
			mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, POS_Z_DEFAULT));
			mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, POS_Z_DEFAULT));
		}
		else
		{
			mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, POS_Z_DEFAULT));
			mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, POS_Z_DEFAULT));
		}

		// Reset버튼 - 선택목록 초기화 버튼 배치
		mUI_btn_ResetChoose->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -1.5f, POS_Z_DEFAULT));

		//==================================================================
		// 버튼 클릭시
		//==================================================================
		//-------------------------------------
		// Play버튼
		//-------------------------------------
		FnClickEvent_BtnPlay();

		//-------------------------------------
		// Reset버튼
		//-------------------------------------
		FnClickEvent_BtnResetChoose();

		//==================================================================
		// 전체 카드 목록에서 Card 선택시
		//==================================================================
		FnClickEvent_CardFrom_WholeCardList();

		//==================================================================
		// 선택한 카드 목록에서 Card 선택시
		//==================================================================
		FnClickEvent_CardFrom_PickedCardList();

	}//END-void CScenePlayGrassDay::FnChoosePlants

	void CScenePlayGrassDay::FnPlay()
	{
		//==================================================================
		// 셋팅
		//==================================================================
		//-------------------------------------
		// Cards
		//-------------------------------------
		FnDrawPickedCardList(eStepMode::Play);

		//-------------------------------------
		// UI
		//-------------------------------------
		mUI_SunPointChk->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.7f, 2.f, POS_Z_DEFAULT));
		mUI_ShovelBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, POS_Z_DEFAULT));
		mUI_Shovel->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, POS_Z_FRONT_1));
		mUI_btn_Menu->FnGetComponent<CTransform>()->FnSetPosition(Vector3(3.3f, 1.98f, POS_Z_DEFAULT));
		mUI_FlagMeterEmpty->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, POS_Z_DEFAULT));
		mUI_FlagMeterParts_Zombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.45f, 2.05f, POS_Z_FRONT_2));
		mUI_FlagMeterParts_Flag->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.38f, 2.05f, POS_Z_FRONT_1));
		mUI_FlagMeterParts_FlagFin->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.33f, 2.05f, POS_Z_FRONT_1));

		//==================================================================
		// Card 선택시
		//==================================================================
		FnClickEvent_Card();

		//==================================================================
		// 뽑기삽을 선택시
		//==================================================================
		FnClickEvent_Shovel();

		//==================================================================
		// 게임보드(잔디밭) 선택시
		//==================================================================
		FnClickEvent_Board();

		//==================================================================
		// 생성 - 햇빛 (해바라기 10초)
		//==================================================================
		for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
		{
			mPlantingTimeList_SunFlowers[idx] += (float)CTime::FnDeltaTime();
		}
		
		FnCalculateSunLightPoints_SunFlowers();

		//==================================================================
		// Plants
		//==================================================================
#pragma region Resource_Plants
		//-------------------------------------
		// SunFlower Status
		//-------------------------------------
		//mPl_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.1f, 0.5f, 0.3f));
		//mPlants_SunFlowers[0]->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.1f, 0.5f, 0.3f));

		//-------------------------------------
		// Peashooter Status
		//-------------------------------------
		mPl_Peashooter1->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.1f, -0.2f, 0.3f));

		if (eColliderStateType::Start == cd_Peashooter1->FnGetColliderState())
			if (eColliderStateType::Ing == cd_Peashooter1->FnGetColliderState())
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
		else if (eColliderStateType::Fin == cd_Chomper->FnGetColliderState() && false == FlagChomperOnceIdleDid)
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
		{
			at_WallNut->FnPlayAnimation(L"Cracked1", true);
			mChkSecondTmp = 0.f;
		}

		mChkSecondTmp += (float)CTime::FnDeltaTime();

		if ((10.0f <= mChkSecondTmp)
			&& (eColliderStateType::Ing == cd_WallNut->FnGetColliderState()))
		{
			at_WallNut->FnPlayAnimation(L"Cracked2", true);
			FlagWallNut = true;
			mChkSecondTmp = 0.f;
		}

		if ((2.0f <= mChkSecondTmp)
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

	}//END-void CScenePlayGrassDay::FnPlay

	void CScenePlayGrassDay::FnMakePickedCardList()
	{
		// mPickedList 목록 채우기
		for (int idx = 0; idx < MAXPICKED; idx++)
		{
			if (ePlantsType::End == mPickedList[idx])
			{
				mPickedList[idx] = mPickedCardType;
				++mCntPickedCard;
				break;
			}
		}

		// Player로 사용할 목록 그리기
		FnDrawPickedCardList(eStepMode::Choose);
	}//END-void CScenePlayGrassDay::FnMakePickedCardList

	bool CScenePlayGrassDay::FnChkPickedBefore(int _idx)
	{
		bool returnValue = false;

		for (size_t idx = 0; idx < MAXPICKED; idx++)
		{
			if ((ePlantsType)_idx == mPickedList[idx])
			{
				returnValue = true;
				break;
			}
		}

		return returnValue;
	}//END-bool CScenePlayGrassDay::FnChkPickedBefore

	void CScenePlayGrassDay::FnDrawWholeCardList()
	{
		for (int chkidx = 0; chkidx < MAXCARDS; chkidx++)
		{
			/*
				선택된 카드 목록 값과 비교하여,
				현재 idx에 해당하는 카드가 선택된 카드인지 확인
			*/
			bool FlagChkPickedBefore = FnChkPickedBefore(chkidx);

			if (FlagChkPickedBefore)
			{// 선택된 카드의 경우 - Disalbed로 표시
				switch (chkidx)
				{
				case (int)ePlantsType::SunFlower:
					mCard_Picked_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_2));
					mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::PeaShooter:
					mCard_Picked_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_2));
					mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::WallNut:
					mCard_Picked_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_2));
					mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Chomper:
					mCard_Picked_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_2));
					mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Jalapeno:
					mCard_Picked_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_2));
					mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::CherryBomb:
					mCard_Picked_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_2));
					mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_1));
					break;
				default:
					break;
				}
			}
			else
			{// 선택되지 않은 카드의 경우 - Disalbed가 아닌 카드로 표시
				switch (chkidx)
				{
				case (int)ePlantsType::SunFlower:
					mCard_Picked_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_1));
					mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::PeaShooter:
					mCard_Picked_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_1));
					mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::WallNut:
					mCard_Picked_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_1));
					mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::Chomper:
					mCard_Picked_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_1));
					mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::Jalapeno:
					mCard_Picked_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_1));
					mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::CherryBomb:
					mCard_Picked_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_1));
					mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_2));
					break;
				default:
					break;
				}
			}
		}//end-for (int Chkidx = 0; Chkidx < MAXCARDS; Chkidx++)
	}//END-void CScenePlayGrassDay::FnDrawWholeCardList
	
	void CScenePlayGrassDay::FnDrawPickedCardList(eStepMode _step)
	{
		CGameObject* card_Picked_Tmp = nullptr;

		//==================================================================
		// 초기화 - 기존 Card목록
		//==================================================================
		mCard_Picked_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

		//==================================================================
		// mPickedList를 통해, Player로 사용할 Card목록 그리기
		//==================================================================
		/*
			- 카드 선택 모드의 경우
			햇빛포인트와 상관없이
			선택된 카드를
			무조건 활성화상태로
			목록 그리기
			
			- 플레이 모드의 경우
			햇빛 포인트와 연동하여
			선택된 카드를
			활성화상태 또는 비활성화 상태로
			목록 그리기
		*/
		for (int idx = 0; idx < MAXPICKED; idx++)
		{
			// 해당 인덱스에 값이 없으면 그리기 패스
			if (ePlantsType::End == mPickedList[idx])
				continue;

			// 선택된 카드 타입으로 card_Picked_Tmp 설정
			switch (mPickedList[idx])
			{
			case ePlantsType::SunFlower:
				if ((eStepMode::Play == _step && 50 <= mSunScore)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_SunFlower;
					mPickedCardIsDisabledList[idx] = false;
				}
				else
				{
					card_Picked_Tmp = mCard_Picked_SunFlower_Disalbed;
					mPickedCardIsDisabledList[idx] = true;
				}
				break;
			case ePlantsType::PeaShooter:
				if ((eStepMode::Play == _step && 100 <= mSunScore)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_PeaShooter;
					mPickedCardIsDisabledList[idx] = false;
				}
				else
				{
					card_Picked_Tmp = mCard_Picked_PeaShooter_Disalbed;
					mPickedCardIsDisabledList[idx] = true;
				}
				break;
			case ePlantsType::WallNut:
				if ((eStepMode::Play == _step && 50 <= mSunScore)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_WallNut;
					mPickedCardIsDisabledList[idx] = false;
				}
				else
				{
					card_Picked_Tmp = mCard_Picked_WallNut_Disalbed;
					mPickedCardIsDisabledList[idx] = true;
				}
				break;
			case ePlantsType::Chomper:
				if ((eStepMode::Play == _step && 150 <= mSunScore)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_Chomper;
					mPickedCardIsDisabledList[idx] = false;
				}
				else
				{
					card_Picked_Tmp = mCard_Picked_Chomper_Disalbed;
					mPickedCardIsDisabledList[idx] = true;
				}
				break;
			case ePlantsType::Jalapeno:
				if ((eStepMode::Play == _step && 125 <= mSunScore)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_Jalapeno;
					mPickedCardIsDisabledList[idx] = false;
				}
				else
				{
					card_Picked_Tmp = mCard_Picked_Jalapeno_Disalbed;
					mPickedCardIsDisabledList[idx] = true;
				}
				break;
			case ePlantsType::CherryBomb:
				if ((eStepMode::Play == _step && 150 <= mSunScore)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_CherryBomb;
					mPickedCardIsDisabledList[idx] = false;
				}
				else
				{
					card_Picked_Tmp = mCard_Picked_CherryBomb_Disalbed;
					mPickedCardIsDisabledList[idx] = true;
				}
				break;
			}

			// 선택된 카드목록 그리기
			switch (idx)
			{
			case 0:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_1, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 1:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_2, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 2:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_3, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 3:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_4, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			case 4:
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_5, POS_Z_FRONT_1));
				card_Picked_Tmp->FnGetComponent<CTransform>()->FnSetScale(SCALE_CARD_DEFAULT);
				break;
			default:
				break;
			}
		}//end-for (int idx = 0; idx < MAXPICKED; idx++)
		
		card_Picked_Tmp = nullptr;
	}//END-void CScenePlayGrassDay::FnDrawPickedCardList

	void CScenePlayGrassDay::FnClickEvent_BtnResetChoose()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			if ((75.f <= MousePos.x) && (123.f >= MousePos.x)
				&& (728.f <= MousePos.y) && (773.f >= MousePos.y))
			{
				// 초기화 - 선택된 카드 목록
				for (size_t idx = 0; idx < MAXPICKED; idx++)
					mPickedList[idx] = ePlantsType::End;

				// 초기화 - 선택된 카드 Disalbed 여부 목록
				for (size_t idx = 0; idx < MAXPICKED; idx++)
					mPickedCardIsDisabledList[idx] = false;

				// 초기화 - 선택된 카드
				mCard_Picked_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				// 초기화 - 선택된 카드 총 개수
				mCntPickedCard = 0;
			}
		}
	}//END-void CScenePlayGrassDay::FnClickEvent_BtnResetChoose

	void CScenePlayGrassDay::FnClickEvent_BtnPlay()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			if ((520.f <= MousePos.x) && (675.f >= MousePos.x)
				&& (819.f <= MousePos.y) && (880.f >= MousePos.y)
				&& mCntPickedCard == MAXPICKED)
			{// Play 모드 진입 조건 충족시
				mFlagPlay = true;

				mPickedCardType = ePlantsType::End;
				mCntPickedCard = 0;

				//==================================================================
				// UI 초기화
				//==================================================================
				//-------------------------------------
				// UI
				//-------------------------------------
				mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mUI_btn_ResetChoose->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mUI_btn_Play->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mUI_btn_ResetChoose->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				//-------------------------------------
				// UI - 전체 카드 목록
				//-------------------------------------
				mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				mCard_SunFlower->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_WallNut->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Chomper->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mCard_Picked_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				mCard_Picked_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				//-------------------------------------
				// UI - 선택한 카드 목록
				//-------------------------------------
				mCard_Picked_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				mCard_Picked_SunFlower->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_PeaShooter->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_WallNut->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_Chomper->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_Jalapeno->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_Picked_CherryBomb->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);

				mCard_EmptySpace1->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_EmptySpace2->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_EmptySpace3->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_EmptySpace4->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_EmptySpace5->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				mCard_EmptySpace1->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_EmptySpace2->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_EmptySpace3->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_EmptySpace4->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
				mCard_EmptySpace5->FnGetComponent<CTransform>()->FnSetScale(SCALE_CLEAR);
			}
			else if ((MousePos.x >= 520.f) && (MousePos.x <= 675.f)
				&& (MousePos.y >= 819.f) && (MousePos.y <= 880.f)
				&& mCntPickedCard != MAXPICKED)
			{// Play 모드 진입 조건 미충족시
				TCHAR Temp[256] = { 0, };
				MessageBox(Tmp_mHwnd, L"사용가능한 플레이어 선택이 완료되지 않았습니다!", L"Warning", MB_OK);
			}
		}
	}//END-void CScenePlayGrassDay::FnClickEvent_BtnPlay

	void CScenePlayGrassDay::FnClickEvent_CardFrom_WholeCardList()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			bool FlagMakeList = false;

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			// Card_SunFlower
			if ((320.f <= MousePos.x) && (480.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::SunFlower;
				FlagMakeList = true;
			}

			// Card_PeaShooter
			if ((520.f <= MousePos.x) && (680.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::PeaShooter;
				FlagMakeList = true;
			}

			// Card_WallNut
			if ((720.f <= MousePos.x) && (880.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::WallNut;
				FlagMakeList = true;
			}

			// Card_Chomper
			if ((320.f <= MousePos.x) && (480.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::Chomper;
				FlagMakeList = true;
			}

			// Card_Jalapeno
			if ((520.f <= MousePos.x) && (680.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::Jalapeno;
				FlagMakeList = true;
			}

			// Card_CherryBomb
			if ((720.f <= MousePos.x) && (880.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::CherryBomb;
				FlagMakeList = true;
			}

			//==================================================================
			// 전체 카드 목록에서 Card 선택시, 선택된 카드 목록에 Card 추가
			//==================================================================
			/*
				선택한 카드가
				선택카드목록에 존재하는지 확인 후,

				존재하지 않으면
				선택카드목록에 추가

				존재하면
				아무작업도 하지 않음
			*/
			if (FlagMakeList)
			{
				bool FlagChkPickedBefore = FnChkPickedBefore((int)mPickedCardType);

				if (!FlagChkPickedBefore)
					FnMakePickedCardList();
			}
		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CScenePlayGrassDay::FnClickEvent_CardFrom_WholeCardList

	void CScenePlayGrassDay::FnClickEvent_CardFrom_PickedCardList()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			bool flagDoDelete = false;
			int deleteIdx = 0;

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			// 1st Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (180.f <= MousePos.y) && (275.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 0;
			}

			// 2nd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (290.f <= MousePos.y) && (385.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 1;
			}

			// 3rd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (400.f <= MousePos.y) && (495.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 2;
			}

			// 4th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (510.f <= MousePos.y) && (605.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 3;
			}

			// 5th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (620.f <= MousePos.y) && (715.f >= MousePos.y))
			{
				flagDoDelete = true;
				deleteIdx = 4;
			}

			//==================================================================
			// 선택 해제 - 선택된 카드 목록에서 Card 선택시
			//==================================================================
			if (flagDoDelete)
			{
				mPickedCardType = mPickedList[deleteIdx];
				mPickedList[deleteIdx] = ePlantsType::End;
				FnDrawPickedCardList(eStepMode::Choose);
				--mCntPickedCard;
			}
		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CScenePlayGrassDay::FnClickEvent_CardFrom_PickedCardList

	void CScenePlayGrassDay::FnClickEvent_Card()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			int idx = 0;
			bool flagDoSelected = false;
			bool flagChkRelease_CardSelected = false;

			//==================================================================
			// 유효범위 선택시
			//==================================================================
			// 1st Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (180.f <= MousePos.y) && (275.f >= MousePos.y))
			{
				idx = 0;
				flagDoSelected = true;
			}

			// 2nd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (290.f <= MousePos.y) && (385.f >= MousePos.y))
			{
				idx = 1;
				flagDoSelected = true;
			}

			// 3rd Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (400.f <= MousePos.y) && (495.f >= MousePos.y))
			{
				idx = 2;
				flagDoSelected = true;
			}

			// 4th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (510.f <= MousePos.y) && (605.f >= MousePos.y))
			{
				idx = 3;
				flagDoSelected = true;
			}

			// 5th Selected Card
			if ((10.f <= MousePos.x) && (185.f >= MousePos.x)
				&& (620.f <= MousePos.y) && (715.f >= MousePos.y))
			{
				idx = 4;
				flagDoSelected = true;
			}

			if (flagDoSelected)
			{
				if ((true == mflagIsCardSelected)
					&& (mPickedList[idx] == mPickedCardType))
				{//  선택 해제 - 카드 선택상태에서 동일 카드 재선택시
					flagChkRelease_CardSelected = true;
				}
				else if (false == mPickedCardIsDisabledList[idx])
				{// 선택 활성화 - 카드가 비활성이 아닌 상태
					mPickedCardType = mPickedList[idx];
					mflagIsCardSelected = true;

					// 선택한 idx별로 POSITION 선정
					switch (idx)
					{
					case 0:
						mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_1, 0.003f));
						break;
					case 1:
						mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_2, 0.003f));
						break;
					case 2:
						mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_3, 0.003f));
						break;
					case 3:
						mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_4, 0.003f));
						break;
					case 4:
						mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_5, 0.003f));
						break;
					default:
						break;
					}
				}
			}

			//==================================================================
			// 선택 해제 (Exception) - 카드가 선택된 상태에서
			//==================================================================
			/*
				&&
				- 카드목록 범위를 벗어났을 때
				- 게임보드(잔디밭) 진입여부 확인하여 그에 못미친 영역일 때
				- 카드가 선택된 상태일 때
				
				||
				- 카드가 선택된 상태에서 동일한 카드를 재클릭시
			*/
			if (!((10.f <= MousePos.x) && (185.f >= MousePos.x) && (180.f <= MousePos.y) && (715.f >= MousePos.y)) 
				&& (400.f >= MousePos.x)
				&& (true == mflagIsCardSelected)
				|| (true == flagChkRelease_CardSelected))
			{
				mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mPickedCardType = ePlantsType::End;
				mflagIsCardSelected = false;
			}

			//==================================================================
			// 정상처리 - 카드가 선택된 상태에서 식물 심기
			//==================================================================
			/*
				카드가 선택된 상태
				게임보드(잔디밭) 내 유효범위를 클릭했을 때
			*/
			if (mflagIsCardSelected)
			{
				// 선택 해제 - 뽑기삽
				if (mflagIsShovelSelected)
					FnRelease_Shovel();

				FnClickEvent_Board();
			}
		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CScenePlayGrassDay::FnClickEvent_Card

	void CScenePlayGrassDay::FnClickEvent_Shovel()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			//==================================================================
			// 뽑기삽을 클릭한 경우
			//==================================================================
			if ((610.f <= MousePos.x) && (690.f >= MousePos.x)
				&& (10.f <= MousePos.y) && (90.f >= MousePos.y))
			{
				// 선택 해제 - 카드
				if (mflagIsCardSelected)
					FnRelease_Card();

				if (!mflagIsShovelSelected)
				{// 뽑기삽이 비활성화였던 경우 - 활성화로 변경
					mflagIsShovelSelected = true;
					mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, 0.003f));
				}
				else
				{// 뽑기삽 활성화였던 경우 - 비활성화로 변경 (뽑기삽이 이미 선택된 상태에서 다시 뽑기삽이 클릭된 상태)
					mflagIsShovelSelected = false;
					mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				}
			}

			//==================================================================
			// 정상처리 - 뽑기삽이 선택된 상태에서 식물 뽑기
			//==================================================================
			/*
				뽑기삽이 선택된 상태
				게임보드(잔디밭) 내 유효범위를 클릭했을 때
			*/
			if (mflagIsShovelSelected)
				FnClickEvent_Board();
		}
	}//END-void CScenePlayGrassDay::FnClickEvent_Shovel

	void CScenePlayGrassDay::FnClickEvent_Board()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			int idx = 0;			// 클릭 위치 확인용
			bool flagDo = false;	// 클릭에 따른 처리 여부

			//==================================================================
			// 가로(horizontal row)		1번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_1
			if (BOARD_X_1 && BOARD_Y_1)
			{
				idx = 0;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_1)
			{
				idx = 1;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_1)
			{
				idx = 2;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_1)
			{
				idx = 3;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_1)
			{
				idx = 4;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_1)
			{
				idx = 5;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_1)
			{
				idx = 6;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_1)
			{
				idx = 7;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_1)
			{
				idx = 8;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		2번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_2
			if (BOARD_X_1 && BOARD_Y_2)
			{
				idx = 9;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_2)
			{
				idx = 10;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_2)
			{
				idx = 11;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_2)
			{
				idx = 12;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_2)
			{
				idx = 13;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_2)
			{
				idx = 14;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_2)
			{
				idx = 15;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_2)
			{
				idx = 16;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_2)
			{
				idx = 17;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		3번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_3
			if (BOARD_X_1 && BOARD_Y_3)
			{
				idx = 18;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_3)
			{
				idx = 19;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_3)
			{
				idx = 20;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_3)
			{
				idx = 21;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_3)
			{
				idx = 22;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_3)
			{
				idx = 23;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_3)
			{
				idx = 24;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_3)
			{
				idx = 25;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_3)
			{
				idx = 26;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		4번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_4
			if (BOARD_X_1 && BOARD_Y_4)
			{
				idx = 27;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_4)
			{
				idx = 28;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_4)
			{
				idx = 29;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_4)
			{
				idx = 30;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_4)
			{
				idx = 31;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_4)
			{
				idx = 32;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_4)
			{
				idx = 33;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_4)
			{
				idx = 34;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_4)
			{
				idx = 35;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		5번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_5
			if (BOARD_X_1 && BOARD_Y_5)
			{
				idx = 36;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_5)
			{
				idx = 37;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_5)
			{
				idx = 38;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_5)
			{
				idx = 39;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_5)
			{
				idx = 40;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_5)
			{
				idx = 41;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_5)
			{
				idx = 42;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_5)
			{
				idx = 43;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_5)
			{
				idx = 44;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 선택 위치별 처리
			// 식물 심기 또는 뽑기
			// 또는 햇빛 포인트 클릭 처리
			//==================================================================
			if (flagDo)
			{
				if (mflagIsCardSelected			// 카드	: O
					&& !mflagIsShovelSelected)	// 삽	: X
				{// 심기
					FnPutPlants(idx);
				}

				if (mflagIsShovelSelected		// 삽	: O
					&& !mflagIsCardSelected)	// 카드	: X
				{// 뽑기
					FnRemovePlants(idx);
				}

				if (true == mIdxList_SunLights[mBoard[idx].IdxPlants])
				{
					HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
					TCHAR Temp[256] = { 0, };
					_stprintf_s(Temp, L"mSunScore: % d -> %d", mSunScore, mSunScore+25);
					MessageBox(Tmp_mHwnd, Temp, L"짠", MB_OK);

					// 그림 없애기 - 해당 좌표의 햇빛 포인트
					mSunLights[mBoard[idx].IdxPlants]->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

					// 초기화 - 기준시간
					mPlantingTimeList_SunFlowers[mBoard[idx].IdxPlants] = 0.f;

					// 갱신 - 햇빛 포인트 생성 여부 인덱스 목록의 인덱스 값
					mIdxList_SunLights[mBoard[idx].IdxPlants] = false;

					// 갱신 - 햇빛 포인트 점수
					mSunScore += 25;
				}
			}

		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CScenePlayGrassDay::FnClickEvent_Board

	void CScenePlayGrassDay::FnPutPlants(int _posIdx)
	{
		bool chkIsPlantsNow = mBoard[_posIdx].flagIsPlants;

		if (!chkIsPlantsNow)
		{// 해당 칸에 식물이 없는 상태

			// 심어질 식물의 현재 idx 확인용
			int idxPlants = 0;

			// 심어질 위치
			Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
			posNumbSet = numbSetList[_posIdx];

			switch (mPickedCardType)
			{
			case ePlantsType::SunFlower:
			{
				if (50 <= mSunScore)
				{
					// 찾기 - 적합한 idx
					idxPlants = FnFind_AvailableIdx();

					// 식물 심기
					mPlants_SunFlowers[idxPlants]->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);

					// 갱신 - 식물 배열 인덱스 목록의 인덱스 값 (특정)
					mIdxList_SunFlowers[idxPlants] = true;

					// 갱신 - 해당 좌표의 게임판 상태 기록
					mBoard[_posIdx].plantsType = ePlantsType::SunFlower;

					// 갱신 - 햇빛 포인트 점수
					mSunScore -= 50;

					//-------------------------------------
					// Only 해바라기
					//-------------------------------------
					// 갱신 - 심은 시간 정보 저장
					mPlantingTimeList_SunFlowers[idxPlants] = 0.f;
				}
			}
			break;
			case ePlantsType::PeaShooter:
				break;
			case ePlantsType::WallNut:
				break;
			case ePlantsType::Chomper:
				break;
			case ePlantsType::Jalapeno:
				break;
			case ePlantsType::CherryBomb:
				break;
			default:
				break;
			}

			// 갱신 - 해당 좌표의 게임판 상태 기록 (공통)
			mBoard[_posIdx].flagIsPlants = true;
			mBoard[_posIdx].IdxPlants = idxPlants;

			/*
				선택된 식물을 선택한 위치에 심고 나서
				선택 해제 - 카드
			*/
			if (mflagIsCardSelected)
				FnRelease_Card();
		}//end-if (!chkIsPlantsNow)
		else
		{// 해당 칸에 식물이 있는 상태

			TCHAR Temp[256] = { 0, };
			MessageBox(MyApplication.FnGetHwnd(), L"이미 심은 식물이 있습니다.\n심은 식물이 없는 다른 곳을 선택하세요", L"Warning", MB_OK);
		}
	}//END-void CScenePlayGrassDay::FnPutPlants

	void CScenePlayGrassDay::FnRemovePlants(int _posIdx)
	{
		bool chkIsPlantsNow = mBoard[_posIdx].flagIsPlants;

		if (chkIsPlantsNow)
		{// 해당 칸에 식물이 있는 상태

			// 뽑힐 식물의 idx 확인용
			int idxPlants = 0;

			mPickedCardType = mBoard[_posIdx].plantsType;

			switch (mPickedCardType)
			{
			case ePlantsType::SunFlower:
			{
				idxPlants = mBoard[_posIdx].IdxPlants;

				// 식물 뽑기
				mPlants_SunFlowers[idxPlants]->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				// 갱신 - 해당 좌표의 게임판 상태 기록
				mBoard[_posIdx].flagIsPlants = false;
				mBoard[_posIdx].plantsType = ePlantsType::End;
				mBoard[_posIdx].IdxPlants = 0;

				// 갱신 - 인덱스 목록의 인덱스 값
				mIdxList_SunFlowers[idxPlants] = false;
			}
			break;
			case ePlantsType::PeaShooter:
				break;
			case ePlantsType::WallNut:
				break;
			case ePlantsType::Chomper:
				break;
			case ePlantsType::Jalapeno:
				break;
			case ePlantsType::CherryBomb:
				break;
			default:
				break;
			}

			// 선택 해제 - 뽑기삽
			if (mflagIsShovelSelected)
				FnRelease_Shovel();
		}//end-if (!chkIsPlantsNow)
		else
		{// 해당 칸에 식물이 없는 상태
			TCHAR Temp[256] = { 0, };
			MessageBox(MyApplication.FnGetHwnd(), L"이 곳에는 식물이 없습니다.\n심은 식물이 있는 다른 곳을 선택하세요", L"Warning", MB_OK);
		}
	}//END-void CScenePlayGrassDay::FnRemovePlants

	void CScenePlayGrassDay::FnRelease_Shovel()
	{
		mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mflagIsShovelSelected = false;
	}//END-void CScenePlayGrassDay::FnRelease_Shovel

	void CScenePlayGrassDay::FnRelease_Card()
	{
		mUI_SelectedCard->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mPickedCardType = ePlantsType::End;
		mflagIsCardSelected = false;
	}//END-void CScenePlayGrassDay::FnRelease_Card

	int CScenePlayGrassDay::FnFind_AvailableIdx()
	{
		int returnValue = 0;
		bool mIdxList_Tmp[MAXCOUNT_PLANTS] = {};

		// 셋팅 - 선택된 카드 별 식물 정보 목록
		switch (mPickedCardType)
		{
		case ePlantsType::SunFlower:
			std::memcpy(&mIdxList_Tmp, &mIdxList_SunFlowers, sizeof(mIdxList_SunFlowers));
		break;
		case ePlantsType::PeaShooter:
			break;
		case ePlantsType::WallNut:
			break;
		case ePlantsType::Chomper:
			break;
		case ePlantsType::Jalapeno:
			break;
		case ePlantsType::CherryBomb:
			break;
		default:
			break;
		}

		// 찾기 - 게임판에 셋팅되지 않은, 올림차순상 가장 낮은 idx값
		for (int chkIdx = 0; chkIdx < MAXCOUNT_PLANTS; chkIdx++)
		{
			if (false == mIdxList_Tmp[chkIdx])
			{
				returnValue = chkIdx;
				break;
			}
		}

		// 반환
		return returnValue;
	}//END-int CScenePlayGrassDay::FnFind_AvailableIdx

	void CScenePlayGrassDay::FnCalculateSunLightPoints_SunFlowers()
	{
		for (int chkIdx = 0; chkIdx < MAXCOUNT_PLANTS; chkIdx++)
		{
			if (true == mIdxList_SunFlowers[chkIdx])
			{// 해바라기가 심어진 곳이면

				if (10.f <= mPlantingTimeList_SunFlowers[chkIdx])
				{// 기준시간이 10초 이상이 되었다면

					//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
					//TCHAR Temp[256] = { 0, };
					//_stprintf_s(Temp, L"chkIdx: % d", chkIdx);
					//MessageBox(Tmp_mHwnd, Temp, L"짠", MB_OK);

					Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);

					for (int chkIdx2 = 0; chkIdx2 < MAXCOUNT_PLANTS; chkIdx2++)
					{
						if (chkIdx == mBoard[chkIdx2].IdxPlants)
						{// 해바라기가 심어진 보드판 내 좌표 찾기

							// 좌표 셋팅
							posNumbSet = numbSetList[chkIdx2];
							posNumbSet.y -= 0.1f;
							posNumbSet.z = POS_Z_FRONT_1;

							if (false == mIdxList_SunLights[chkIdx])
							{// 기존에 생성된 햇빛 포인트가 없는 경우 - 같은 위치에 햇빛 포인트 중복 생성 방지

								// 해당 좌표에 햇빛 포인트 활성화
								mSunLights[chkIdx]->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);

								// 갱신 - 햇빛 포인트 생성 여부 인덱스 목록의 인덱스 값
								mIdxList_SunLights[chkIdx] = true;
								break;
							}
						}
					}

					// 초기화 - 기준시간
					mPlantingTimeList_SunFlowers[chkIdx] = 0.f;
				}
			}
		}
	}//END-void CScenePlayGrassDay::FnCalculateSunLightPoints_SunFlowers
}
