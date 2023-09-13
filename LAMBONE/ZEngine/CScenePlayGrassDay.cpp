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
		CCollisionManager::FnSetLayer(eLayerType::Player, eLayerType::Monster, true);

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
		cameraComp->FnTurnLayerMask(eLayerType::Player, false);
		cameraComp->FnTurnLayerMask(eLayerType::Monster, false);
		cameraComp->FnTurnLayerMask(eLayerType::SunLight, false);
		cameraComp->FnTurnLayerMask(eLayerType::SunLightNatural, false);
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
		// Initialize - All GameObject
		//==================================================================
		//CSunLightScore* sunLightScore = object::FnInstantiate<CSunLightScore>(eLayerType::UI);
		//sunLightScore->FnInitialize();

		FnInitialize_UI();
		FnInitialize_Cards();
		FnInitialize_Plants();
		FnInitialize_Zombies();
	}//END-void CScenePlayGrassDay::FnDoInitialize

	void CScenePlayGrassDay::FnInitialize_UI()
	{
		//==================================================================
		// Choose Plants
		//==================================================================
#pragma region Resource_UI_Choose Plants
		// UI_SeedChooserBG
		mUI_SeedChooserBG = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		CMeshRenderer* mr = mUI_SeedChooserBG->FnAddComponent<CMeshRenderer>();
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
#pragma endregion

		//==================================================================
		// Play
		//==================================================================
#pragma region Resource_UI_Play
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
	}//END-void CScenePlayGrassDay::FnInitialize_UI

	void CScenePlayGrassDay::FnInitialize_Cards()
	{
		//==================================================================
		// Card_EmptySpace
		//==================================================================
#pragma region Resource_Card_EmptySpace
		mCard_EmptySpace1 = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::UI);
		CMeshRenderer* mr = mCard_EmptySpace1->FnAddComponent<CMeshRenderer>();
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
#pragma endregion

		//==================================================================
		// Card_Plants
		//==================================================================
#pragma region Resource_Card_Plants
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
#pragma endregion

		//==================================================================
		// Card_Picked
		//==================================================================
#pragma region Resource_Card_Picked
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
#pragma endregion

		//==================================================================
		// Card_Picked_Disalbed
		//==================================================================
#pragma region Resource_Card_Picked_Disalbed
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
	}//END-void CScenePlayGrassDay::FnInitialize_Cards

	void CScenePlayGrassDay::FnInitialize_Plants()
	{
		//==================================================================
		// SunLight
		//==================================================================
		//mSunLights.resize(MAX_PLANTS);

		//-------------------------------------
		// made by Sunflower
		//-------------------------------------
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			mSunLights[idx].sunLight = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::SunLight);
			
			CMeshRenderer* mr = mSunLights[idx].sunLight->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			std::shared_ptr<CTexture> atlas_SunLight
				= CResources::FnLoad<CTexture>(L"SunLight", L"..\\Resources\\Texture\\MyGame\\Plants\\SunLight.png");
			CAnimator* at_SunLight = mSunLights[idx].sunLight->FnAddComponent<CAnimator>();
			at_SunLight->FnCreate(
				L"Idle"						// name
				, atlas_SunLight			// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(2574.f / 22.f, 117.f)	// size
				, 22						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);
			at_SunLight->FnPlayAnimation(L"Idle", true);
		}

		//-------------------------------------
		// made by Natural
		//-------------------------------------
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
		{
			mSunLights_Natural[idx].sunLight = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::SunLightNatural);

			CMeshRenderer* mr = mSunLights_Natural[idx].sunLight->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			std::shared_ptr<CTexture> atlas_SunLight
				= CResources::FnLoad<CTexture>(L"SunLight", L"..\\Resources\\Texture\\MyGame\\Plants\\SunLight.png");
			CAnimator* at_SunLight = mSunLights_Natural[idx].sunLight->FnAddComponent<CAnimator>();
			at_SunLight->FnCreate(
				L"Idle"						// name
				, atlas_SunLight			// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(2574.f / 22.f, 117.f)	// size
				, 22						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);
			at_SunLight->FnPlayAnimation(L"Idle", true);
		}

		//==================================================================
		// SunFlower
		//==================================================================
