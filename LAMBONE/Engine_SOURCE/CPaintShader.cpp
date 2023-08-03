#include "CPaintShader.h"
#include "CTexture.h"

namespace yha::graphics
{
	void CPaintShader::FnBinds()
	{
		mTarget->FnBindUnorderedAccessViews(0);

		mGroupX = mTarget->FnGetWidth() / mThreadGroupCountX + 1;
		mGroupY = mTarget->FnGetHeight() / mThreadGroupCountY + 1;
		mGroupZ = 1;
	}
	void CPaintShader::FnClear()
	{
		mTarget->FnClearUnorderedAccessViews(0);
	}
}
