#include "CScript.h"

#include "../Engine_SOURCE/CGameObject.h"
#include "../Engine_SOURCE/CConstantBuffer.h"
#include "../Engine_SOURCE/CRenderer.h"

namespace yha
{
	CScript::CScript()
		: CComponent(enums::eComponentType::Script)
	{
	}

	CScript::~CScript()
	{
	}

	void CScript::FnInitialize()
	{
	}

	void CScript::FnUpdate()
	{
	}

	void CScript::FnLateUpdate()
	{
	}

	void CScript::FnRender()
	{
	}

	void CScript::FnOnCollisionEnter(CCollider2D* other)
	{
		//FnGetOwner()->FnGetComponent<CCollider2D>()->FnSetRectColor(eColor::Red);
	}

	void CScript::FnOnCollisionStay(CCollider2D* other)
	{
		
	}

	void CScript::FnOnCollisionExit(CCollider2D* other)
	{
		//FnGetOwner()->FnGetComponent<CCollider2D>()->FnSetRectColor(eColor::Green);
	}
}