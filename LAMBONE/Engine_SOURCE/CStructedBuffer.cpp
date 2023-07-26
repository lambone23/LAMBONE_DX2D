#include "CStructedBuffer.h"
#include "CGraphicDevice_Dx11.h"

namespace yha::graphics
{
	CStructedBuffer::CStructedBuffer()
		: mSRV(nullptr)
		, mType(eSRVType::None)
		, mSize(0)
		, mStride(0)
	{
	}

	CStructedBuffer::~CStructedBuffer()
	{
	}

	bool CStructedBuffer::FnCreate(UINT size, UINT stride, eSRVType type)
	{
		mSize = size;
		mStride = stride;

		desc.ByteWidth = mSize * stride;
		desc.StructureByteStride = mSize;

		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;

		if (!FnGetDevice()->FnCreateBuffer(buffer.GetAddressOf(), &desc, nullptr))
			return false;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION::D3D_SRV_DIMENSION_BUFFEREX;

		if (!(FnGetDevice()->FnCreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
			return false;

		return true;
	}//END-bool CStructedBuffer::FnCreate

	void CStructedBuffer::FnSetData(void* data, UINT stride)
	{
		if (mStride < stride)
			FnCreate(mSize, stride, eSRVType::None);
		else
			FnGetDevice()->FnBindBuffer(buffer.Get(), data, mSize * stride);
	}//END-void CStructedBuffer::FnSetData

	void CStructedBuffer::FnBind(eShaderStage stage, UINT slot)
	{
		FnGetDevice()->FnBindShaderResource(stage, slot, mSRV.GetAddressOf());
	}//END-void CStructedBuffer::FnBind
}
