#include "CTransform.h"

namespace yha
{
	CTransform::CTransform()
		:CComponent(eComponentType::Transform)
		, mPos(Vector4::Zero)
		, mScale(Vector4::One)
	{
	}
	CTransform::~CTransform()
	{
	}
	void CTransform::FnInitialize()
	{
	}
	void CTransform::FnUpdate()
	{
	}
	void CTransform::FnRender()
	{
	}
	void CTransform::FnLateUpdate()
	{
	}
}
