#pragma once
#include "CComponent.h"

namespace yha
{
	class CAudioListener : public CComponent
	{
	public:
		CAudioListener();
		~CAudioListener();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
