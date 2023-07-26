#pragma once
#include "CEntity.h"
#include "CGraphics.h"

namespace yha::graphics
{
	class CStructedBuffer : public GpuBuffer
	{
	public:
		CStructedBuffer();
		~CStructedBuffer();

	public:
		bool FnCreate(UINT size, UINT stride, eSRVType type);
		void FnSetData(void* data, UINT stride);
		void FnBind(eShaderStage stage, UINT slot);

		UINT FnGetSize() { return mSize; }
		UINT FnGetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		eSRVType mType;

		UINT mSize;
		UINT mStride;
	};
}
