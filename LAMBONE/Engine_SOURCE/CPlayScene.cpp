#include "CPlayScene.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CMesh.h"
#include "CCameraScript.h"
#include "CCamera.h"

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
		{
			CGameObject* player = new CGameObject();
			FnAddGameObject(eLayerType::Player, player);

			CMeshRenderer* mr = player->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteMaterial"));

			player->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, 0.0f));
			//player->FnAddComponent<CCameraScript>();
		}

		{
			CGameObject* player = new CGameObject();
			FnAddGameObject(eLayerType::Player, player);

			CMeshRenderer* mr = player->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteMaterial02"));

			player->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.0f, 0.0f, 0.0f));
			//player->AddComponent<CameraScript>();
		}

		//Main Camera
		CGameObject* camera = new CGameObject();
		FnAddGameObject(eLayerType::Player, camera);
		
		camera->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.0f, 0.0f, -10.0f));
		CCamera* cameraComp = camera->FnAddComponent<CCamera>();
		camera->FnAddComponent<CCameraScript>();

		//GameObject* player2 = new GameObject();
		//AddGameObject(eLayerType::Player, player2);
		//player2->AddComponent<MeshRenderer>();

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