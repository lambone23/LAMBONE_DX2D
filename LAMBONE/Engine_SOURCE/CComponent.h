#pragma once
#include "CEntity.h"

namespace yha
{
	using namespace yha::enums;

	class CComponent : public CEntity
	{
	public:
		CComponent();
		~CComponent();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();

	private:
		const eComponentType mType;
	};
}
