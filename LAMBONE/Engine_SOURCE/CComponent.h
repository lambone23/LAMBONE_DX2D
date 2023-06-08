#pragma once
#include "CEntity.h"

using namespace yha::math;
namespace yha
{
	using namespace yha::enums;

	class CComponent : public CEntity
	{
	public:
		CComponent(eComponentType Type); //CComponent();
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
