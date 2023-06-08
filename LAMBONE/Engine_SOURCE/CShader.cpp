#include "CShader.h"

namespace yha
{
	CShader::CShader()
		: mInputLayout(nullptr)
		, mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
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
			FnGetDevice()->FnCreateVertexShader(mVSBlob->GetBufferPointer()
				, mVSBlob->GetBufferSize(), mVS.GetAddressOf());
		}
		else if (stage == eShaderStage::PS)
		{
			FnGetDevice()->FnCompileFromfile(fullPath, funcName, "ps_5_0", mPSBlob.GetAddressOf());
			FnGetDevice()->FnCreatePixelShader(mPSBlob->GetBufferPointer()
				, mPSBlob->GetBufferSize(), mPS.GetAddressOf());
		}

		return true;;
	}
	void CShader::FnBinds()
	{
		FnGetDevice()->FnBindPrimitiveTopology(mTopology);
		FnGetDevice()->FnBindInputLayout(mInputLayout);

		FnGetDevice()->FnBindVertexShader(mVS.Get());
		FnGetDevice()->FnBindPixelShader(mPS.Get());
	}
}