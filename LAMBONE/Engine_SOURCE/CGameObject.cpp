#include "CGameObject.h"
#include "CRenderer.h"
#include "CGraphicDevice_Dx11.h"
#include "CTransform.h"

namespace yha
{
	CGameObject::CGameObject()
		: mState(eState::Active)
	{
		FnAddComponent<CTransform>();
	}

	CGameObject::~CGameObject()
	{
		for (CComponent* comp : mComponents)
		{
			if (comp == nullptr)
				continue;

			delete comp;
			comp = nullptr;
		}
	}

	void CGameObject::FnInitialize()
	{

	}

	void CGameObject::FnUpdate()
	{
		for (CComponent* comp : mComponents)
		{
			comp->FnUpdate();
		}
	}

	void CGameObject::FnLateUpdate()
	{
		for (CComponent* comp : mComponents)
		{
			comp->FnLateUpdate();
		}
	}

	void CGameObject::FnRender()
	{
		for (CComponent* comp : mComponents)
		{
			comp->FnRender();
		}
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.


	}
}
