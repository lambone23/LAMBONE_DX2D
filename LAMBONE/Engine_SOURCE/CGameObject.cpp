#include "CGameObject.h"
#include "CRenderer.h"
#include "CGraphicDevice_Dx11.h"

namespace yha
{
	CGameObject::CGameObject()
		: mState(eState::Active)
	{
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::FnInitialize()
	{
	}

	void CGameObject::FnUpdate()
	{
		// �� ������ ����



		// ����

	}

	void CGameObject::FnLateUpdate()
	{

	}

	void CGameObject::FnRender()
	{
		//������۷� ��ġ���� ũ������, ����, ������Ʈ ������Ѵ�.

		renderer::mesh->FnBindBuffer();
		renderer::shader->FnBinds();
		graphics::FnGetDevice()->FnDrawIndexed(renderer::mesh->FnGetIndexCount(), 0, 0);
	}
}
