#pragma once
#include "CEntity.h"
#include "CGameObject.h"

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

	private:
		std::vector<CGameObject*> mGameObjects;
	};
}
