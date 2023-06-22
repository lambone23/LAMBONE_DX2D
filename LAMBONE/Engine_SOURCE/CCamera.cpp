#include "CCamera.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CApplication.h"

extern yha::CApplication MyApplication;

namespace yha
{
	Matrix CCamera::mView = Matrix::Identity;
	Matrix CCamera::mProjection = Matrix::Identity;

	CCamera::CCamera()
		: CComponent(eComponentType::Camera)
		, mType(eProjectionType::OrthoGraphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(5.0f)
	{
	}

	CCamera::~CCamera()
	{
	}

	void CCamera::FnInitialize()
	{
	}

	void CCamera::FnUpdate()
	{
	}

	void CCamera::FnLateUpdate()
	{
		FnCreateViewMatrix();
		FnCreateProjectionMatrix(mType);
	}

	void CCamera::FnRender()
	{
	}

	bool CCamera::FnCreateViewMatrix()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		// View Translate Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// View Rotation Matrix
		Vector3 up = tr->FnUp();
		Vector3 right = tr->FnRight();
		Vector3 foward = tr->FnFoward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = foward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = foward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = foward.z;
		mView *= viewRotate;

		return true;
	}//END-bool CCamera::FnCreateViewMatrix

	bool CCamera::FnCreateProjectionMatrix(eProjectionType type)
	{
		// 종횡비 계산
		RECT rect = {};
		GetClientRect(MyApplication.FnGetHwnd(), &rect);
		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		mAspectRatio = width / height;;

		if (type == eProjectionType::OrthoGraphic)
		{// 2D - 원근감, 공간감 X
			float OrthoGraphicRatio = mSize / 1000.0f;
			width *= OrthoGraphicRatio;
			height *= OrthoGraphicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else // 원근감, 공간감 O
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);

		return true;
	}//END-bool CCamera::FnCreateProjectionMatrix

}
