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
		void FnSetMesh(std::shared_ptr<CMesh> mesh) { mMesh = mesh; }
		void FnSetMaterial(std::shared_ptr<CMaterial> material) { mMaterial = material; }
		std::shared_ptr<CMaterial> FnGetMaterial() { return mMaterial; }

	private:
		std::shared_ptr<CMesh> mMesh;
		
		//CShader* mShader;
		std::shared_ptr<CMaterial> mMaterial;
	};
}
