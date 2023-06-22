#pragma once
#include "CComponent.h"
#include "CGraphics.h"

namespace yha
{
	class CCamera : public CComponent
	{
	public:
		CCamera();
		~CCamera();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		enum class eProjectionType
		{
			Perpective,
			OrthoGraphic,
			None,
		};

		static Matrix FnGetViewMatrix() { return mView; }
		static Matrix FnGetProjectionMatrix() { return mProjection; }

		bool FnCreateViewMatrix();
		bool FnCreateProjectionMatrix(eProjectionType type);

	private:
		static Matrix mView;
		static Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;
	};
}