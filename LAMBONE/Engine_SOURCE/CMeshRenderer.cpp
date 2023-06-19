#include "CMeshRenderer.h"
#include "CGameObject.h"
#include "CTransform.h"
#include "CRenderer.h"

namespace yha
{
	CMeshRenderer::CMeshRenderer()
		: CComponent(eComponentType::MeshRenderer)
	{
	}
	CMeshRenderer::~CMeshRenderer()
	{
	}
	void CMeshRenderer::FnInitialize()
	{
	}
	void CMeshRenderer::FnUpdate()
	{
	}
	void CMeshRenderer::FnLateUpdate()
	{
	}
	void CMeshRenderer::FnRender()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		tr->FnBindConstantBuffer();

		////mMesh->BindBuffer();
		////mShader->Binds();

		//renderer::mesh->FnBindBuffer();
		//renderer::shader->FnBinds();
		//FnGetDevice()->FnDrawIndexed(renderer::mesh->FnGetIndexCount(), 0, 0);

		mMesh->FnBindBuffer();
		mMaterial->FnBinds();
		mMesh->FnRender();
	}
}
