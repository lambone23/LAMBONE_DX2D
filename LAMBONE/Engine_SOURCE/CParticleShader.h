#pragma once
#include "CComputeShader.h"
#include "CStructedBuffer.h"

namespace yha::graphics
{
	class CParticleShader : public CComputeShader
	{
	public:
		CParticleShader();
		~CParticleShader();

	public:
		virtual void FnBinds() override;
		virtual void FnClear() override;

		void FnSetParticleBuffer(CStructedBuffer* particleBuffer);
		void FnSetSharedBuffer(CStructedBuffer* sharedBuffer) { mSharedBuffer = sharedBuffer; }

	private:
		CStructedBuffer* mParticleBuffer;
		CStructedBuffer* mSharedBuffer;
	};
}
