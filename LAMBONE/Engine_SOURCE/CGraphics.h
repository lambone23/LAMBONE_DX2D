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
		Less,		// 기존보다 앞에 있는 지오메트리를 드로우, 기존과 같은 거리에 있거나 뒤에 있는 지오메트리는 드로우X
		Greater,	// 기존보다 뒤에 있는 지오메트리를 드로우, 기존과 같은 거리에 있거나 앞에 있는 지오메트리는 드로우X
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
		Opaque,			// 불투명 - ex) 일반 솔리드 오브젝트
		CutOut,			// 투명 영역과 불투명 영역 사이에 하드 에지가 있는 투명 효과 - ex) 나뭇잎이나 구멍과 찢어진 부분이 있는 옷감 투명도를 사용할 때 유용
		Transparent,	// ex) 투명한 플라스틱이나 유리
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