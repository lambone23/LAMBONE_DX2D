#pragma once
#include "CLayer.h"
#include "CGameObject.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CTransform.h"

namespace yha::object
{
	template <typename T>
	static __forceinline T* FnInstantiate(enums::eLayerType layer)
	{
		T* gameObj = new T();
		CScene* scene = CSceneManager::FnGetActiveScene();
		scene->FnAddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* FnInstantiate(Vector3 pos, enums::eLayerType layer)
	{
		T* gameObj = new T();
		CTransform* tr = gameObj->FnGetComponent<CTransform>();
		tr->FnSetPosition(pos);

		CScene* scene = CSceneManager::FnGetActiveScene();
		scene->FnAddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* FnInstantiate(Vector3 pos, Vector3 rotate, enums::eLayerType layer)
	{
		T* gameObj = new T();
		CTransform* tr = gameObj->FnGetComponent<CTransform>();
		tr->FnSetPosition(pos);
		tr->FnSetRotation(rotate);

		CScene* scene = CSceneManager::FnGetActiveScene();
		scene->FnAddGameObject(layer, gameObj);

		return gameObj;
	}

	template <typename T>
	static __forceinline T* FnInstantiate(Vector3 pos, Vector3 rotate, Vector3 scale, enums::eLayerType layer)
	{
		T* gameObj = new T();
		CTransform* tr = gameObj->FnGetComponent<CTransform>();
		tr->FnSetPosition(pos);
		tr->FnSetRotation(rotate);
		tr->FnSetScale(scale);

		CScene* scene = CSceneManager::FnGetActiveScene();
		scene->FnAddGameObject(layer, gameObj);

		return gameObj;
	}

	static __forceinline void FnDestroy(CGameObject* gameObj)
	{
		gameObj->FnSetState(yha::CGameObject::eState::Dead);
	}
}