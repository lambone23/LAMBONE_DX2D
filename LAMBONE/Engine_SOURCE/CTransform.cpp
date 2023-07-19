#include "CTransform.h"
#include "CRenderer.h"
#include "CConstantBuffer.h"
#include "CCamera.h"

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
		// 이동 회전 크기 변경
	}

	void CTransform::FnLateUpdate()
	{
		//BindConstantBuffer();

		mWorld = Matrix::Identity;

		Matrix scale = Matrix::CreateScale(mScale);

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position;
		position.Translation(mPosition);

		mWorld = scale * rotation * position;

		mUp		= Vector3::TransformNormal(Vector3::Up, rotation);
		mFoward	= Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight	= Vector3::TransformNormal(Vector3::Right, rotation);

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
	}

	void CTransform::FnRender()
	{

	}

	void CTransform::FnBindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.mWorld = mWorld;

		//trCB.mView = mWorld;
		trCB.mView = CCamera::FnGetGpuViewMatrix();
		 
		//trCB.mProjection = mWorld;
		trCB.mProjection = CCamera::FnGetGpuProjectionMatrix();

		//CConstantBuffer* cb = renderer::constantBuffer;
		CConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		
		Vector4 position(mPosition.x, mPosition.y, mPosition.z, 1.0f);
		
		//cb->FnSetData(&position);
		cb->FnSetData(&trCB);

		cb->FnBind(eShaderStage::VS);
	}

}
