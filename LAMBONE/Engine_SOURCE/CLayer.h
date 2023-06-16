#pragma once
#include "CGameObject.h"

namespace yha
{
	class CLayer
	{
	public:
		CLayer();
		~CLayer();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();

	public:
		void FnAddGameObject(CGameObject* gameObj);

	private:
		std::vector<CGameObject*> mGameObjects;
	};
}
