#include "CParticleShader.h"
#include "CRenderer.h"
#include "CConstantBuffer.h"
#include "CTime.h"

namespace yha::graphics
{
	CParticleShader::CParticleShader()
		: CComputeShader(128, 1, 1)
		, mParticleBuffer(nullptr)
	{
	}

	CParticleShader::~CParticleShader()
	{
	}

	void CParticleShader::FnBinds()
	{
		mParticleBuffer->FnBindUAV(0);
		mSharedBuffer->FnBindUAV(1);

		mGroupX = mParticleBuffer->FnGetStride() / mThreadGroupCountX + 1;
		mGroupY = 1;
		mGroupZ = 1;
	}

	void CParticleShader::FnClear()
	{
		mParticleBuffer->FnClear();
		mSharedBuffer->FnClear();
	}

	void CParticleShader::FnSetParticleBuffer(CStructedBuffer* particleBuffer)
	{
		mParticleBuffer = particleBuffer;

		CConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Particle];

		static float elapsedTime = 0.0f;
		elapsedTime += CTime::FnDeltaTime();

		renderer::ParticleCB data = {};
		data.elementCount = mParticleBuffer->FnGetStride();
		data.elpasedTime = CTime::FnDeltaTime();

		cb->FnSetData(&data);
		cb->FnBind(eShaderStage::CS);
	}//END-void CParticleShader::FnSetParticleBuffer
}
