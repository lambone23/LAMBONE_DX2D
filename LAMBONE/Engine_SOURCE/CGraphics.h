#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "CEnums.h"
#include "CMath.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name 

#define CBSLOT_TRANSFORM		0
#define CBSLOT_GRID				2
#define CBSLOT_ANIMATION2D		3
//#define CBSLOT_PARTICLE			1

namespace yha::graphics
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		End,
	};

	// Constant Buffer
	enum class eCBType
	{
		Transform,
		Material,
		Grid,
		Animator,
		End,
	};

	enum class eSamplerType
	{
		Point,
		Anisotropic,
		End,
	};

	// Rasterizer State
	enum class eRSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		End,
	};

	// Depth Stencil State
	enum class eDSType
	{
		Less,		// �������� �տ� �ִ� ������Ʈ���� ��ο�, ������ ���� �Ÿ��� �ְų� �ڿ� �ִ� ������Ʈ���� ��ο�X
		Greater,	// �������� �ڿ� �ִ� ������Ʈ���� ��ο�, ������ ���� �Ÿ��� �ְų� �տ� �ִ� ������Ʈ���� ��ο�X
		NoWrite,
		None,
		End,
	};

	// Blend State
	enum class eBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		End,
	};

	enum class eRenderingMode
	{
		Opaque,			// ������ - ex) �Ϲ� �ָ��� ������Ʈ
		CutOut,			// ���� ������ ������ ���� ���̿� �ϵ� ������ �ִ� ���� ȿ�� - ex) �������̳� ���۰� ������ �κ��� �ִ� �ʰ� ������ ����� �� ����
		Transparent,	// ex) ������ �ö�ƽ�̳� ����
		End,
	};

	enum class eSRVType
	{
		None,
		End,
	};

	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;
		enums::eColor color;

		float radius;
		float duration;
		float time;

		//bool isCollide;
	};

	struct LightAttribute
	{
		math::Vector4 color;
		math::Vector4 position;
		math::Vector4 direction;

		enums::eLightType type;
		float radius;
		float angle;
		int pad;
	};
}