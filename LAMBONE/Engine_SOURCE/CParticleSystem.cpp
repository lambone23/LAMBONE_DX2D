#include "CParticleSystem.h"
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
	{
		std::shared_ptr<CMesh> mesh = CResources::FnFind<CMesh>(L"PointMesh");
		FnSetMesh(mesh);

		std::shared_ptr<CMaterial> material = CResources::FnFind<CMaterial>(L"ParticleMaterial");
		FnSetMaterial(material);

		Particle particles[1000] = {};
		for (size_t i = 0; i < 1000; i++)
		{
			Vector4 pos = Vector4::Zero;
			pos.x += rand() % 20;
			pos.y += rand() % 10;

			int sign = rand() % 2;

			if (sign == 0)
				pos.x *= -1.0f;

			sign = rand() % 2;

			if (sign == 0)
				pos.y *= -1.0f;

			particles[i].position = pos;
			particles[i].active = 1;
		}

		mBuffer = new graphics::CStructedBuffer();
		mBuffer->FnCreate(sizeof(Particle), 1000, eSRVType::None);
		mBuffer->FnSetData(particles, 1000);
	}

	CParticleSystem::~CParticleSystem()
	{
	}
	void CParticleSystem::FnInitialize()
	{
	}
	void CParticleSystem::FnUpdate()
	{
	}
	void CParticleSystem::FnLateUpdate()
	{
	}
	void CParticleSystem::FnRender()
	{
		FnGetOwner()->FnGetComponent<CTransform>()->FnBindConstantBuffer();
		mBuffer->FnBind(eShaderStage::VS, 14);
		mBuffer->FnBind(eShaderStage::GS, 14);
		mBuffer->FnBind(eShaderStage::PS, 14);

		FnGetMaterial()->FnBinds();
		FnGetMesh()->FnRenderInstanced(1000);
	}
}