#include "CShader.h"
#include "CRenderer.h"

namespace yha
{
	CShader::CShader()
		//: mInputLayout(nullptr)
		: CResource(enums::eResourceType::Shader)
		, mInputLayout(nullptr)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
		, mRSType(eRSType::SolidBack)
		, mDSType(eDSType::Less)
		, mBSType(eBSType::AlphaBlend)
	{
	}

	CShader::~CShader()
	{
		mInputLayout->Release();
	}
	HRESULT CShader::FnLoad(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	bool CShader::FnCreate
	(
		const eShaderStage stage
		, const std::wstring& fileName
		, const std::string& funcName
	)
	{
		std::filesystem::path shaderPath
			= std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += fileName;

		ID3DBlob* errorBlob = nullptr;
		if (stage == eShaderStage::VS)
		{
			FnGetDevice()->FnCompileFromfile(fullPath, funcName, "vs_5_0", mVSBlob.GetAddressOf());
			FnGetDevice()->FnCreateVertexShader(
				mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize()
				, mVS.GetAddressOf());
		}
		else if (stage == eShaderStage::PS)
		{
			FnGetDevice()->FnCompileFromfile(fullPath, funcName, "ps_5_0", mPSBlob.GetAddressOf());
			FnGetDevice()->FnCreatePixelShader(
				mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize()
				, mPS.GetAddressOf());
		}

		return true;;
	}
	void CShader::FnBinds()
	{
		FnGetDevice()->FnBindPrimitiveTopology(mTopology);
		FnGetDevice()->FnBindInputLayout(mInputLayout);

		FnGetDevice()->FnBindVertexShader(mVS.Get());
		FnGetDevice()->FnBindPixelShader(mPS.Get());

		Microsoft::WRL::ComPtr<ID3D11RasterizerState> rsState = renderer::rasterizerStates[(UINT)mRSType];
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)mDSType];
		Microsoft::WRL::ComPtr<ID3D11BlendState> bsState = renderer::blendStates[(UINT)mBSType];

		FnGetDevice()->FnBindRasterizeState(rsState.Get());
		FnGetDevice()->FnBindDepthStencilState(dsState.Get());
		FnGetDevice()->FnBindBlendState(bsState.Get());
	}
}