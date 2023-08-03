#pragma once
#include "CMeshRenderer.h"
#include "CStructedBuffer.h"

namespace yha
{
	class CParticleSystem : public CMeshRenderer
	{
	public:
		CParticleSystem();
		~CParticleSystem();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	private:
		graphics::CStructedBuffer* mBuffer;

		UINT    mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float   mLifeTime;
	};
}
