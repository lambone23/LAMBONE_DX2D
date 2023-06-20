#pragma once
#include "CComponent.h"

namespace yha
{
	class CScript : public CComponent
	{
	public:
		CScript();
		~CScript();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	private:

	};
}
