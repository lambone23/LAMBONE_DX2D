#include "CMesh.h"
#include "CRenderer.h"

namespace yha
{
	CMesh::CMesh()
		: mVertexBuffer(nullptr)
		, mIndexBuffer(nullptr)
		, mVBDesc{}
		, mIBDesc{}
		, mIndexCount(0)
	{
	}

	CMesh::~CMesh()
	{
	}

	HRESULT CMesh::FnLoad(const std::wstring& path)
	{
		return E_NOTIMPL;
	}

	bool CMesh::FnCreateVertexBuffer(void* data, UINT Count)
	{
		mVBDesc.ByteWidth = sizeof(renderer::Vertex) * Count;
		mVBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mVBDesc.CPUAccessFlags = 0; // NONE

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;

		if (!FnGetDevice()->FnCreateBuffer(mVertexBuffer.GetAddressOf(), &mVBDesc, &sub))
			return false;

		return true;
	}

	bool CMesh::FnCreateIndexBuffer(void* data, UINT Count)
	{
		mIndexCount = Count;
		mIBDesc.ByteWidth = sizeof(UINT) * Count;
		mIBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		mIBDesc.CPUAccessFlags = 0; // NONE

		D3D11_SUBRESOURCE_DATA sub = {};
		sub.pSysMem = data;

		if (!FnGetDevice()->FnCreateBuffer(mIndexBuffer.GetAddressOf(), &mIBDesc, &sub))
			return false;

		return true;
	}

	void CMesh::FnBindBuffer()
	{
		UINT stride = sizeof(renderer::Vertex);
		UINT offset = 0;

		FnGetDevice()->FnBindVertexBuffer(0, mVertexBuffer.GetAddressOf(), &stride, &offset);
		FnGetDevice()->FnBindIndexBuffer(mIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	}
}
