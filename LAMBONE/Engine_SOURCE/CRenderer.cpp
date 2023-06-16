#include "CRenderer.h"

namespace renderer
{
	using namespace yha;
	using namespace yha::graphics;

	Vertex vertexes[4] = {};
	yha::CMesh* mesh = nullptr;
	yha::CShader* shader = nullptr;
	yha::graphics::CConstantBuffer* constantBuffer = nullptr;

	void FnSetupState()
	{
		// Input layout 정점 구조 정보를 넘겨줘야한다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		yha::graphics::FnGetDevice()->FnCreateInputLayout(
			arrLayout
			, 2
			, shader->FnGetVSCode()
			, shader->FnGetInputLayoutAddressOf());

	}

	void FnLoadBuffer()
	{
		//==================================================================
		// Vertex Buffer
		//==================================================================
		//D3D11_BUFFER_DESC triangleDesc = {};
		//triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		////■[HW-230530] - drawing shapes
		////triangleDesc.ByteWidth = sizeof(Vertex) * 100; //triangleDesc.ByteWidth = sizeof(Vertex) * 3;

		////[230531] 인덱스버퍼, 상수버퍼 생성 이후
		//triangleDesc.ByteWidth = sizeof(Vertex) * 24; //triangleDesc.ByteWidth = sizeof(Vertex) * 3;

		//triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		//triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		//D3D11_SUBRESOURCE_DATA triangleData = {};
		//triangleData.pSysMem = vertexes;
		//yha::graphics::FnGetDevice()->FnCreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		//std::vector<UINT> indexes = {};
		////indexes.push_back(0);
		////indexes.push_back(1);
		////indexes.push_back(2);
		//for (size_t i = 0; i < 24; i++)
		//{
		//	indexes.push_back(i);
		//}

		mesh = new yha::CMesh();
		mesh->FnCreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		//==================================================================
		// Index Buffer
		//==================================================================
		//D3D11_BUFFER_DESC triangleIdxDesc = {};
		//triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size();
		//triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		//triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;
		//triangleIdxDesc.CPUAccessFlags = 0;

		//D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		//triangleIdxData.pSysMem = indexes.data();
		//yha::graphics::FnGetDevice()->FnCreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		mesh->FnCreateIndexBuffer(indexes.data(), indexes.size());

		//==================================================================
		// Constant Buffer
		//==================================================================
		//D3D11_BUFFER_DESC triangleCSDesc = {};
		//triangleCSDesc.ByteWidth = sizeof(Vector4);
		//triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		//triangleCSDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		//triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		//yha::graphics::FnGetDevice()->FnCreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		////Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f); //Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);
		////yha::graphics::FnGetDevice()->FnSetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		////yha::graphics::FnGetDevice()->FnBindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);

		constantBuffer = new CConstantBuffer(eCBType::Transform);
		constantBuffer->FnCreate(sizeof(Vector4));

		//Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
		//constantBuffer->FnSetData(&pos);
		//constantBuffer->FnBind(eShaderStage::VS);
	}

	void FnLoadShader()
	{
		//yha::graphics::FnGetDevice()->FnCreateShader();

		shader = new yha::CShader();
		shader->FnCreate(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->FnCreate(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void FnInitialize()
	{
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		FnLoadBuffer();
		FnLoadShader();
		FnSetupState();
	}

	void FnRelease()
	{
		delete mesh;
		delete shader;
		delete constantBuffer;
	}
}
























