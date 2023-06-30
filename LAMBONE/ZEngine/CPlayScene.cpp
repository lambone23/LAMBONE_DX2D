#include "CPlayScene.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CMesh.h"
#include "CCameraScript.h"
#include "CCamera.h"
#include "CSceneManager.h"

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
			CGameObject* player = new CGameObject();
			player->FnSetName(L"Zelda");
			FnAddGameObject(eLayerType::Player, player);

			CMeshRenderer* mr = player->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteMaterial"));

			player->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 1.0001f)); // (Vector3(0.0f, 0.0f, 1.0f));
			//player->FnAddComponent<CCameraScript>();
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
		{// Main Camera - [OFF : UI / ON : Player] - Move[O]
			CGameObject* camera = new CGameObject();
			FnAddGameObject(eLayerType::Player, camera);

			camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* cameraComp = camera->FnAddComponent<CCamera>();
			cameraComp->FnTurnLayerMask(eLayerType::UI, false);
			camera->FnAddComponent<CCameraScript>();
		}

		{// UI Camera - [OFF : Player / ON : UI] - Move[X]
			CGameObject* camera = new CGameObject();
			FnAddGameObject(eLayerType::Player, camera);

			camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
			CCamera* cameraComp = camera->FnAddComponent<CCamera>();
			cameraComp->FnTurnLayerMask(eLayerType::Player, false);
			//camera->FnAddComponent<CCameraScript>();
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
		CScene::FnLateUpdate();
	}

	void CPlayScene::FnRender()
	{
		CScene::FnRender();
	}
}
