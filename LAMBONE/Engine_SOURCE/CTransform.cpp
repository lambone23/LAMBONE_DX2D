#include "CTransform.h"
#include "CRenderer.h"
#include "CConstantBuffer.h"

namespace yha
{
	using namespace yha::graphics;
	CTransform::CTransform()
		: CComponent(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
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

	void CTransform::FnLateUpdate()
	{
		//BindConstantBuffer();
	}

	void CTransform::FnRender()
	{

	}

	void CTransform::FnBindConstantBuffer()
	{
		CConstantBuffer* cb = renderer::constantBuffer;
		Vector4 position(mPosition.x, mPosition.y, mPosition.z, 1.0f);
		cb->FnSetData(&position);
		cb->FnBind(eShaderStage::VS);
	}

}
