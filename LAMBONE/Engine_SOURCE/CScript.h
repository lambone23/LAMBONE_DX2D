#pragma once
#include "CComponent.h"
#include "CCollider2D.h"

namespace yha
{
	class CScript : public CComponent
	{
	public:
		CScript();
		~CScript();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		virtual void FnOnCollisionEnter(CCollider2D* other);
		virtual void FnOnCollisionStay(CCollider2D* other);
		virtual void FnOnCollisionExit(CCollider2D* other);
	};
}
