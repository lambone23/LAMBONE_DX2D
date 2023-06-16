#include "CScene.h"

namespace yha
{
	CScene::CScene()
	{
		mLayers.resize((int)yha::enums::eLayerType::End);
	}
	CScene::~CScene()
	{

	}

	void CScene::FnInitialize()
	{

	}

	void CScene::FnUpdate()
	{
		for (CLayer& layer : mLayers)
		{
			layer.FnUpdate();
		}
	}

	void CScene::FnLateUpdate()
	{
		for (CLayer& layer : mLayers)
		{
			layer.FnLateUpdate();
		}
	}
	void CScene::FnRender()
	{
		for (CLayer& layer : mLayers)
		{
			layer.FnRender();
		}
	}
	void CScene::FnAddGameObject(eLayerType type, CGameObject* gameObj)
	{
		mLayers[(int)type].FnAddGameObject(gameObj);
	}
}
