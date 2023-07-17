#pragma once
#include "CResource.h"
#include "CGraphicDevice_Dx11.h"

//
namespace yha
{
	using namespace graphics;
	class CShader : public CResource
	{
	public:
		CShader();
		~CShader();

	public:
		virtual HRESULT FnLoad(const std::wstring& path) override;

		bool FnCreate(const eShaderStage stage, const std::wstring& fileName, const std::string& funcName);
		void FnBinds();

		ID3DBlob* FnGetVSCode() { return mVSBlob.Get(); }
		ID3D11InputLayout* FnGetInputLayout() { return mInputLayout; }
		ID3D11InputLayout** FnGetInputLayoutAddressOf() { return &mInputLayout; }

		void FnSetRSState(eRSType type) { mRSType = type; }
		void FnSetDSState(eDSType type) { mDSType = type; }
		void FnSetBSState(eBSType type) { mBSType = type; }
		void FnSetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { mTopology = topology; }

	private:
		ID3D11InputLayout* mInputLayout;
		D3D11_PRIMITIVE_TOPOLOGY mTopology;

		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

		eRSType mRSType;
		eDSType mDSType;
		eBSType mBSType;
	};
}
