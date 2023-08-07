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
		bool FnCreate(UINT size, UINT stride, eViewType type, void* data, bool cpuAccess = false);
		bool FnCreateRWBuffer();
		//void FnSetData(void* data, UINT stride);
		void FnSetData(void* data, UINT bufferCount);
		void FnGetData(void* data, UINT size);
		void FnBindSRV(eShaderStage stage, UINT slot);
		void FnBindUAV(UINT slot);

		void FnClear();

		UINT FnGetSize() { return mSize; }
		UINT FnGetStride() { return mStride; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mReadBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mWriteBuffer;

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
		Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> mUAV;
		eViewType mType;

		UINT mSize;
		UINT mStride;

		UINT mSRVSlot;
		UINT mUAVslot;
	};
}
