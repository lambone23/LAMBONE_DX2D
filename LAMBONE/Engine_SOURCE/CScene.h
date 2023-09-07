#pragma once
#include "CEntity.h"
#include "CLayer.h"

namespace yha
{
	class CScene : public CEntity
	{
	public:
		CScene();
		virtual ~CScene();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();
		virtual void FnRender_Font();
		virtual void FnDestroy();

	public:
		virtual void FnOnEnter();
		virtual void FnOnExit();

		void FnAddGameObject(eLayerType type, CGameObject* gameObj);

		template <typename T>
		std::vector<T*> FnFindObjectsOfType()
		{
			std::vector<T*> findObjs = {};
			for (CLayer* layer : mLayers)
			{
				auto gameObjs = layer->FnGetGameObjects();
				for (CGameObject* obj : gameObjs)
				{
					T* buff = dynamic_cast<T*>(obj);
					if (buff != nullptr)
						findObjs.push_back(buff);
				}
			}

			return findObjs;
		}

		CLayer& FnGetLayer(eLayerType type) { return mLayers[(UINT)type]; }

	private:
		std::vector<CLayer> mLayers;
	};
}
