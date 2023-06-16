#pragma once
#include "CComponent.h"
#include "CMesh.h"
#include "CShader.h"

namespace yha
{
	class CMeshRenderer : public CComponent
	{
	public:
		CMeshRenderer();
		~CMeshRenderer();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	private:
		CMesh* mMesh;
		CShader* mShader;
	};
}
