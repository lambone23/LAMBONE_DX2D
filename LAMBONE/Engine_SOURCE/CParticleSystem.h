#pragma once
#include "CMeshRenderer.h"
#include "CStructedBuffer.h"
#include "CParticleShader.h"

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
		graphics::CStructedBuffer* mSharedBuffer;

		std::shared_ptr<CParticleShader> mCS;

		UINT	mCount;
		Vector4 mStartSize;
		Vector4 mEndSize;
		Vector4 mStartColor;
		Vector4 mEndColor;
		float	mLifeTime;
		float	mFrequency;
		float	mTime;
	};
}