#pragma region Resource_Plants_SunFlower
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			mPlants_SunFlowers[idx].plants = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::Player);
			mPlants_SunFlowers[idx].plants->FnSetName(L"GrassDay_SunFlower_"+ idx);
			
			CMeshRenderer* mr = mPlants_SunFlowers[idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			//-------------------------------------
			// plants_animator
			//-------------------------------------
			mPlants_SunFlowers[idx].animator = mPlants_SunFlowers[idx].plants->FnAddComponent<CAnimator>();

			// Idle
			std::shared_ptr<CTexture> atlas_SunFlower_Idle
				= CResources::FnLoad<CTexture>(L"SunFlower_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\SunFlower\\SunFlower.png");
			mPlants_SunFlowers[idx].animator->FnCreate(
				L"SunFlower_Idle"			// name
				, atlas_SunFlower_Idle		// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1971.f / 18.f, 111.f)	// size
				, 18						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			// Bright
			std::shared_ptr<CTexture> atlas_SunFlower_Bright
				= CResources::FnLoad<CTexture>(L"SunFlower_Bright", L"..\\Resources\\Texture\\MyGame\\Plants\\SunFlower\\SunFlower_Bright.png");
			mPlants_SunFlowers[idx].animator->FnCreate(
				L"SunFlower_Bright"			// name
				, atlas_SunFlower_Bright	// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1980.0f / 18.f, 112.0f)	// size
				, 18						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			// Blink
			std::shared_ptr<CTexture> atlas_SunFlower_Blink
				= CResources::FnLoad<CTexture>(L"SunFlower_Blink", L"..\\Resources\\Texture\\MyGame\\Plants\\SunFlower\\SunFlower_Blink.png");
			mPlants_SunFlowers[idx].animator->FnCreate(
				L"SunFlower_Blink"			// name
				, atlas_SunFlower_Blink		// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1971.f / 18.f, 111.f)	// size
				, 18						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			//-------------------------------------
			// ���� - Status
			//-------------------------------------
			FnChangeStatus_Plants(ePlantsType::SunFlower, idx, eStatusType::End);

			//-------------------------------------
			// plants_collider
			//-------------------------------------
			//mPlants_SunFlowers[idx].collider = mPlants_SunFlowers[idx].plants->FnAddComponent<CCollider2D>();
			//mPlants_SunFlowers[idx].collider->FnSetSize(Vector2(0.3f, 0.3f));
			//mPlants_SunFlowers[idx].collider->FnSetCenter(Vector2(-0.1f, -0.05f));
		}
#pragma endregion

		//==================================================================
		// WallNut
		//==================================================================
#pragma region Resource_Plants_WallNut
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			mPlants_WallNuts[idx].plants = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::Player);
			mPlants_WallNuts[idx].plants->FnSetName(L"GrassDay_WallNut_" + idx);

			CMeshRenderer* mr = mPlants_WallNuts[idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			//-------------------------------------
			// plants_animator
			//-------------------------------------
			mPlants_WallNuts[idx].animator = mPlants_WallNuts[idx].plants->FnAddComponent<CAnimator>();

			// Idle
			std::shared_ptr<CTexture> atlas_WallNut_Idle
				= CResources::FnLoad<CTexture>(L"WallNut_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\WallNut_Idle.png");
			mPlants_WallNuts[idx].animator->FnCreate(
				L"WallNut_Idle"				// name
				, atlas_WallNut_Idle		// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1560.f / 16.f, 109.f)	// size
				, 16						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			// Cracked1
			std::shared_ptr<CTexture> atlas_WallNut_Cracked1
				= CResources::FnLoad<CTexture>(L"WallNut_Cracked1", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\WallNut_Cracked1.png");
			mPlants_WallNuts[idx].animator->FnCreate(
				L"WallNut_Cracked1"			// name
				, atlas_WallNut_Cracked1	// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1072.f / 11.f, 109.f)	// size
				, 11						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			// Cracked2
			std::shared_ptr<CTexture> atlas_WallNut_Cracked2
				= CResources::FnLoad<CTexture>(L"WallNut_Cracked2", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\WallNut_Cracked2.png");
			mPlants_WallNuts[idx].animator->FnCreate(
				L"WallNut_Cracked2"			// name
				, atlas_WallNut_Cracked2	// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1462.f / 15.f, 109.f)	// size
				, 15						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			//-------------------------------------
			// ���� - Status
			//-------------------------------------
			FnChangeStatus_Plants(ePlantsType::WallNut, idx, eStatusType::End);
		}
#pragma endregion

		//==================================================================
		// Peashooter
		//==================================================================
#pragma region Resource_Plants_Peashooter
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			mPlants_Peashooters[idx].plants = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::Player);
			mPlants_Peashooters[idx].plants->FnSetName(L"GrassDay_Peashooter_" + idx);

			CMeshRenderer* mr = mPlants_Peashooters[idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			//-------------------------------------
			// plants_animator
			//-------------------------------------
			mPlants_Peashooters[idx].animator = mPlants_Peashooters[idx].plants->FnAddComponent<CAnimator>();

			// Idle
			std::shared_ptr<CTexture> atlas_Peashooter_Idle
				= CResources::FnLoad<CTexture>(L"PeaShooter_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\Peashooter\\Peashooter.png");
			mPlants_Peashooters[idx].animator->FnCreate(
				L"PeaShooter_Idle"			// name
				, atlas_Peashooter_Idle		// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1384.f / 13.f, 106.f)	// size
				, 13						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			//-------------------------------------
			// ���� - Status
			//-------------------------------------
			FnChangeStatus_Plants(ePlantsType::PeaShooter, idx, eStatusType::End);
		}
#pragma endregion

		//==================================================================
		// Chomper
		//==================================================================
#pragma region Resource_Plants_Chomper
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			mPlants_Chompers[idx].plants = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::Player);
			mPlants_Chompers[idx].plants->FnSetName(L"GrassDay_Chomper_" + idx);

			CMeshRenderer* mr = mPlants_Chompers[idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			//-------------------------------------
			// plants_animator
			//-------------------------------------
			mPlants_Chompers[idx].animator = mPlants_Chompers[idx].plants->FnAddComponent<CAnimator>();

			// Idle
			std::shared_ptr<CTexture> atlas_Chomper_Idle
				= CResources::FnLoad<CTexture>(L"Chomper_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Idle.png");
			mPlants_Chompers[idx].animator->FnCreate(
				L"Chomper_Idle"				// name
				, atlas_Chomper_Idle		// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(2535.f / 13.f, 171.0f)// size
				, 13						// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			// Attack
			std::shared_ptr<CTexture> atlas_Chomper_Attack
				= CResources::FnLoad<CTexture>(L"Chomper_Attack", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Attack.png");
			mPlants_Chompers[idx].animator->FnCreate(
				L"Chomper_Attack"			// name
				, atlas_Chomper_Attack		// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1755.0f / 9.f, 171.0f)// size
				, 9							// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			// Digest
			std::shared_ptr<CTexture> atlas_Chomper_Digest
				= CResources::FnLoad<CTexture>(L"Chomper_Digest", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Digest.png");
			mPlants_Chompers[idx].animator->FnCreate(
				L"Chomper_Digest"			// name
				, atlas_Chomper_Digest		// atlas
				, Vector2(0.0f, 0.0f)		// leftTop
				, Vector2(1170.0f / 9.f, 171.0f)// size
				, 9							// columnLength
				, Vector2::Zero				// offset
				, 0.08f						// duration
			);

			//-------------------------------------
			// ���� - Status
			//-------------------------------------
			FnChangeStatus_Plants(ePlantsType::Chomper, idx, eStatusType::End);
		}
#pragma endregion
	}//END-void CScenePlayGrassDay::FnInitialize_Plants

	void CScenePlayGrassDay::FnInitialize_Zombies()
	{
		//==================================================================
		// NormalZombie
		//==================================================================
#pragma region Resource_Zombies_NormalZombie
		mZb_NormalZombie = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.2f), eLayerType::Monster);
		mZb_NormalZombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.0f, -1.0f, 0.2f));

		mZb_NormalZombie->FnSetName(L"GrassDay_NormalZombie");

		cd_NormalZombie = mZb_NormalZombie->FnAddComponent<CCollider2D>();
		cd_NormalZombie->FnSetSize(Vector2(0.2f, 0.53f));
		//cd_NormalZombie->FnSetCenter(Vector2(0.09f, -0.05f));

		CMeshRenderer* mr = mZb_NormalZombie->FnAddComponent<CMeshRenderer>();
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
			, Vector2(5478.f / 22.f, 216.f)	// size
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
			, Vector2(5229.f / 21.f, 216.f)	// size
			, 21						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		at_NormalZombie->FnPlayAnimation(L"Idle", true);
		mZb_NormalZombie->FnAddComponent<CPlayerScript>();
#pragma endregion
	}//END-void CScenePlayGrassDay::FnInitialize_Zombies
	
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
		if (!mFlagChkEnter && !mFlagPlayEnter)
			FnChoosePlants();

		//==================================================================
		// 2. Main Camera Move to LEFT
		// 3. Play
		//==================================================================
		if (mFlagPlayEnter && FnMoveCamera(eDirection::Left))
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

	void CScenePlayGrassDay::FnRender_Font()
	{
		//==================================================================
		// �޺� ����Ʈ ����
		//==================================================================
		if(mFlagPlay)
		{
			TCHAR Temp[10] = { 0, };
			_stprintf_s(Temp, L"%5d ", mSunLightScore);
			CFontWrapper::FnDrawFont(Temp, 405.f, 15.f, 65, FONT_RGBA(33, 33, 33, 255));
		}

		//==================================================================
		// ī�� ��Ÿ��
		//==================================================================
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			if (true == mPickedCardList[idx].isCoolTimeActive)
			{
				TCHAR Temp[5] = { 0, };
				_stprintf_s(Temp, L"%02i ", 10 - (int)mPickedCardList[idx].coolTime);

				switch (idx)
				{
				case 0:
					CFontWrapper::FnDrawFont(Temp, 50.f, 185.f, 77, FONT_RGBA(95, 0, 255, 255));
					break;
				case 1:
					CFontWrapper::FnDrawFont(Temp, 50.f, 295.f, 77, FONT_RGBA(95, 0, 255, 255));
					break;
				case 2:
					CFontWrapper::FnDrawFont(Temp, 50.f, 405.f, 77, FONT_RGBA(95, 0, 255, 255));
					break;
				case 3:
					CFontWrapper::FnDrawFont(Temp, 50.f, 515.f, 77, FONT_RGBA(95, 0, 255, 255));
					break;
				case 4:
					CFontWrapper::FnDrawFont(Temp, 50.f, 625.f, 77, FONT_RGBA(95, 0, 255, 255));
					break;
				}
			}
		}
	}//END-void CScenePlayGrassDay::FnRender_Font

	void CScenePlayGrassDay::FnOnEnter()
	{
		mSunLightScore			= 5500;
		mChkSecond_SunLight		= 0.f;
		mChkSecond_MoveCamera	= 0.f;
		mFlagChkEnter			= true;
		mFlagPlayEnter			= false;
		mFlagPlay				= false;
		mCntPickedCard			= 0;

		mflagIsCardSelected		= false;
		mflagIsShovelSelected	= false;

		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			mPickedCardList[idx].plantsType			= ePlantsType::End;
			mPickedCardList[idx].isDisabled			= false;
			mPickedCardList[idx].isCoolTimeActive	= false;
			mPickedCardList[idx].coolTime			= 0.f;
		}

		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			mBoard[idx].isPlanted					= false;
			mBoard[idx].plantsType					= ePlantsType::End;

			mSunLights[idx].isExist					= false;
			mSunLights[idx].isExistSunflower		= false;
			mSunLights[idx].cycleChkTime			= 999.f;

			if (idx < 25)
			{
				mSunLights_Natural[idx].isExist		= false;
				mSunLights_Natural[idx].isArrived	= false;
				mSunLights_Natural[idx].cycleChkTime = 0.f;
			}

			mPlants_SunFlowers[idx].isPlanted		= false;
			mPlants_SunFlowers[idx].isChangeStatus	= false;
			mPlants_SunFlowers[idx].statusType		= eStatusType::End;
			mPlants_SunFlowers[idx].isAttacked		= false;
			mPlants_SunFlowers[idx].attackedTime	= 0.f;

			mPlants_WallNuts[idx].isPlanted			= false;
			mPlants_WallNuts[idx].isChangeStatus	= false;
			mPlants_WallNuts[idx].statusType		= eStatusType::End;
			mPlants_WallNuts[idx].isAttacked		= false;
			mPlants_WallNuts[idx].attackedTime		= 0.f;

			mPlants_Peashooters[idx].isPlanted		= false;
			mPlants_Peashooters[idx].isChangeStatus	= false;
			mPlants_Peashooters[idx].statusType		= eStatusType::End;
			mPlants_Peashooters[idx].isAttacked		= false;
			mPlants_Peashooters[idx].attackedTime	= 0.f;

			mPlants_Chompers[idx].isPlanted			= false;
			mPlants_Chompers[idx].isChangeStatus	= false;
			mPlants_Chompers[idx].statusType		= eStatusType::End;
			mPlants_Chompers[idx].isAttacked		= false;
			mPlants_Chompers[idx].attackedTime		= 0.f;
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
		object::FnDestroy(mUI_SelectedShovel);

		//-------------------------------------
		// Plants
		//-------------------------------------
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			object::FnDestroy(mSunLights[idx].sunLight);
			object::FnDestroy(mPlants_SunFlowers[idx].plants);
			object::FnDestroy(mPlants_WallNuts[idx].plants);
			object::FnDestroy(mPlants_Peashooters[idx].plants);
			object::FnDestroy(mPlants_Chompers[idx].plants);
		}

		object::FnDestroy(mZb_NormalZombie);
	}//END-void CScenePlayGrassDay::FnOnExit

	bool CScenePlayGrassDay::FnMoveCamera(eDirection _dir)
	{
		bool returnValue = false;

		CTransform* tr = mCamera_Main->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		if (_dir == eDirection::Right)
		{// ȭ�� �̵� ( -->> )
			while (pos.x <= 3.f)
			{
				mChkSecond_MoveCamera += CTime::FnDeltaTime();
				if (mChkSecond_MoveCamera > 1.0f)
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
		{// ȭ�� �̵� ( <<-- )
			while (pos.x >= 0.f)
			{
				mChkSecond_MoveCamera += CTime::FnDeltaTime();
				if (mChkSecond_MoveCamera > 1.0f)
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
		// ����
		//==================================================================
		//-------------------------------------
		// UI - ��ü ī�� ���
		//-------------------------------------
		/* <form>
			[0]-SunFlower	[1]-PeaShooter	[2]-WallNut
			[3]-Chomper		[4]-Jalapeno	[5]-CherryBomb
		*/
		// ��ü ī�� ��� â ��� ����
		mUI_SeedChooserBG->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, 0.2f, 0.010f));

		// ��ü ī�� ��� ��ġ
		FnDrawWholeCardList();

		//-------------------------------------
		// UI - ������ ī�� ���
		//-------------------------------------
		/* <form>
			1st Selected
			2nd Selected
			3rd Selected
			4th Selected
			5th Selected
		*/
		// ����ī���� â ��� ����
		mCard_EmptySpace1->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_1, POS_Z_DEFAULT));
		mCard_EmptySpace2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_2, POS_Z_DEFAULT));
		mCard_EmptySpace3->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_3, POS_Z_DEFAULT));
		mCard_EmptySpace4->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_4, POS_Z_DEFAULT));
		mCard_EmptySpace5->FnGetComponent<CTransform>()->FnSetPosition(Vector3(POS_XY_PICKEDLIST_5, POS_Z_DEFAULT));

		//-------------------------------------
		// UI - ��ư
		//-------------------------------------
		// Reset��ư - ���ø�� �ʱ�ȭ ��ư ��ġ
		mUI_btn_ResetChoose->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.5f, -1.5f, POS_Z_DEFAULT));

		// Play��ư - Ȱ��ȭ ���� Ȯ�� �� ��ġ
		if (mCntPickedCard == MAX_CARDS_PICKED)
		{
			mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, POS_Z_DEFAULT));
			mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, POS_Z_DEFAULT));
		}
		else
		{
			mUI_btn_Play_Disabled->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.0f, -2.0f, POS_Z_DEFAULT));
			mUI_btn_Play->FnGetComponent<CTransform>()->FnSetPosition(Vector3(100.0f, 0.f, POS_Z_DEFAULT));
		}

		//==================================================================
		// *****���� �߿�*****
		//==================================================================
		//-------------------------------------
		// 1. Card ���ý�
		//-------------------------------------
		// ��ü ī�� ��Ͽ���
		FnClickEvent_CardFrom_WholeCardList();

		// ������ ī�� ��Ͽ���
		FnClickEvent_CardFrom_PickedCardList();

		//-------------------------------------
		// 2. Player�� ����� ��� �׸���
		//-------------------------------------
		FnDrawPickedCardList(eStepMode::Choose);

		//-------------------------------------
		// 3. ��ư Ŭ����
		//-------------------------------------
		// Reset��ư
		FnClickEvent_BtnResetChoose();

		// ��ư Ŭ���� - Play��ư
		FnClickEvent_BtnPlay();
			
	}//END-void CScenePlayGrassDay::FnChoosePlants

	void CScenePlayGrassDay::FnPlay()
	{
		mFlagPlay = true;

		//==================================================================
		// ����
		//==================================================================
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

		//-------------------------------------
		// Cards
		//-------------------------------------
		FnDrawPickedCardList(eStepMode::Play);

		//==================================================================
		// Card ���ý�
		//==================================================================
		FnClickEvent_Card();

		//==================================================================
		// �̱���� ���ý�
		//==================================================================
		FnClickEvent_Shovel();

		//==================================================================
		// ���Ӻ���(�ܵ��) ���ý�
		//==================================================================
		FnClickEvent_Board();

		//==================================================================
		// ���� - �޺�
		//==================================================================
		FnManageSunLight_Sunflower();

		mChkSecond_SunLight += CTime::FnDeltaTime();
		FnManageSunLight_Natural();

		FnDrawSunLights();

		//==================================================================
		// �׸��� - Plants
		//==================================================================
		FnDrawBoard();


		FnManageFSM_Zombies();
		FnManageCollider_Zombies();

	}//END-void CScenePlayGrassDay::FnPlay

	void CScenePlayGrassDay::FnMakePickedCardList()
	{
		// mPickedList ��� ä���
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			if (ePlantsType::End == mPickedCardList[idx].plantsType)
			{
				mPickedCardList[idx].plantsType = mPickedCardType;
				++mCntPickedCard;
				break;
			}
		}
	}//END-void CScenePlayGrassDay::FnMakePickedCardList

	bool CScenePlayGrassDay::FnChkPickedBefore(int _idx)
	{
		/* <form>
			[0]-SunFlower	[1]-PeaShooter	[2]-WallNut
			[3]-Chomper		[4]-Jalapeno	[5]-CherryBomb
		*/
		bool returnValue = false;

		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			if ((ePlantsType)_idx == mPickedCardList[idx].plantsType)
			{
				/*
					Ȯ���Ϸ��� ī�� �ѹ���(_idx)��
					���õ� ī�� ���(mPickedCardList)�� ���Ͽ�
					�ѹ���(_idx)�� ��Ͽ� �����ϴ� ���
					
					��, �ش�ī�尡 �̹� ���õ� ���
				*/
				returnValue = true;
				break;
			}
		}

		return returnValue;
	}//END-bool CScenePlayGrassDay::FnChkPickedBefore

	void CScenePlayGrassDay::FnDrawWholeCardList()
	{
		for (int idx = 0; idx < MAX_CARDS_WHOLE; idx++)
		{
			/*
				���õ� ī�� ��� ���� ���Ͽ�,
				���� idx�� �ش��ϴ� ī�尡 ���õ� ī������ Ȯ��
			*/
			bool FlagChkPickedBefore = FnChkPickedBefore(idx);

			if (FlagChkPickedBefore)
			{// ���õ� ī���� ��� - Disalbed�� ǥ��
				switch (idx)
				{
				case (int)ePlantsType::SunFlower:	// 0
					mCard_Picked_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_2));
					mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::PeaShooter:	// 1
					mCard_Picked_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_2));
					mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::WallNut:		// 2
					mCard_Picked_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_2));
					mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Chomper:		// 3
					mCard_Picked_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_2));
					mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::Jalapeno:	// 4
					mCard_Picked_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_2));
					mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_1));
					break;
				case (int)ePlantsType::CherryBomb:	// 5
					mCard_Picked_CherryBomb_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_2));
					mCard_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.f, POS_Z_FRONT_1));
					break;
				default:
					break;
				}
			}
			else
			{// ���õ��� ���� ī���� ��� - Disalbed�� �ƴ� ī��� ǥ��
				switch (idx)
				{
				case (int)ePlantsType::SunFlower:	// 0
					mCard_Picked_SunFlower_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_1));
					mCard_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.5f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::PeaShooter:	// 1
					mCard_Picked_PeaShooter_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_1));
					mCard_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.5f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::WallNut:		// 2
					mCard_Picked_WallNut_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_1));
					mCard_WallNut->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.f, 1.5f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::Chomper:		// 3
					mCard_Picked_Chomper_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_1));
					mCard_Chomper->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-2.f, 1.f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::Jalapeno:	// 4
					mCard_Picked_Jalapeno_Disalbed->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_1));
					mCard_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-1.f, 1.f, POS_Z_FRONT_2));
					break;
				case (int)ePlantsType::CherryBomb:	// 5
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
		// �ʱ�ȭ - ���� Card���
		//==================================================================
		mCard_Picked_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		mCard_Picked_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

		//==================================================================
		// mPickedList�� ����, Player�� ����� Card��� �׸���
		//==================================================================
		/*
			- ī�� ���� ����� ���
			�޺�����Ʈ�� ��Ÿ�ӿ� �������
			������ Ȱ��ȭ���·�
			��� �׸���
			
			- �÷��� ����� ���
			�޺� ����Ʈ�� ��Ÿ���� �ݿ��Ͽ�
			Ȱ��ȭ���� �Ǵ� ��Ȱ��ȭ ���·�
			��� �׸���
		*/
		for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
		{
			// �ش� �ε����� ���� ������ �׸��� �н�
			if (ePlantsType::End == mPickedCardList[idx].plantsType)
				continue;

			bool flagDoMakeFalse = false;

			// ���� - ���ؽð�(ī�� ��Ÿ��) counting
			mPickedCardList[idx].coolTime += CTime::FnDeltaTime();

			// ���õ� ī�� Ÿ������ card_Picked_Tmp ����
			switch (mPickedCardList[idx].plantsType)
			{
			case ePlantsType::SunFlower:
				if ((eStepMode::Play == _step && !mPickedCardList[idx].isCoolTimeActive && 50 <= mSunLightScore)
					|| (mPickedCardList[idx].isCoolTimeActive && 10.f <= mPickedCardList[idx].coolTime)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_SunFlower;
					flagDoMakeFalse = true;
				}
				else
					card_Picked_Tmp = mCard_Picked_SunFlower_Disalbed;
				break;
			case ePlantsType::PeaShooter:
				if ((eStepMode::Play == _step && !mPickedCardList[idx].isCoolTimeActive && 100 <= mSunLightScore)
					|| (mPickedCardList[idx].isCoolTimeActive && 10.f <= mPickedCardList[idx].coolTime)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_PeaShooter;
					flagDoMakeFalse = true;
				}
				else
					card_Picked_Tmp = mCard_Picked_PeaShooter_Disalbed;
				break;
			case ePlantsType::WallNut:
				if ((eStepMode::Play == _step && !mPickedCardList[idx].isCoolTimeActive && 50 <= mSunLightScore)
					|| (mPickedCardList[idx].isCoolTimeActive && 10.f <= mPickedCardList[idx].coolTime)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_WallNut;
					flagDoMakeFalse = true;
				}
				else
					card_Picked_Tmp = mCard_Picked_WallNut_Disalbed;
				break;
			case ePlantsType::Chomper:
				if ((eStepMode::Play == _step && !mPickedCardList[idx].isCoolTimeActive && 150 <= mSunLightScore)
					|| (mPickedCardList[idx].isCoolTimeActive && 10.f <= mPickedCardList[idx].coolTime)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_Chomper;
					flagDoMakeFalse = true;
				}
				else
					card_Picked_Tmp = mCard_Picked_Chomper_Disalbed;
				break;
			case ePlantsType::Jalapeno:
				if ((eStepMode::Play == _step && !mPickedCardList[idx].isCoolTimeActive && 125 <= mSunLightScore)
					|| (mPickedCardList[idx].isCoolTimeActive && 10.f <= mPickedCardList[idx].coolTime)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_Jalapeno;
					flagDoMakeFalse = true;
				}
				else
					card_Picked_Tmp = mCard_Picked_Jalapeno_Disalbed;
				break;
			case ePlantsType::CherryBomb:
				if ((eStepMode::Play == _step && !mPickedCardList[idx].isCoolTimeActive && 150 <= mSunLightScore)
					|| (mPickedCardList[idx].isCoolTimeActive && 10.f <= mPickedCardList[idx].coolTime)
					|| eStepMode::Choose == _step)
				{
					card_Picked_Tmp = mCard_Picked_CherryBomb;
					flagDoMakeFalse = true;
				}
				else
					card_Picked_Tmp = mCard_Picked_CherryBomb_Disalbed;
				break;
			}

			// ���õ� ī���� �׸���
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

			// ���� - ī�� Ȱ��ȭ ����, ���ؽð�(ī�� ��Ÿ��)End
			if (flagDoMakeFalse)
			{
				mPickedCardList[idx].isDisabled = false;
				mPickedCardList[idx].isCoolTimeActive = false;
			}
			else
				mPickedCardList[idx].isDisabled = true;

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
			// ��ȿ���� ���ý�
			//==================================================================
			if ((75.f <= MousePos.x) && (123.f >= MousePos.x)
				&& (728.f <= MousePos.y) && (773.f >= MousePos.y))
			{
				
				// �ʱ�ȭ - ���õ� ī�� ���
				for (size_t idx = 0; idx < MAX_CARDS_PICKED; idx++)
				{
					mPickedCardList[idx].plantsType = ePlantsType::End;
					mPickedCardList[idx].isDisabled = false;
				}

				// �ʱ�ȭ - ���õ� ī�� �׸�
				mCard_Picked_SunFlower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				mCard_Picked_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

				// �ʱ�ȭ - ���õ� ī�� �� ����
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
			// ��ȿ���� ���ý�
			//==================================================================
			if ((520.f <= MousePos.x) && (675.f >= MousePos.x)
				&& (819.f <= MousePos.y) && (880.f >= MousePos.y)
				&& mCntPickedCard == MAX_CARDS_PICKED)
			{// Play ��� ���� ���� ������

				mFlagPlayEnter = true;

				mPickedCardType = ePlantsType::End;
				mCntPickedCard = 0;

				//==================================================================
				// UI �ʱ�ȭ
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
				// UI - ��ü ī�� ���
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
				// UI - ������ ī�� ���
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
				&& mCntPickedCard != MAX_CARDS_PICKED)
			{// Play ��� ���� ���� ��������

				TCHAR Temp[256] = { 0, };
				MessageBox(Tmp_mHwnd, L"��밡���� �÷��̾� ������ �Ϸ���� �ʾҽ��ϴ�!", L"Warning", MB_OK);
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

			bool flagMakeList = false;

			//==================================================================
			// ��ȿ���� ���ý�
			//==================================================================
			// Card_SunFlower
			if ((320.f <= MousePos.x) && (480.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::SunFlower;
				flagMakeList = true;
			}

			// Card_PeaShooter
			if ((520.f <= MousePos.x) && (680.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::PeaShooter;
				flagMakeList = true;
			}

			// Card_WallNut
			if ((720.f <= MousePos.x) && (880.f >= MousePos.x)
				&& (105.f <= MousePos.y) && (190.f) >= MousePos.y)
			{
				mPickedCardType = ePlantsType::WallNut;
				flagMakeList = true;
			}

			// Card_Chomper
			if ((320.f <= MousePos.x) && (480.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::Chomper;
				flagMakeList = true;
			}

			// Card_Jalapeno
			if ((520.f <= MousePos.x) && (680.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::Jalapeno;
				flagMakeList = true;
			}

			// Card_CherryBomb
			if ((720.f <= MousePos.x) && (880.f >= MousePos.x)
				&& (205.f <= MousePos.y) && (290.f >= MousePos.y))
			{
				mPickedCardType = ePlantsType::CherryBomb;
				flagMakeList = true;
			}

			//==================================================================
			// ��ü ī�� ��Ͽ��� Card ���ý�, ���õ� ī�� ��Ͽ� Card �߰�
			//==================================================================
			/*
				������ ī�尡
				����ī���Ͽ� �����ϴ��� Ȯ�� ��,

				�������� ������
				����ī���Ͽ� �߰�

				�����ϸ�
				�ƹ��۾��� ���� ����
			*/
			if (flagMakeList)
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
			// ��ȿ���� ���ý�
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
			// ���� ���� - ���õ� ī�� ��Ͽ��� Card ���ý�
			//==================================================================
			if (flagDoDelete)
			{
				mPickedCardType = ePlantsType::End;
				mPickedCardList[deleteIdx].plantsType = ePlantsType::End;
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
			// ��ȿ���� ���ý�
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
				// ���� ���� - �̱��
				if (mflagIsShovelSelected)
					FnRelease_Shovel();

				if ((true == mflagIsCardSelected)
					&& (mPickedCardType == mPickedCardList[idx].plantsType))
				{
					//==================================================================
					// ��Ȱ��ȭ - �̹���(������ ī�� ǥ��)
					//==================================================================
					/*
						ī�尡 ���õ� ���¿���
						�⼱�ð� ������ ī��� ��Ŭ����
					*/
					flagChkRelease_CardSelected = true;
				}
				else if (false == mPickedCardList[idx].isDisabled)
				{
					//==================================================================
					// Ȱ��ȭ - �̹���(������ ī�� ǥ��)
					//==================================================================
					/*
						��Ȱ���� �ƴ� ������ ī�带 Ŭ����
						(ī�尡 ���õ� ���¿��� �⼱�ð� �ٸ� ī�带 ������ ��쵵 �ش�)
					*/
					mPickedCardType = mPickedCardList[idx].plantsType;
					mflagIsCardSelected = true;

					// �̹���(������ ī�� ǥ��)�� ������ idx�� �ش��ϴ� Position�� �̵�
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
			// ��Ȱ��ȭ - �̹���(������ ī�� ǥ��)
			//==================================================================
			/* (Exception)���� ���� - ī�尡 ���õ� ���¿���

				&&
				- ī���� ������ ����� ��
				- ���Ӻ���(�ܵ��) ���Կ��� Ȯ���Ͽ� �׿� ����ģ ������ ��
				- ī�尡 ���õ� ������ ��
				
				||
				- ī�尡 ���õ� ���¿��� �⼱�ð� ������ ī��� ��Ŭ����
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
			// �̱���� Ŭ���� ���
			//==================================================================
			if ((610.f <= MousePos.x) && (690.f >= MousePos.x)
				&& (10.f <= MousePos.y) && (90.f >= MousePos.y))
			{
				// ���� ���� - ī��
				if (mflagIsCardSelected)
					FnRelease_Card();

				if (!mflagIsShovelSelected)
				{// �̱���� ��Ȱ��ȭ���� ��� - Ȱ��ȭ�� ����
					mflagIsShovelSelected = true;
					mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-0.75f, 2.f, 0.003f));
				}
				else
				{// �̱�� Ȱ��ȭ���� ��� - ��Ȱ��ȭ�� ���� (�̱���� �̹� ���õ� ���¿��� �ٽ� �̱���� Ŭ���� ����)
					mflagIsShovelSelected = false;
					mUI_SelectedShovel->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				}
			}
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

			int idx = 0;			// Ŭ�� ��ġ Ȯ�ο�
			bool flagDo = false;	// Ŭ���� ���� ó�� ����

			//==================================================================
			// ����(horizontal row)		1��°
			// ����(vertical column)	9���� ��
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
			// ����(horizontal row)		2��°
			// ����(vertical column)	9���� ��
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
			// ����(horizontal row)		3��°
			// ����(vertical column)	9���� ��
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
			// ����(horizontal row)		4��°
			// ����(vertical column)	9���� ��
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
			// ����(horizontal row)		5��°
			// ����(vertical column)	9���� ��
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
			// ���� ��ġ�� ó��
			// �Ĺ� �ɱ� �Ǵ� �̱�
			// �Ǵ� �޺� ����Ʈ Ŭ�� ó��
			//==================================================================
			if (flagDo)
			{
				if ((true == mSunLights[idx].isExist)
					&& (false == mflagIsCardSelected)
					&& (false == mflagIsShovelSelected))
				{
					//==================================================================
					// ���� - �޺� ����Ʈ ����
					//==================================================================
					//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
					//TCHAR Temp[256] = { 0, };
					//_stprintf_s(Temp, L"mSunScore: % d -> %d", mSunLightScore, mSunLightScore + 25);
					//MessageBox(Tmp_mHwnd, Temp, L"§", MB_OK);

					// ��Ȱ��ȭ - �޺�
					mSunLights[idx].isExist = false;
					mSunLights[idx].position = POSITION_CLEAR;
					mSunLights[idx].cycleChkTime = 0.f;

					// ���� - �޺� ����Ʈ ����
					mSunLightScore += 25;
				}
				else if ((true == mflagIsCardSelected)		// ī��	: O
					&& (false == mflagIsShovelSelected))	// ��	: X
				{
					//==================================================================
					// �ɱ�
					//==================================================================
					FnPutPlants(idx);
				}
				else if ((true == mflagIsShovelSelected)	// ��	: O
					&& (false == mflagIsCardSelected))		// ī��	: X
				{
					//==================================================================
					// �̱�
					//==================================================================
					FnRemovePlants(idx);
				}
			}

		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CScenePlayGrassDay::FnClickEvent_Board

	void CScenePlayGrassDay::FnPutPlants(int _posIdx)
	{
		bool chkIsPlantsNow = mBoard[_posIdx].isPlanted;

		if (!chkIsPlantsNow)
		{// �ش� ĭ�� �Ĺ��� ���� ����

			/*
				���� - Status
				���� - �Ĺ� ���� ����
				���� - �浹ü ����
				���� - �ش� ��ǥ�� ������ ���� ���
				���� - �޺� ����Ʈ ����

				���� - �ش� ��ǥ�� ������ ���� ��� (����)
			*/
			switch (mPickedCardType)
			{
#pragma region SunFlower
			case ePlantsType::SunFlower:
			{
				if (50 <= mSunLightScore)
				{
					FnChangeStatus_Plants(ePlantsType::SunFlower, _posIdx, eStatusType::Idle);
					mPlants_SunFlowers[_posIdx].isPlanted = true;
					mPlants_SunFlowers[_posIdx].collider = mPlants_SunFlowers[_posIdx].plants->FnAddComponent<CCollider2D>();
					mPlants_SunFlowers[_posIdx].collider->FnSetSize(Vector2(0.3f, 0.3f));
					mBoard[_posIdx].plantsType = ePlantsType::SunFlower;
					mSunLightScore -= 50;

					//-------------------------------------
					// Only SunFlower
					//-------------------------------------
					mSunLights[_posIdx].isExistSunflower	= true;
					mSunLights[_posIdx].cycleChkTime		= 0.f;
				}
			}
			break;
#pragma endregion
#pragma region WallNut
			case ePlantsType::WallNut:
			{
				if (50 <= mSunLightScore)
				{
					FnChangeStatus_Plants(ePlantsType::WallNut, _posIdx, eStatusType::Idle);
					mPlants_WallNuts[_posIdx].isPlanted = true;
					mPlants_WallNuts[_posIdx].collider = mPlants_WallNuts[_posIdx].plants->FnAddComponent<CCollider2D>();
					mPlants_WallNuts[_posIdx].collider->FnSetSize(Vector2(0.3f, 0.3f));
					mBoard[_posIdx].plantsType = ePlantsType::WallNut;
					mSunLightScore -= 50;
				}
			}
			break;
#pragma endregion
#pragma region PeaShooter
			case ePlantsType::PeaShooter:
			{
				if (100 <= mSunLightScore)
				{
					FnChangeStatus_Plants(ePlantsType::PeaShooter, _posIdx, eStatusType::Idle);
					mPlants_Peashooters[_posIdx].isPlanted = true;
					mPlants_Peashooters[_posIdx].collider = mPlants_Peashooters[_posIdx].plants->FnAddComponent<CCollider2D>();
					mPlants_Peashooters[_posIdx].collider->FnSetSize(Vector2(0.3f, 0.3f));
					mBoard[_posIdx].plantsType = ePlantsType::PeaShooter;
					mSunLightScore -= 100;
				}
			}
			break;
#pragma endregion
#pragma region Chomper
			case ePlantsType::Chomper:
			{
				if (150 <= mSunLightScore)
				{
					FnChangeStatus_Plants(ePlantsType::Chomper, _posIdx, eStatusType::Idle);
					mPlants_Chompers[_posIdx].isPlanted = true;
					mPlants_Chompers[_posIdx].collider = mPlants_Chompers[_posIdx].plants->FnAddComponent<CCollider2D>();
					mPlants_Chompers[_posIdx].collider->FnSetSize(Vector2(1.1f, 0.5f));
					mPlants_Chompers[_posIdx].collider->FnSetCenter(Vector2(0.2f, -0.05f));
					mBoard[_posIdx].plantsType = ePlantsType::Chomper;
					mSunLightScore -= 150;
				}
			}
			break;
#pragma endregion
#pragma region Jalapeno
			case ePlantsType::Jalapeno:
				break;
#pragma endregion
#pragma region CherryBomb
			case ePlantsType::CherryBomb:
				break;
#pragma endregion
			default:
				break;
			}

			//==================================================================
			// (����) ���� - �ش� ��ǥ�� ������ ���� ���
			//==================================================================
			mBoard[_posIdx].isPlanted = true;

			/*
				���õ� �Ĺ��� ������ ��ġ�� �ɰ� ����
				1. ���� - ���ؽð�(ī�� ��Ÿ��) Start
				2. ���� ���� - ī��
			*/
			//==================================================================
			// 1. ���� - ���ؽð�(ī�� ��Ÿ��) Start
			//==================================================================
			int catchidx = 0;
			for (int idx = 0; idx < MAX_CARDS_PICKED; idx++)
			{
				if (mPickedCardType == mPickedCardList[idx].plantsType)
				{
					catchidx = idx;
					break;
				}
			}
			
			mPickedCardList[catchidx].isCoolTimeActive = true;
			mPickedCardList[catchidx].coolTime = 0.f;
			
			//==================================================================
			// 2. ���� ���� - ī��
			//==================================================================
			FnRelease_Card();

		}//end-if (!chkIsPlantsNow)
		else
		{// �ش� ĭ�� �Ĺ��� �ִ� ����

			TCHAR Temp[256] = { 0, };
			MessageBox(MyApplication.FnGetHwnd(), L"�̹� ���� �Ĺ��� �ֽ��ϴ�.\n���� �Ĺ��� ���� �ٸ� ���� �����ϼ���", L"Warning", MB_OK);
		}
	}//END-void CScenePlayGrassDay::FnPutPlants

	void CScenePlayGrassDay::FnRemovePlants(int _posIdx)
	{
		bool chkIsPlantsNow = mBoard[_posIdx].isPlanted;

		if (chkIsPlantsNow)
		{// �ش� ĭ�� �Ĺ��� �ִ� ����

			ePlantsType removePlantsType = mBoard[_posIdx].plantsType;

			switch (removePlantsType)
			{
#pragma region SunFlower
			case ePlantsType::SunFlower:
			{
				// �Ĺ� �̱�
				mPlants_SunFlowers[_posIdx].isPlanted = false;
				mPlants_SunFlowers[_posIdx].plants->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				FnChangeStatus_Plants(ePlantsType::SunFlower, _posIdx, eStatusType::End);

				/*
					�̱������ ���Ž� �浹ü ����
					�ǰ������� ���Ž� �浹ü ����X
				*/
				if (mflagIsShovelSelected)
				{
					// ���� - �浹ü ����
					mPlants_SunFlowers[_posIdx].plants->FnDeleteCollider();
					mPlants_SunFlowers[_posIdx].collider = nullptr;
				}

				//-------------------------------------
				// Only SunFlower
				//-------------------------------------
				mSunLights[_posIdx].isExistSunflower = false;
			}
			break;
#pragma endregion
#pragma region WallNut
			case ePlantsType::WallNut:
			{
				mPlants_WallNuts[_posIdx].isPlanted = false;
				mPlants_WallNuts[_posIdx].plants->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				FnChangeStatus_Plants(ePlantsType::WallNut, _posIdx, eStatusType::End);

				if (mflagIsShovelSelected)
				{
					mPlants_WallNuts[_posIdx].plants->FnDeleteCollider();
					mPlants_WallNuts[_posIdx].collider = nullptr;
				}
			}
			break;
#pragma endregion
#pragma region PeaShooter
			case ePlantsType::PeaShooter:
			{
				mPlants_Peashooters[_posIdx].isPlanted = false;
				mPlants_Peashooters[_posIdx].plants->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				FnChangeStatus_Plants(ePlantsType::WallNut, _posIdx, eStatusType::End);

				if (mflagIsShovelSelected)
				{
					mPlants_Peashooters[_posIdx].plants->FnDeleteCollider();
					mPlants_Peashooters[_posIdx].collider = nullptr;
				}
			}
			break;
#pragma endregion
#pragma region Chomper
			case ePlantsType::Chomper:
			{
				mPlants_Chompers[_posIdx].isPlanted = false;
				mPlants_Chompers[_posIdx].plants->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				FnChangeStatus_Plants(ePlantsType::WallNut, _posIdx, eStatusType::End);

				if (mflagIsShovelSelected)
				{
					mPlants_Chompers[_posIdx].plants->FnDeleteCollider();
					mPlants_Chompers[_posIdx].collider = nullptr;
				}
			}
			break;
#pragma endregion
#pragma region Jalapeno
			case ePlantsType::Jalapeno:
				break;
#pragma endregion
#pragma region CherryBomb
			case ePlantsType::CherryBomb:
				break;
#pragma endregion
			default:
				break;
			}

			//==================================================================
			// (����) ���� - �ش� ��ǥ�� ������ ���� ���
			//==================================================================
			mBoard[_posIdx].isPlanted = false;
			mBoard[_posIdx].plantsType = ePlantsType::End;

			//==================================================================
			// (����) ���� ���� - �̱�� (�̱���� ���õ� ���)
			//==================================================================
			if (mflagIsShovelSelected)
				FnRelease_Shovel();

		}//end-if (!chkIsPlantsNow)
		else
		{// �ش� ĭ�� �Ĺ��� ���� ����

			TCHAR Temp[256] = { 0, };
			MessageBox(MyApplication.FnGetHwnd(), L"�� ������ �Ĺ��� �����ϴ�.\n���� �Ĺ��� �ִ� �ٸ� ���� �����ϼ���", L"Warning", MB_OK);
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

	void CScenePlayGrassDay::FnManageSunLight_Sunflower()
	{
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			// ���� - �޺� �����ֱ� �ð�
			mSunLights[idx].cycleChkTime += (float)CTime::FnDeltaTime();

			if ((true == mSunLights[idx].isExist)
				&& (7.f <= mSunLights[idx].cycleChkTime))
			{// �޺��� �����Ǿ� �ִ� ���

				//==================================================================
				// ��Ȱ��ȭ - �޺�
				//==================================================================
				/*
					������ ������ �޺� ����Ʈ�� �ִ� ���
					&& ���� �ð��� 7�� �̻�
				*/

				// ��ǥ ����
				mSunLights[idx].position = POSITION_CLEAR;

				// ���� - �޺� ����Ʈ ���� ����
				mSunLights[idx].isExist = false;

				// �ʱ�ȭ - ���ؽð�
				mSunLights[idx].cycleChkTime = 0.f;
			}
			else if ((false == mSunLights[idx].isExist)
				&& (true == mBoard[idx].isPlanted)
				&& (ePlantsType::SunFlower == mBoard[idx].plantsType)
				&& (true == mSunLights[idx].isExistSunflower))
			{// �޺��� �������� �ʾҰ�, �عٶ�Ⱑ �ɾ��� ���

				//==================================================================
				// ���� - �޺� ���� �ֱ�ð�
				//==================================================================
				/*
					�޺� ����Ʈ ������ ����
					���� �ֱ� �ð��� ����
				*/
				float limitTime = 0.f;

				if (100 > mSunLightScore)
					limitTime = 10.f;
				else if ((100 <= mSunLightScore) && (200 > mSunLightScore))
					limitTime = 15.f;
				else if (200 <= mSunLightScore)
					limitTime = 20.f;

				if ((limitTime - 2.f <= mSunLights[idx].cycleChkTime) 
					&& (limitTime > mSunLights[idx].cycleChkTime))
				{
					//==================================================================
					// ���� - Status
					//==================================================================
					// ���� �ð� 2�� ��
					FnChangeStatus_Plants(ePlantsType::SunFlower, idx, eStatusType::Bright_OnlySunflower);
				}
				else if (limitTime <= mSunLights[idx].cycleChkTime)
				{
					//==================================================================
					// Ȱ��ȭ - �޺�
					//==================================================================
					// ���� �ð��� 10�� �̻�

					// ��ǥ ����
					Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
					posNumbSet = positonList[idx];
					posNumbSet.y -= 0.1f;
					posNumbSet.z = POS_Z_FRONT_1;
					mSunLights[idx].position = posNumbSet;

					// ���� - �޺� ����Ʈ ���� ����
					mSunLights[idx].isExist = true;

					// �ʱ�ȭ - ���ؽð�
					mSunLights[idx].cycleChkTime = 0.f;

					//==================================================================
					// ���� - Status
					//==================================================================
					FnChangeStatus_Plants(ePlantsType::SunFlower, idx, eStatusType::Idle);
				}
			}
		}//end-for (int idx = 0; idx < MAXCOUNT_PLANTS; idx++)
	}//END-void CScenePlayGrassDay::FnManageSunLight_Sunflower

	void CScenePlayGrassDay::FnManageSunLight_Natural()
	{
		bool flagDo = false; // ���� ���� ����

		//==================================================================
		// Ȯ�� - �޺� ���� ����
		//==================================================================
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
		{
			if (false == mSunLights_Natural[idx].isExist)
				flagDo = true;
		}

		//==================================================================
		// ����
		//==================================================================
		if (flagDo)
		{
			//-------------------------------------
			// ���� - �޺� ���� �ֱ�ð�
			//-------------------------------------
			/*
				�޺� ����Ʈ ������ ����
				���� �ֱ� �ð��� ����
			*/
			float limitTime = 0.f;

			if (100 > mSunLightScore)
				limitTime = 10.f;
			else if ((100 <= mSunLightScore) && (200 > mSunLightScore))
				limitTime = 15.f;
			else if (200 <= mSunLightScore)
				limitTime = 10.f;

			if (limitTime <= mChkSecond_SunLight)
			{
				//-------------------------------------
				// ���� ��ǥ ����
				//-------------------------------------
				srand((unsigned int)CTime::FnDeltaTime());
				int random = rand();	// �������
				int idx = 0;			// ���� ��ǥ //(�ִ� - �ּ� + 1) + �ּ�
				int conversionIdx = 0;	// ��ȯ�� ��ǥ

				//-------------------------------------
				// ������ ���� Ȯ��
				//-------------------------------------
				while (true)
				{
					idx = rand() % MAX_SUNLIGHT_NATURAL;

					if (false == mSunLights_Natural[idx].isExist)
						break;
				}

				//-------------------------------------
				// ��ǥ ��ȯ (5*5) -> (9*5)
				//-------------------------------------
				if (5 > idx)
					conversionIdx = idx;
				else if ((5 <= idx) && (9 >= idx))
					conversionIdx = idx + 4;
				else if ((10 <= idx) && (14 >= idx))
					conversionIdx = idx + 8;

				//-------------------------------------
				// ��ǥ(������) ����
				//-------------------------------------
				Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
				posNumbSet = positonList[conversionIdx];
				posNumbSet.x -= 0.2f;
				posNumbSet.y -= 0.2f;
				posNumbSet.z = POS_Z_FRONT_2;
				mSunLights_Natural[idx].destination = posNumbSet;
				posNumbSet.y = 2.f;	// ����ȭ��� �� ��
				mSunLights_Natural[idx].position = posNumbSet;
				mSunLights_Natural[idx].isExist = true;
				mSunLights_Natural[idx].isArrived = false;

				//-------------------------------------
				// �ʱ�ȭ - �� ī����(�޺� ������)
				//-------------------------------------
				mChkSecond_SunLight = 0.f;
			}
		}//end-if (flagDo)

		//==================================================================
		// ���� - ��ǥ
		//==================================================================
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
		{
			if (true == mSunLights_Natural[idx].isExist)
			{
				float now = mSunLights_Natural[idx].position.y;
				float destination = mSunLights_Natural[idx].destination.y;

				if ((false == mSunLights_Natural[idx].isArrived)
					&& (destination >= now))
				{
					mSunLights_Natural[idx].isArrived = true;
					mSunLights_Natural[idx].cycleChkTime = 0.f;
				}	
				else if (false == mSunLights_Natural[idx].isArrived)
				{// ������ �������� ���� ���

					// ����
					mSunLights_Natural[idx].position.y -= 0.5f * CTime::FnDeltaTime();
				}
			}
		}

		//==================================================================
		// ��Ȱ��ȭ - �޺�
		//==================================================================
		/*
			������ ������ �޺� ����Ʈ�� �ִ� ���
			&& ���� �ð��� 7�� �̻�
		*/
		for (int idx = 0; idx < MAX_SUNLIGHT_NATURAL; idx++)
		{
			mSunLights_Natural[idx].cycleChkTime += CTime::FnDeltaTime();

			if ((true == mSunLights_Natural[idx].isExist)
				&& (true == mSunLights_Natural[idx].isArrived)
				&& (7.f <= mSunLights_Natural[idx].cycleChkTime))
			{
				// ��ǥ ����
				mSunLights_Natural[idx].position = POSITION_CLEAR;

				// ���� - �޺� ����Ʈ ���� ����
				mSunLights_Natural[idx].isExist = false;

				// �ʱ�ȭ - ���ؽð�
				mSunLights_Natural[idx].cycleChkTime = 0.f;
			}
		}

	}//END-void CScenePlayGrassDay::FnManageSunLight_Natural

	void CScenePlayGrassDay::FnDrawSunLights()
	{
		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			//==================================================================
			// made by Sunflower
			//==================================================================
			// �޺� �������ο� ����
			if (true == mSunLights[idx].isExist)	// Ȱ��ȭ
				mSunLights[idx].sunLight->FnGetComponent<CTransform>()->FnSetPosition(mSunLights[idx].position);
			else									// ��Ȱ��ȭ
				mSunLights[idx].sunLight->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

			//==================================================================
			// made by Natural
			//==================================================================
			if (idx < 25)
			{
				// �޺� �������ο� ����
				if (true == mSunLights_Natural[idx].isExist)	// Ȱ��ȭ
					mSunLights_Natural[idx].sunLight->FnGetComponent<CTransform>()->FnSetPosition(mSunLights_Natural[idx].position);
				else											// ��Ȱ��ȭ
					mSunLights_Natural[idx].sunLight->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			}
		}
	}//END-void CScenePlayGrassDay::FnDrawSunLights

	void CScenePlayGrassDay::FnDrawBoard()
	{
		bool flagDoDraw = false;

		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			if (true == mBoard[idx].isPlanted)
				flagDoDraw = true;
			else
				continue;

			if (flagDoDraw)
			{// ������ �׸��� - �Ĺ��� �ɾ��� ����

				ePlantsType drawPlantsType = mBoard[idx].plantsType;

				FnManageCollider_Plants(drawPlantsType, idx);
				FnManageFSM_Plants(drawPlantsType, idx);
			}
		}
	}//END-void CScenePlayGrassDay::FnDrawBoard

	void CScenePlayGrassDay::FnManageFSM_Plants(ePlantsType _inPlants, int _idx)
	{
		/*
			���� ���´�
			�浹 ���ο� ���� ���º�ȭ�� ����� ����
		*/
		switch (_inPlants)
		{
#pragma region SunFlower
		case ePlantsType::SunFlower:
		{
			//==================================================================
			// SunFlower
			//==================================================================
			mPlants_SunFlowers[_idx].plants->FnGetComponent<CTransform>()->FnSetPosition(positonList[_idx]);

			if (true == mPlants_SunFlowers[_idx].isChangeStatus)
			{// ���� ��ȭ�� �ִ� ���

				switch (mPlants_SunFlowers[_idx].statusType)
				{
				case eStatusType::Idle:
					mPlants_SunFlowers[_idx].animator->FnPlayAnimation(L"SunFlower_Idle", true);
					break;
				case eStatusType::Attacked:
					mPlants_SunFlowers[_idx].animator->FnPlayAnimation(L"SunFlower_Blink", true);
					break;
				case eStatusType::Dead:
					FnRemovePlants(_idx);
					break;
				case eStatusType::Bright_OnlySunflower:
					mPlants_SunFlowers[_idx].animator->FnPlayAnimation(L"SunFlower_Bright", true);
					break;
				}

				mPlants_SunFlowers[_idx].isChangeStatus = false;
			}
		}
		break;
#pragma endregion
#pragma region WallNut
		case ePlantsType::WallNut:
		{
			//==================================================================
			// WallNut
			//==================================================================
			mPlants_WallNuts[_idx].plants->FnGetComponent<CTransform>()->FnSetPosition(positonList[_idx]);

			if (true == mPlants_WallNuts[_idx].isChangeStatus)
			{// ���� ��ȭ�� �ִ� ���

				switch (mPlants_WallNuts[_idx].statusType)
				{
				case eStatusType::Idle:
					mPlants_WallNuts[_idx].animator->FnPlayAnimation(L"WallNut_Idle", true);
					break;
				case eStatusType::Attack:
					mPlants_WallNuts[_idx].animator->FnPlayAnimation(L"WallNut_Cracked1", true);
					break;
				case eStatusType::Attacked:
					mPlants_WallNuts[_idx].animator->FnPlayAnimation(L"WallNut_Cracked2", true);
					break;
				case eStatusType::Dead:
					FnRemovePlants(_idx);
					break;
				}

				mPlants_WallNuts[_idx].isChangeStatus = false;
			}
		}
		break;
#pragma endregion
#pragma region PeaShooter
		case ePlantsType::PeaShooter:
		{
			//==================================================================
			// PeaShooter
			//==================================================================
			mPlants_Peashooters[_idx].plants->FnGetComponent<CTransform>()->FnSetPosition(positonList[_idx]);

			if (true == mPlants_Peashooters[_idx].isChangeStatus)
			{// ���� ��ȭ�� �ִ� ���

				switch (mPlants_Peashooters[_idx].statusType)
				{
				case eStatusType::Idle:
					mPlants_Peashooters[_idx].animator->FnPlayAnimation(L"PeaShooter_Idle", true);
					break;
				case eStatusType::Attack:
					mPlants_Peashooters[_idx].animator->FnPlayAnimation(L"PeaShooter_Idle", true);
					break;
				case eStatusType::Attacked:
					mPlants_Peashooters[_idx].animator->FnPlayAnimation(L"PeaShooter_Idle", true);
					break;
				case eStatusType::Dead:
					FnRemovePlants(_idx);
					break;
				}

				mPlants_Peashooters[_idx].isChangeStatus = false;
			}
		}
		break;
#pragma endregion
#pragma region Chomper
		case ePlantsType::Chomper:
		{
			//==================================================================
			// Chomper
			//==================================================================
			// ��ǥ ����
			Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
			posNumbSet = positonList[_idx];
			posNumbSet.x += 0.2f;
			posNumbSet.y += 0.1f;
			posNumbSet.z = POS_Z_FRONT_1;

			mPlants_Chompers[_idx].plants->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);

			if (true == mPlants_Chompers[_idx].isChangeStatus)
			{// ���� ��ȭ�� �ִ� ���

				switch (mPlants_Chompers[_idx].statusType)
				{
				case eStatusType::Idle:
					mPlants_Chompers[_idx].animator->FnPlayAnimation(L"Chomper_Idle", true);
					break;
				case eStatusType::Attack:
					mPlants_Chompers[_idx].animator->FnPlayAnimation(L"Chomper_Attack", true);
					break;
				case eStatusType::Attacked:
					mPlants_Chompers[_idx].animator->FnPlayAnimation(L"Chomper_Attack", true);
					break;
				case eStatusType::Dead:
					FnRemovePlants(_idx);
					break;
				}

				mPlants_Chompers[_idx].isChangeStatus = false;
			}
		}
		break;
#pragma endregion
#pragma region Jalapeno
		case ePlantsType::Jalapeno:
			break;
#pragma endregion
#pragma region CherryBomb
		case ePlantsType::CherryBomb:
			break;
#pragma endregion
		default:
			break;
		}
	}//END-void CScenePlayGrassDay::FnManageFSM_Plants

	void CScenePlayGrassDay::FnManageFSM_Zombies()
	{
	}//END-void CScenePlayGrassDay::FnManageFSM_Zombies
	
	void CScenePlayGrassDay::FnManageCollider_Plants(ePlantsType _inPlants, int _idx)
	//void CScenePlayGrassDay::FnManageCollider_Plants()
	{
		switch (_inPlants)
		{
#pragma region SunFlower
		case ePlantsType::SunFlower:
		{
			//==================================================================
			// SunFlower
			//==================================================================
			eColliderStateType nowState = mPlants_SunFlowers[_idx].collider->FnGetColliderState();

			switch (nowState)
			{
			case eColliderStateType::Start:
			{
				FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Attacked);
				mPlants_SunFlowers[_idx].isAttacked = true;
			}
			break;
			case eColliderStateType::Ing:
			{
				mPlants_SunFlowers[_idx].attackedTime += CTime::FnDeltaTime();

				if ((true == mPlants_SunFlowers[_idx].isAttacked)
					&& (2.f <= mPlants_SunFlowers[_idx].attackedTime))
				{
					FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Dead);
					mPlants_SunFlowers[_idx].attackedTime = 0.f;
				}
			}
			break;
			case eColliderStateType::Fin:
			{// ���� - Idle
				if ((true == mPlants_SunFlowers[_idx].isAttacked)
					&& (eStatusType::Dead == mPlants_SunFlowers[_idx].statusType))
				{
					// ���� - �浹ü ����
					mPlants_SunFlowers[_idx].plants->FnDeleteCollider();
					mPlants_SunFlowers[_idx].collider = nullptr;

					// ����
					mPlants_SunFlowers[_idx].isAttacked = false;
					mPlants_SunFlowers[_idx].attackedTime = 0.f;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
#pragma endregion
#pragma region WallNut
		case ePlantsType::WallNut:
		{
			//==================================================================
			// WallNut
			//==================================================================
			eColliderStateType nowState = mPlants_WallNuts[_idx].collider->FnGetColliderState();

			switch (nowState)
			{
			case eColliderStateType::Start:
			{
				FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Attack);
				mPlants_WallNuts[_idx].isAttacked = true;
			}
			break;
			case eColliderStateType::Ing:
			{
				mPlants_WallNuts[_idx].attackedTime += CTime::FnDeltaTime();

				if ((true == mPlants_WallNuts[_idx].isAttacked)
					&& (8.f <= mPlants_WallNuts[_idx].attackedTime)
					&& (eStatusType::Attack == mPlants_WallNuts[_idx].statusType))
				{
					FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Attacked);
					mPlants_WallNuts[_idx].attackedTime = 0.f;
				}
				else if ((true == mPlants_WallNuts[_idx].isAttacked)
					&& (2.f <= mPlants_WallNuts[_idx].attackedTime)
					&& (eStatusType::Attacked == mPlants_WallNuts[_idx].statusType))
				{
					FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Dead);
				}
			}
			break;
			case eColliderStateType::Fin:
			{
				if ((true == mPlants_WallNuts[_idx].isAttacked)
					&& (eStatusType::Dead == mPlants_WallNuts[_idx].statusType))
				{
					mPlants_WallNuts[_idx].plants->FnDeleteCollider();
					mPlants_WallNuts[_idx].collider = nullptr;

					mPlants_WallNuts[_idx].isAttacked = false;
					mPlants_WallNuts[_idx].attackedTime = 0.f;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
#pragma endregion
#pragma region PeaShooter
		case ePlantsType::PeaShooter:
		{
			//==================================================================
			// PeaShooter
			//==================================================================
			eColliderStateType nowState = mPlants_Peashooters[_idx].collider->FnGetColliderState();

			switch (nowState)
			{
			case eColliderStateType::Start:
			{
				FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Attack);
				mPlants_Peashooters[_idx].isAttacked = true;
			}
			break;
			case eColliderStateType::Ing:
			{
				mPlants_Peashooters[_idx].attackedTime += CTime::FnDeltaTime();

				if ((true == mPlants_Peashooters[_idx].isAttacked)
					&& (2.f <= mPlants_Peashooters[_idx].attackedTime))
				{
					FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Dead);
					mPlants_Peashooters[_idx].attackedTime = 0.f;
				}
			}
			break;
			case eColliderStateType::Fin:
			{// ���� - Idle
				if ((true == mPlants_Peashooters[_idx].isAttacked)
					&& (eStatusType::Dead == mPlants_Peashooters[_idx].statusType))
				{
					// ���� - �浹ü ����
					mPlants_Peashooters[_idx].plants->FnDeleteCollider();
					mPlants_Peashooters[_idx].collider = nullptr;

					// ����
					mPlants_Peashooters[_idx].isAttacked = false;
					mPlants_Peashooters[_idx].attackedTime = 0.f;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
#pragma endregion
#pragma region Chomper
		case ePlantsType::Chomper:
		{
			//==================================================================
			// Chomper
			//==================================================================
			eColliderStateType nowState = mPlants_Chompers[_idx].collider->FnGetColliderState();

			switch (nowState)
			{
			case eColliderStateType::Start:
			{
				FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Attacked);
				mPlants_Chompers[_idx].isAttacked = true;
			}
			break;
			case eColliderStateType::Ing:
			{
				mPlants_Chompers[_idx].attackedTime += CTime::FnDeltaTime();

				if ((true == mPlants_Chompers[_idx].isAttacked)
					&& (2.f <= mPlants_Chompers[_idx].attackedTime))
				{
					FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Dead);
					mPlants_Chompers[_idx].attackedTime = 0.f;
				}
			}
			break;
			case eColliderStateType::Fin:
			{// ���� - Idle
				if ((true == mPlants_Chompers[_idx].isAttacked)
					&& (eStatusType::Dead == mPlants_Chompers[_idx].statusType))
				{
					// ���� - �浹ü ����
					mPlants_Chompers[_idx].plants->FnDeleteCollider();
					mPlants_Chompers[_idx].collider = nullptr;

					// ����
					mPlants_Chompers[_idx].isAttacked = false;
					mPlants_Chompers[_idx].attackedTime = 0.f;
				}
				else if ((true == mPlants_Chompers[_idx].isAttacked)
					&& (eStatusType::Attacked == mPlants_Chompers[_idx].statusType))
				{
					FnChangeStatus_Plants(_inPlants, _idx, eStatusType::Idle);

					// ����
					mPlants_Chompers[_idx].isAttacked = false;
					mPlants_Chompers[_idx].attackedTime = 0.f;
				}
			}
			break;
			default:
				break;
			}
		}
		break;
#pragma endregion
#pragma region Jalapeno
		case ePlantsType::Jalapeno:
			break;
#pragma endregion
#pragma region CherryBomb
		case ePlantsType::CherryBomb:
			break;
#pragma endregion
		default:
			break;
		}
	}//END-void CScenePlayGrassDay::FnManageCollider_Plants

	void CScenePlayGrassDay::FnManageCollider_Zombies()
	{
		//==================================================================
		// Zombies
		//==================================================================
		//-------------------------------------
		// NormalZombie Status
		//-------------------------------------
		if (false == FlagNormalZombie)
		{
			mZb_NormalZombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.0f, -1.0f, POS_Z_FRONT_1));
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
	}//END-void CScenePlayGrassDay::FnManageCollider_Zombies

	void CScenePlayGrassDay::FnChangeStatus_Plants(ePlantsType _inPlants, int _idx, eStatusType _inStatus)
	{
		switch (_inPlants)
		{
#pragma region SunFlower
		case ePlantsType::SunFlower:
		{
			//==================================================================
			// SunFlower
			//==================================================================
			eStatusType now = _inStatus;
			eStatusType prev = mPlants_SunFlowers[_idx].statusType;

			if (now != prev)
			{
				mPlants_SunFlowers[_idx].isChangeStatus = true;
				mPlants_SunFlowers[_idx].statusType = now;
			}
			else
				mPlants_SunFlowers[_idx].isChangeStatus = false;
		}
		break;
#pragma endregion
#pragma region WallNut
		case ePlantsType::WallNut:
		{
			//==================================================================
			// WallNut
			//==================================================================
			eStatusType now = _inStatus;
			eStatusType prev = mPlants_WallNuts[_idx].statusType;

			if (now != prev)
			{
				mPlants_WallNuts[_idx].isChangeStatus = true;
				mPlants_WallNuts[_idx].statusType = now;
			}
			else
				mPlants_WallNuts[_idx].isChangeStatus = false;
		}
		break;
#pragma endregion
#pragma region PeaShooter
		case ePlantsType::PeaShooter:
		{
			//==================================================================
			// PeaShooter
			//==================================================================
			eStatusType now = _inStatus;
			eStatusType prev = mPlants_Peashooters[_idx].statusType;

			if (now != prev)
			{
				mPlants_Peashooters[_idx].isChangeStatus = true;
				mPlants_Peashooters[_idx].statusType = now;
			}
			else
				mPlants_Peashooters[_idx].isChangeStatus = false;
		}
		break;
#pragma endregion
#pragma region Chomper
		case ePlantsType::Chomper:
		{
			//==================================================================
			// Chomper
			//==================================================================
			eStatusType now = _inStatus;
			eStatusType prev = mPlants_Chompers[_idx].statusType;

			if (now != prev)
			{
				mPlants_Chompers[_idx].isChangeStatus = true;
				mPlants_Chompers[_idx].statusType = now;
			}
			else
				mPlants_Chompers[_idx].isChangeStatus = false;
		}
		break;
#pragma endregion
#pragma region Jalapeno
		case ePlantsType::Jalapeno:
			break;
#pragma endregion
#pragma region CherryBomb
		case ePlantsType::CherryBomb:
			break;
#pragma endregion
		default:
			break;
		}
	}//END-void CScenePlayGrassDay::FnChangeStatus_Plants
}
