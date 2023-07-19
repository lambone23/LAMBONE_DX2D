#include "CPlayScene.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CMesh.h"
#include "CCameraScript.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CGridScript.h"
#include "CObject.h"
#include "CRenderer.h"
#include "CCollider2D.h"

#include "CApplication.h"
#include <tchar.h>

extern yha::CApplication MyApplication;

namespace yha
{
	CPlayScene::CPlayScene()
	{
	}
	CPlayScene::~CPlayScene()
	{
	}
	void CPlayScene::FnInitialize()
	{
		//==================================================================
		// Contents
		//==================================================================
		{// Zelda [Player]

			//-------------------------------------
			// player - Parent
			//-------------------------------------
			CGameObject* player = object::FnInstantiate<CGameObject>(Vector3(0.0f, 0.0f, 1.0001f), eLayerType::Player);
			//¡áobject //CGameObject* player = new CGameObject();
			player->FnSetName(L"Zelda");
			//¡áobject //FnAddGameObject(eLayerType::Player, player);

			CCollider2D* cd = player->FnAddComponent<CCollider2D>();

			CMeshRenderer* mr = player->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteMaterial"));

			//¡áobject //player->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 1.0001f));
			//¡áobject ////player->FnAddComponent<CCameraScript>();

			//-------------------------------------
			// player2 - Child
			//-------------------------------------
			//CGameObject* player2 = new CGameObject();
			//player2->FnSetName(L"ZeldaChild");
			//FnAddGameObject(eLayerType::Player, player2);

			//CMeshRenderer* mr2 = player2->FnAddComponent<CMeshRenderer>();
			//mr2->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			//mr2->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteMaterial"));

			//player2->FnGetComponent<CTransform>()->FnSetPosition(Vector3(1.0f, 0.0f, 1.0001f));
			////player->AddComponent<CameraScript>();

			//player2->FnGetComponent<CTransform>()->FnSetParent(player->FnGetComponent<CTransform>());
			
			//-------------------------------------
			// player & player2
			//-------------------------------------
			const float pi = 3.141592f;
			float degree = pi / 8.0f; //float degree = pi / 2.0f;
			player->FnGetComponent<CTransform>()->FnSetPosition(Vector3(-3.0f, 0.0f, 1.0001f));
			player->FnGetComponent<CTransform>()->FnSetRotation(Vector3(0.0f, 0.0f, degree));
		}

		{// Smile [Player]
			CGameObject* player = new CGameObject();
			player->FnSetName(L"Smile");
			FnAddGameObject(eLayerType::Player, player);

			CMeshRenderer* mr = player->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteMaterial02"));

			player->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 1.0f)); // (Vector3(0.2f, 0.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		{// Smile [UI]
			CGameObject* player = new CGameObject();
			player->FnSetName(L"Smile");
			FnAddGameObject(eLayerType::UI, player);

			CMeshRenderer* mr = player->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteMaterial02"));
			
			player->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.2f, 0.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		//==================================================================
		// Camera
		//==================================================================
		CCamera* cameraComp = nullptr;

		{// Main Camera - [OFF : UI / ON : Player] - Move[O]
			CGameObject* camera = new CGameObject();
			FnAddGameObject(eLayerType::Player, camera);

			camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
			cameraComp = camera->FnAddComponent<CCamera>();
			cameraComp->FnTurnLayerMask(eLayerType::UI, false);
			camera->FnAddComponent<CCameraScript>();

			renderer::cameras.push_back(cameraComp);
			renderer::mainCamera = cameraComp;
		}

		{// UI Camera - [OFF : Player / ON : UI] - Move[X]
			CGameObject* camera = new CGameObject();
			FnAddGameObject(eLayerType::Player, camera);

			camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* cameraComp = camera->FnAddComponent<CCamera>();
			cameraComp->FnTurnLayerMask(eLayerType::Player, false);
			//camera->FnAddComponent<CCameraScript>();
		}

		//==================================================================
		// Grid (After Camera Set)
		//==================================================================
		{
			CGameObject* grid = new CGameObject();
			grid->FnSetName(L"Grid");
			FnAddGameObject(eLayerType::Grid, grid);
			
			CMeshRenderer* mr = grid->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"GridMaterial"));
			CGridScript* gridSc = grid->FnAddComponent<CGridScript>();
			gridSc->FnSetCamera(cameraComp);
		}

		//CGameObject* player2 = new CGameObject();
		//FnAddGameObject(eLayerType::Player, player2);
		//player2->FnAddComponent<CMeshRenderer>();

		//CTransform* tr = player->FnGetComponent<CTransform>();
		//tr->FnSetPosition(Vector3(0.5f, 0.5f, 0.0f));
	}

	void CPlayScene::FnUpdate()
	{
		CScene::FnUpdate();
	}

	void CPlayScene::FnLateUpdate()
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

	void CPlayScene::FnRender()
	{
		CScene::FnRender();
	}

	void CPlayScene::FnOnEnter()
	{
		//int a = 0;

		//std::wstring name = CSceneManager::FnGetActiveSceneName();
		//if (name == L"PlayScene")
		//	a = 1;

		//HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		//TCHAR Temp[256] = { 0, };
		//_stprintf_s(Temp, L"x: %d", a);
		//MessageBox(Tmp_mHwnd, Temp, L"ÁÂÇ¥", MB_OK);
	}

	void CPlayScene::FnOnExit()
	{

	}
}
