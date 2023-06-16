#pragma once
#include "CEntity.h"

namespace yha
{
	using namespace yha::enums;
	using namespace yha::math;

	class CGameObject;
	class CComponent : public CEntity
	{
	public:
		CComponent(eComponentType type);
		~CComponent();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();

	public:
		CGameObject* FnGetOwner() { return mOwner; }
		void FnSetOwner(CGameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		CGameObject* mOwner;
	};
}
