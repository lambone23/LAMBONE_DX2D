#include "CConstantBuffer.h"
#include "CGraphicDevice_Dx11.h"

namespace yha::graphics
{
	CConstantBuffer::CConstantBuffer(const eCBType type)
		: GpuBuffer()
		, mType(type)
	{

	}

	CConstantBuffer::~CConstantBuffer()
	{
	}

	bool CConstantBuffer::FnCreate(size_t size)
	{
		desc.ByteWidth = size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		yha::graphics::FnGetDevice()->FnCreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return false;
	}

	void CConstantBuffer::FnSetData(void* data)
	{
		yha::graphics::FnGetDevice()->FnSetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}

	void CConstantBuffer::FnBind(eShaderStage stage)
	{
		yha::graphics::FnGetDevice()->FnBindConstantBuffer(stage, mType, buffer.Get());
	}

}
