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
		virtual void FnRender() override;
		//virtual void Release() override;
		virtual void FnLateUpdate() override;

	public:
		void FnSetPos(Vector4 Pos) { mPos = Pos; }
		void FnSetSize(Vector4 Size) { mScale = Size; }
		Vector4 FnGetPos() { return mPos; }
		Vector4 GetScale() { return mScale; }

	private:
		Vector4 mPos;
		Vector4 mScale;

	};
}
