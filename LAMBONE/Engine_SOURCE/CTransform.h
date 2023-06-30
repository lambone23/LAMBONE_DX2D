#pragma once
#include "CComponent.h"

namespace yha
{
	class CTransform : public CComponent
	{
	public:
		CTransform();
		~CTransform();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		void FnBindConstantBuffer();

		void FnSetPosition(Vector3 position) { mPosition = position; }
		void FnSetRotation(Vector3 rotation) { mRotation = rotation; }
		void FnSetScale(Vector3 scale) { mScale = scale; }

		void FnSetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void FnSetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void FnSetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }

		Vector3 FnGetPosition() { return mPosition; }
		Vector3 FnGetRotation() { return mRotation; }
		Vector3 FnGetScale() { return mScale; }

		Vector3 FnFoward() { return mFoward; }
		Vector3 FnRight() { return mRight; }
		Vector3 FnUp() { return mUp; }

		void FnSetParent(CTransform* transform) { mParent = transform; }
		CTransform* FnGetParent() { return mParent; }

	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Vector3 mUp;
		Vector3 mFoward;
		Vector3 mRight;

		Matrix mWorld;

		CTransform* mParent;
	};
}
