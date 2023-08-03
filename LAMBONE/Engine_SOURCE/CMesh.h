#pragma once
#include "CResource.h"
#include "CGraphicDevice_Dx11.h"

namespace yha
{
	using namespace graphics;

	class CMesh : public CResource
	{
	public:
		CMesh();
		~CMesh();

	public:
		virtual HRESULT FnLoad(const std::wstring& path) override;

		bool FnCreateVertexBuffer(void* data, UINT Count);
		bool FnCreateIndexBuffer(void* data, UINT Count);

		void FnBindBuffer(); //Buffer 파이프라인에 묶어준다.
		void FnRender();
		void FnRenderInstanced(UINT startIndexLocation);

		UINT FnGetIndexCount() { return mIndexCount; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;

		D3D11_BUFFER_DESC mVBDesc;
		D3D11_BUFFER_DESC mIBDesc;

		UINT mIndexCount;
	};
}
