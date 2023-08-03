#pragma once
#include "CComputeShader.h"

namespace yha::graphics
{
	class CPaintShader : public CComputeShader
	{
	public:
		virtual void FnBinds() override;
		virtual void FnClear() override;

		void FnSetTarget(std::shared_ptr<class CTexture> target) { mTarget = target; }

	private:
		std::shared_ptr<class CTexture> mTarget;
	};
}
