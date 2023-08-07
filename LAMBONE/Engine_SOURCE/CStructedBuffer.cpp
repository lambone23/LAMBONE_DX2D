#include "CStructedBuffer.h"
#include "CGraphicDevice_Dx11.h"

namespace yha::graphics
{
	CStructedBuffer::CStructedBuffer()
		: GpuBuffer()
		, mType(eViewType::SRV)
		, mSRV(nullptr)
		, mSize(0)
		, mStride(0)
		, mSRVSlot(0)
		, mUAVslot(0)
	{
	}

	CStructedBuffer::~CStructedBuffer()
	{
	}

	bool CStructedBuffer::FnCreate(UINT size, UINT stride, eViewType type, void* data, bool cpuAccess)
	{
		mType = type;

		mSize = size;
		mStride = stride;

		desc.ByteWidth = mSize * mStride;
		desc.StructureByteStride = mSize;

		desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		desc.CPUAccessFlags = 0;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding
		desc.MiscFlags = D3D11_RESOURCE_MISC_FLAG::D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정

		if (mType == eViewType::UAV)
		{
			desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS;	// Texture Register Binding
			desc.CPUAccessFlags = 0;
		}

		if (data)
		{
			D3D11_SUBRESOURCE_DATA tSub = {};
			tSub.pSysMem = data;

			if (!(FnGetDevice()->FnCreateBuffer(buffer.GetAddressOf(), &desc, &tSub)))
				return false;
		}
		else
		{
			if (!(FnGetDevice()->FnCreateBuffer(buffer.GetAddressOf(), &desc, nullptr)))
				return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.BufferEx.NumElements = mStride;
		srvDesc.ViewDimension = D3D_SRV_DIMENSION_BUFFEREX;

		if (!(FnGetDevice()->FnCreateShaderResourceView(buffer.Get(), &srvDesc, mSRV.GetAddressOf())))
		return false;

		if (mType == eViewType::UAV)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
			uavDesc.Buffer.NumElements = mStride;
			uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;

			if (!FnGetDevice()->FnCreateUnordedAccessView(buffer.Get(), &uavDesc, mUAV.GetAddressOf()))
				return false;
		}

		if (cpuAccess)
			FnCreateRWBuffer();

		return true;
	}//END-bool CStructedBuffer::FnCreate

	bool CStructedBuffer::FnCreateRWBuffer()
	{
		D3D11_BUFFER_DESC wDesc(desc);

		wDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정
		wDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding	

		wDesc.Usage = D3D11_USAGE_DYNAMIC;
		wDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		if (!FnGetDevice()->FnCreateBuffer(mWriteBuffer.GetAddressOf(), &wDesc, nullptr))
			return false;

		D3D11_BUFFER_DESC rDesc(desc);

		rDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED; // 구조화 버퍼 추가 플래그 설정
		rDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;	// Texture Register Binding	

		rDesc.Usage = D3D11_USAGE_DEFAULT;
		rDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;

		if (!FnGetDevice()->FnCreateBuffer(mReadBuffer.GetAddressOf(), &rDesc, nullptr))
			return false;

		return true;
	}//END-bool CStructedBuffer::FnCreateRWBuffer

	void CStructedBuffer::FnSetData(void* data, UINT bufferCount)
	{
		if (mStride < bufferCount)
			FnCreate(mSize, bufferCount, mType, data);
		else
			FnGetDevice()->FnBindBuffer(mWriteBuffer.Get(), data, mSize * bufferCount);

		FnGetDevice()->FnCopyResource(buffer.Get(), mWriteBuffer.Get());
	}//END-void CStructedBuffer::FnSetData

	void CStructedBuffer::FnGetData(void* data, UINT size)
	{
		FnGetDevice()->FnCopyResource(mReadBuffer.Get(), buffer.Get());

		if (size == 0)
			FnGetDevice()->FnBindBuffer(mReadBuffer.Get(), data, mSize * mStride);
		else
			FnGetDevice()->FnBindBuffer(mReadBuffer.Get(), data, size);
	}//END-void CStructedBuffer::FnGetData

	void CStructedBuffer::FnBindSRV(eShaderStage stage, UINT slot)
	{
		mSRVSlot = slot;
		FnGetDevice()->FnBindShaderResource(stage, slot, mSRV.GetAddressOf());
	}//END-void CStructedBuffer::FnBindSRV

	void CStructedBuffer::FnBindUAV(UINT slot)
	{
		mUAVslot = slot;
		UINT i = -1;
		FnGetDevice()->FnBindUnorderedAccess(slot, mUAV.GetAddressOf(), &i);
	}//END-void CStructedBuffer::FnBindUAV

	void CStructedBuffer::FnClear()
	{
		// srv clear
		ID3D11ShaderResourceView* srv = nullptr;
		FnGetDevice()->FnBindShaderResource(eShaderStage::VS, mSRVSlot, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::HS, mSRVSlot, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::DS, mSRVSlot, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::GS, mSRVSlot, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::PS, mSRVSlot, &srv);
		FnGetDevice()->FnBindShaderResource(eShaderStage::CS, mSRVSlot, &srv);

		ID3D11UnorderedAccessView* uav = nullptr;
		UINT i = -1;
		FnGetDevice()->FnBindUnorderedAccess(mUAVslot, &uav, &i);

		// uav clear
	}//END-void CStructedBuffer::FnClear
}
