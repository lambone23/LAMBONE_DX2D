#pragma once
//#include "CScript.h"
#include <CScript.h>

namespace yha
{
	class CPlayerScript : public CScript
	{
	public:
		CPlayerScript();
		~CPlayerScript();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;

		void FnComplete();

		//virtual void FnOnCollisionEnter(Collider2D* other) override;
		//virtual void FnOnCollisionStay(Collider2D* other) override;
		//virtual void FnOnCollisionExit(Collider2D* other) override;

	private:

	};
}