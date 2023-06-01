#include "CRenderer.h"

#include "CInput.h"
#include "CTime.h"

namespace yha::renderer
{
	//■[HW-230530] - drawing shapes
	//Vertex vertexes[100] = {}; //Vertex vertexes[3] = {};

	//[230531] 인덱스버퍼, 상수버퍼 생성 이후
	Vertex vertexes[24] = {}; //Vertex vertexes[3] = {};

	// Input Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* triangleBuffer = nullptr;

	ID3D11Buffer* triangleIdxBuffer = nullptr;		// 인덱스버퍼
	ID3D11Buffer* triangleConstantBuffer = nullptr;	// 상수버퍼

	Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);

	// error blob
	ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary Code
	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;

	// Pixel Shader code -> Binary Code
	ID3DBlob* trianglePSBlob = nullptr;

	// Vertex Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	void FnSetupState()
	{




	}

	void FnLoadBuffer()
	{
		//-----------------------------
		// Vertex Buffer
		//-----------------------------
		D3D11_BUFFER_DESC triangleDesc = {};
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		//■[HW-230530] - drawing shapes
		//triangleDesc.ByteWidth = sizeof(Vertex) * 100; //triangleDesc.ByteWidth = sizeof(Vertex) * 3;

		//[230531] 인덱스버퍼, 상수버퍼 생성 이후
		triangleDesc.ByteWidth = sizeof(Vertex) * 24; //triangleDesc.ByteWidth = sizeof(Vertex) * 3;

		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		yha::graphics::FnGetDevice()->FnCreateBuffer(&triangleBuffer, &triangleDesc, &triangleData);

		std::vector<UINT> indexes = {};
		//indexes.push_back(0);
		//indexes.push_back(1);
		//indexes.push_back(2);
		for (size_t i = 0; i < 24; i++)
		{
			indexes.push_back(i);
		}

		//-----------------------------
		// Index Buffer
		//-----------------------------
		D3D11_BUFFER_DESC triangleIdxDesc = {};
		triangleIdxDesc.ByteWidth = sizeof(UINT) * indexes.size();
		triangleIdxDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		triangleIdxDesc.Usage = D3D11_USAGE_DEFAULT;
		triangleIdxDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA triangleIdxData = {};
		triangleIdxData.pSysMem = indexes.data();
		yha::graphics::FnGetDevice()->FnCreateBuffer(&triangleIdxBuffer, &triangleIdxDesc, &triangleIdxData);

		//-----------------------------
		// Constant Buffer
		//-----------------------------
		D3D11_BUFFER_DESC triangleCSDesc = {};
		triangleCSDesc.ByteWidth = sizeof(Vector4);
		triangleCSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		triangleCSDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleCSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		yha::graphics::FnGetDevice()->FnCreateBuffer(&triangleConstantBuffer, &triangleCSDesc, nullptr);

		//Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f); //Vector4 pos(0.3f, 0.0f, 0.0f, 1.0f);
		//yha::graphics::FnGetDevice()->FnSetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		//yha::graphics::FnGetDevice()->FnBindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);

	}

	void FnLoadShader()
	{
		yha::graphics::FnGetDevice()->FnCreateShader();
	}

	void FnInitialize()
	{
		//■[HW-230530] - drawing shapes

		// triangle // 3
		vertexes[0].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		// square // 6
		vertexes[3].pos = Vector3(-0.5f, 0.5f, 0.0f); // RT
		vertexes[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[4].pos = Vector3(-0.5f, 0.0f, 0.0f); // RB
		vertexes[4].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[5].pos = Vector3(-0.75f, 0.0f, 0.0f); //LB
		vertexes[5].color = Vector4(.0f, 0.0f, 1.0f, 1.0f);

		vertexes[6].pos = Vector3(-0.5f, 0.5f, 0.0f); // RT
		vertexes[6].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[7].pos = Vector3(-0.75f, 0.0f, 0.0f); // LB
		vertexes[7].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[8].pos = Vector3(-0.75f, 0.5f, 0.0f); // LT
		vertexes[8].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		// rhombus // 6
		vertexes[9].pos = Vector3(0.5f, 0.75f, 0.0f); // T
		vertexes[9].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[10].pos = Vector3(0.9f, 0.5f, 0.0f); // R
		vertexes[10].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[11].pos = Vector3(0.5f, 0.25f, 0.0f); //B
		vertexes[11].color = Vector4(.0f, 0.0f, 1.0f, 1.0f);

		vertexes[12].pos = Vector3(0.5f, 0.75f, 0.0f); // T
		vertexes[12].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[13].pos = Vector3(0.5f, 0.25f, 0.0f); // B
		vertexes[13].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[14].pos = Vector3(0.1f, 0.5f, 0.0f); // LT
		vertexes[14].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		// pentagon // 9
		vertexes[15].pos = Vector3(0.75f, 0.25f, 0.0f); // T
		vertexes[15].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[16].pos = Vector3(0.9f, 0.10f, 0.0f); // RT
		vertexes[16].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[17].pos = Vector3(0.85f, -0.2f, 0.0f); // RB
		vertexes[17].color = Vector4(.0f, 0.0f, 1.0f, 1.0f);

		vertexes[18].pos = Vector3(0.75f, 0.25f, 0.0f); // T
		vertexes[18].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		vertexes[19].pos = Vector3(0.85f, -0.2f, 0.0f); // RB
		vertexes[19].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[20].pos = Vector3(0.65f, -0.2f, 0.0f); // LB
		vertexes[20].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[21].pos = Vector3(0.75f, 0.25f, 0.0f); // T
		vertexes[21].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		vertexes[22].pos = Vector3(0.65f, -0.2f, 0.0f); // LB
		vertexes[22].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[23].pos = Vector3(0.6f, 0.10f, 0.0f); // LT
		vertexes[23].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);


		FnSetupState();
		FnLoadBuffer();
		FnLoadShader();
	}

	void FnUpdate()
	{

		//if (CInput::FnGetKeyState(eKeyCode::UP) == eKeyState::Down)
		//{
		//}
		//if (CInput::FnGetKeyDown(eKeyCode::RIGHT))
		//{
		//}
		if (CInput::FnGetKey(eKeyCode::RIGHT))
			pos += Vector4(0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::LEFT))
			pos += Vector4(-0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::UP))
			pos += Vector4(0.0f, 0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::DOWN))
			pos += Vector4(0.0f, -0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);

		yha::graphics::FnGetDevice()->FnSetConstantBuffer(triangleConstantBuffer, &pos, sizeof(Vector4));
		yha::graphics::FnGetDevice()->FnBindConstantBuffer(eShaderStage::VS, eCBType::Transform, triangleConstantBuffer);
			
	}
}



