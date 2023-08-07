#pragma once
#include "CResource.h"
#include "CGraphics.h"

namespace yha::graphics
{
	class CComputeShader : public CResource
	{
	public:
		CComputeShader(int x, int y, int z);
		CComputeShader();
		virtual ~CComputeShader();

	public:
		bool FnCreate(const std::wstring& name, const std::string& methodName);
		virtual HRESULT FnLoad(const std::wstring& path) { return S_FALSE; };
		void FnOnExcute();

		virtual void FnBinds();
		virtual void FnClear();

	protected:
		Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;

		UINT mThreadGroupCountX;
		UINT mThreadGroupCountY;
		UINT mThreadGroupCountZ;

		UINT mGroupX;
		UINT mGroupY;
		UINT mGroupZ;
	};
}
