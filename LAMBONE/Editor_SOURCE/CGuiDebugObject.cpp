#include "CGuiDebugObject.h"

namespace gui
{
	CDebugObject::CDebugObject()
	{
	}
	CDebugObject::~CDebugObject()
	{
	}
	void CDebugObject::FnInitialize()
	{
	}
	void CDebugObject::FnUpdate()
	{
	}
	void CDebugObject::FnLateUpdate()
	{
		CGameObject::FnLateUpdate();
	}
	void CDebugObject::FnRender()
	{
		CGameObject::FnRender();
	}
}