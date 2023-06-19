#pragma once
#include "CComponent.h"
#include "CMesh.h"

//#include "CShader.h"
#include "CMaterial.h"

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

	public:
		void FnSetMesh(CMesh* mesh) { mMesh = mesh; }
		void FnSetMaterial(CMaterial* material) { mMaterial = material; }

	private:
		CMesh* mMesh;
		
		//CShader* mShader;
		CMaterial* mMaterial;
	};
}
