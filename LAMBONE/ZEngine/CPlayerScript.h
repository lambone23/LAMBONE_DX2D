#pragma once
//#include "CScript.h"
#include <CScript.h>

namespace yha
{
	class CPlayerScript : public CScript
	{
	public:
		virtual void FnUpdate() override;

		//virtual void FnOnCollisionEnter(Collider2D* other) override;
		//virtual void FnOnCollisionStay(Collider2D* other) override;
		//virtual void FnOnCollisionExit(Collider2D* other) override;

	private:

	};
}