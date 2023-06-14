#pragma once
#include "ZEngine.h"
#include "CGraphicDevice_Dx11.h"

#include "CMesh.h"
#include "CShader.h"
#include "CConstantBuffer.h"

using namespace yha::math;
namespace renderer
{
	struct Vertex
	{
		Vector4 pos;
		Vector4 color;
	};

	//extern Vertex vertexes[];
	extern vector<Vertex> vertexes;
	extern vector<UINT> indexes;

	//extern ID3D11InputLayout* triangleLayout;
	//extern ID3D11Buffer* triangleBuffer;
	//extern ID3D11Buffer* triangleIdxBuffer;		// 인덱스버퍼
	//extern ID3D11Buffer* triangleConstantBuffer;	// 상수버퍼
	//extern ID3DBlob* errorBlob;
	//extern ID3DBlob* triangleVSBlob;
	//extern ID3D11VertexShader* triangleVSShader;
	//extern ID3DBlob* trianglePSBlob;
	//extern ID3D11PixelShader* trianglePSShader;

	extern yha::CMesh* mesh;
	extern yha::CShader* shader;
	//extern yha::graphics::CConstantBuffer* constantBuffer;
	extern yha::graphics::CConstantBuffer* constantBuffers[];

	void FnInitialize();
	void FnUpdate();
	void FnRelease();
}
