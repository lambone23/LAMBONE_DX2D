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
		// 공 움직임 구현



		// 렌더

	}

	void CGameObject::FnLateUpdate()
	{

	}

	void CGameObject::FnRender()
	{
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		renderer::mesh->FnBindBuffer();
		renderer::shader->FnBinds();
		graphics::FnGetDevice()->FnDrawIndexed(renderer::mesh->FnGetIndexCount(), 0, 0);
	}
}
