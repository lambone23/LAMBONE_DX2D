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

	public:
		virtual void FnOnEnter();
		virtual void FnOnExit();

		void FnAddGameObject(eLayerType type, CGameObject* gameObj);

	private:
		std::vector<CLayer> mLayers;
	};
}
