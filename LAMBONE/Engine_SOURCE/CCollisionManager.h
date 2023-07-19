#pragma once
#include "ZEngine.h"

namespace yha
{
#define LAYER_MAX (UINT)eLayerType::End 
	using namespace enums;

	class CCollider2D;

	class CCollisionManager
	{
	public:
		union ColliderID
		{
			struct
			{
				UINT left;
				UINT right;
			};
			UINT64 id;
		};

	public:
		static void FnInitialize();
		static void FnUpdate();
		static void FnLayerCollision(eLayerType left, eLayerType right);
		static void FnColliderCollision(CCollider2D* left, CCollider2D* right);
		static bool FnIntersect(CCollider2D* left, CCollider2D* right);

		static void FnSetLayer(eLayerType left, eLayerType right, bool enable);
		static void FnClear();

	private:

		static std::bitset<LAYER_MAX> mMatrix[LAYER_MAX];
		static std::map<UINT64, bool> mCollisionMap;
	};
}
