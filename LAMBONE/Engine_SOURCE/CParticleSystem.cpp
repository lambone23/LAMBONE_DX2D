#include "CParticleSystem.h"

#include "CTime.h"
#include "CMesh.h"
#include "CMaterial.h"
#include "CResources.h"
#include "CTransform.h"
#include "CGameObject.h"

namespace yha
{
	CParticleSystem::CParticleSystem()
		: mCount(0)
		, mStartSize(Vector4::One)
		, mEndSize(Vector4::One)
		, mStartColor(Vector4::Zero)
		, mEndColor(Vector4::Zero)
		, mLifeTime(0.0f)
		, mTime(0.0f)
	{
		std::shared_ptr<CMesh> mesh = CResources::FnFind<CMesh>(L"PointMesh");
		FnSetMesh(mesh);

		std::shared_ptr<CMaterial> material = CResources::FnFind<CMaterial>(L"ParticleMaterial");
		FnSetMaterial(material);

		mCS = CResources::FnFind<CParticleShader>(L"ParticleSystemShader");

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector4::Zero;
			//pos.x += rand() % 20;
			//pos.y += rand() % 10;

			//int sign = rand() % 2;

			//if (sign == 0)
			//	pos.x *= -1.0f;

			//sign = rand() % 2;

			//if (sign == 0)
			//	pos.y *= -1.0f;

			particles[i].direction =
					Vector4(cosf((float)i * (XM_2PI / (float)1000))
					, sinf((float)i * (XM_2PI / 100.f))
					, 0.0f, 1.0f);

			particles[i].position = pos;
			particles[i].speed = 1.0f;
			particles[i].active = 0;
		}

		mBuffer = new graphics::CStructedBuffer();
		mBuffer->FnCreate(sizeof(Particle), 1000, eViewType::UAV, particles);

		mSharedBuffer = new graphics::CStructedBuffer();
		mSharedBuffer->FnCreate(sizeof(ParticleShared), 1, eViewType::UAV, nullptr, true);

		//ParticleShared shareData = {};
		//shareData.sharedActiveCount = 1000;
		//mSharedBuffer->FnSetData(&shareData, 1);
		//mBuffer->FnSetData(particles, 100);
	}

	CParticleSystem::~CParticleSystem()
	{
		delete mSharedBuffer;
		delete mBuffer;
	}
	void CParticleSystem::FnInitialize()
	{
	}
	void CParticleSystem::FnUpdate()
	{
	}

	void CParticleSystem::FnLateUpdate()
	{
		float AliveTime = 1.0f / 1.0f;

		mTime += CTime::FnDeltaTime();

		if (mTime > AliveTime)
		{
			float f = (mTime / AliveTime);
			UINT AliveCount = (UINT)f;
			mTime = f - floor(f);

			ParticleShared shareData = {};
			shareData.sharedActiveCount = 2;
			mSharedBuffer->FnSetData(&shareData, 1);
		}
		else
		{
			ParticleShared shareData = {};
			shareData.sharedActiveCount = 0;
			mSharedBuffer->FnSetData(&shareData, 1);
		}

		mCS->FnSetParticleBuffer(mBuffer);
		mCS->FnSetSharedBuffer(mSharedBuffer);
		mCS->FnOnExcute();
	}

	void CParticleSystem::FnRender()
	{
		FnGetOwner()->FnGetComponent<CTransform>()->FnBindConstantBuffer();
		mBuffer->FnBindSRV(eShaderStage::VS, 14);
		mBuffer->FnBindSRV(eShaderStage::GS, 14);
		mBuffer->FnBindSRV(eShaderStage::PS, 14);

		FnGetMaterial()->FnBinds();
		FnGetMesh()->FnRenderInstanced(1000);

		mBuffer->FnClear();
	}
}