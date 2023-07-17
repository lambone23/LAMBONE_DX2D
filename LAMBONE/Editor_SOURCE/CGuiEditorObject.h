#pragma once
#include "..\\Engine_SOURCE\\CGameObject.h"

namespace gui
{
	class CEditorObject : public yha::CGameObject
	{
	public:
		CEditorObject();
		virtual ~CEditorObject();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}