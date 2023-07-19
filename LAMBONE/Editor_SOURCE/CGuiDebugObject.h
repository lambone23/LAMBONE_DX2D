#pragma once
#include "..\\Engine_SOURCE\\CGameObject.h"

namespace gui
{
	class CDebugObject : public yha::CGameObject
	{
	public:
		CDebugObject();
		~CDebugObject();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
