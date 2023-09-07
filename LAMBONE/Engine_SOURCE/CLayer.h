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
		virtual void FnRender_Font();
		virtual void FnDestory();

	public:
		void FnAddGameObject(CGameObject* gameObj);
		const std::vector<CGameObject*> FnGetGameObjects() { return mGameObjects; }

	private:
		std::vector<CGameObject*> mGameObjects;
	};
}
