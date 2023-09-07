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
	void CScene::FnRender_Font()
	{
		for (CLayer& layer : mLayers)
		{
			layer.FnRender_Font();
		}
	}
	void CScene::FnDestroy()
	{
		for (CLayer& layer : mLayers)
		{
			layer.FnDestory();
		}
	}
	void CScene::FnOnEnter()
	{
	}
	void CScene::FnOnExit()
	{
	}
	void CScene::FnAddGameObject(eLayerType type, CGameObject* gameObj)
	{
		mLayers[(int)type].FnAddGameObject(gameObj);
	}
}
