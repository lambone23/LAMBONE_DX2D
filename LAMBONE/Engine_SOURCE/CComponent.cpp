#include "CComponent.h"


namespace yha
{
	CComponent::CComponent(eComponentType Type)
		: mType(eComponentType::End)
	{

	}

	CComponent::~CComponent()
	{
	}
	void CComponent::FnInitialize()
	{
	}
	void CComponent::FnUpdate()
	{
	}
	void CComponent::FnLateUpdate()
	{
	}
	void CComponent::FnRender()
	{
	}
}