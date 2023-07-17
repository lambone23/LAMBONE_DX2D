#pragma once
#include "CComponent.h"
#include "CTransform.h"

namespace yha
{
	class CCollider2D : public CComponent
	{
	public:
		CCollider2D();
		~CCollider2D();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		void FnOnCollisionEnter(CCollider2D* other);
		void FnOnCollisionStay(CCollider2D* other);
		void FnOnCollisionExit(CCollider2D* other);

		void FnSetType(eColliderType type) { mType = type; }
		void FnSetSize(Vector2 size) { mSize = size; }
		void FnSetCenter(Vector2 size) { mCenter = size; }
		UINT FnGetColliderID() { return mColliderID; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		CTransform* mTransform;

		Vector3 mPosition;
		Vector2 mSize;
		Vector2 mCenter;
	};
}
