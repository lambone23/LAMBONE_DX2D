#pragma once
#include "CGraphics.h"

namespace yha::graphics
{
	class CConstantBuffer : public GpuBuffer
	{
	public:
		CConstantBuffer(const eCBType type);
		~CConstantBuffer();

	public:
		bool FnCreate(size_t size);
		void FnSetData(void* data);
		void FnBind(eShaderStage stage);

	private:
		const eCBType mType;
	};
}
