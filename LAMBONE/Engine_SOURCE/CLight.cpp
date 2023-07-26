#include "CLight.h"
#include "CRenderer.h"
#include "CTransform.h"
#include "CGameObject.h"

namespace yha
{
	CLight::CLight()
		: CComponent(eComponentType::Light)
	{
	}
	CLight::~CLight()
	{
	}
	void CLight::FnInitialize()
	{
	}
	void CLight::FnUpdate()
	{
	}
	void CLight::FnLateUpdate()
	{
		renderer::lights.push_back(this);

		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();
		mAttribute.position = Vector4(pos.x, pos.y, pos.z, 1.0f);
		mAttribute.direction = Vector4(tr->FnFoward().x, tr->FnFoward().y, tr->FnFoward().z, 1.0f);
	}

	void CLight::FnRender()
	{

	}
}
