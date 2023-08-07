#include "CComputeShader.h"
#include "CGraphicDevice_Dx11.h"

namespace yha::graphics
{
	CComputeShader::CComputeShader(int x, int y, int z)
		: CResource(enums::eResourceType::ComputeShader)
	{
		mThreadGroupCountX = x;
		mThreadGroupCountY = y;
		mThreadGroupCountZ = z;
	}

	CComputeShader::CComputeShader()
		: CResource(enums::eResourceType::ComputeShader)
	{
		mThreadGroupCountX = 32;
		mThreadGroupCountY = 32;
		mThreadGroupCountZ = 1;
	}

	CComputeShader::~CComputeShader()
	{
	}

	bool CComputeShader::FnCreate(const std::wstring& name, const std::string& methodName)
	{
		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader_SOURCE\\";

		std::filesystem::path fullPath(shaderPath.c_str());
		fullPath += name;

		ID3DBlob* errorBlob = nullptr;
		graphics::FnGetDevice()->FnCompileFromfile(fullPath, methodName, "cs_5_0", mCSBlob.GetAddressOf());
		
		graphics::FnGetDevice()->FnCreateComputeShader(
			mCSBlob->GetBufferPointer()
			, mCSBlob->GetBufferSize()
			, mCS.GetAddressOf());

		return true;
	}
	//END-CComputeShader::FnCreate

	void CComputeShader::FnOnExcute()
	{
		FnBinds();

		FnGetDevice()->FnBindComputeShader(mCS.Get());
		FnGetDevice()->FnDispatch(mGroupX, mGroupY, mGroupZ);

		FnClear();
	}

	void CComputeShader::FnBinds()
	{
	}

	void CComputeShader::FnClear()
	{
	}
}
