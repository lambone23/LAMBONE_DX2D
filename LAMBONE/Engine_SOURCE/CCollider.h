//#pragma once
//#include "CComponent.h"
//
//namespace yha
//{
//	class CCollider : public CComponent
//	{
//	public:
//		CCollider();
//		~CCollider();
//
//	public:
//		virtual void FnInitialize() override;
//		virtual void FnUpdate() override;
//		virtual void FnRender() override;
//		//virtual void FnRelease() override;
//		virtual void FnLateUpdate() override;
//
//	public:
//		virtual void FnOnCollisionEnter(CCollider* Other);
//		virtual void FnOnCollisionStay(CCollider* Other);
//		virtual void FnOnCollisionExit(CCollider* Other);
//
//		void FnSetCenter(Vector4 Center) { mCenter = Center; };
//		void FnSetSize(Vector4 Size) { mSize = Size; };
//		Vector4 FnGetPos() { return mPos; }
//		Vector4 FnGetSize() { return mSize; }
//		UINT FnGetID() { return mID; }
//
//	private:
//		static UINT ColliderNumber;
//		UINT mCollisionCount;
//		UINT mID;
//		Vector4 mCenter;
//		Vector4 mSize;
//		Vector4 mPos;
//	};
//}
//
