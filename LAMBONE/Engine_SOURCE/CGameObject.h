#pragma once
#include "CEntity.h"
#include "CComponent.h"

namespace yha
{
	class CGameObject : public CEntity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

	public:
		CGameObject();
		virtual ~CGameObject();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();

	private:
		eState mState;
		//std::vector<Component*> mComponents;
		//int y;
		//int x;
	};
}
