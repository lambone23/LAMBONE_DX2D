#pragma once
#include "CComponent.h"
#include "CGraphics.h"

namespace yha
{
	class CCamera : public CComponent
	{
	public:
		CCamera();
		~CCamera();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		enum class eProjectionType
		{
			Perpective,
			OrthoGraphic,
			None,
		};

		static Matrix& FnGetGpuViewMatrix() { return View; }
		static void FnSetGpuViewMatrix(Matrix view) { View = view; }

		static Matrix& FnGetGpuProjectionMatrix() { return Projection; }
		static void FnSetGpuProjectionMatrix(Matrix projection) { Projection = projection; }

		bool FnCreateViewMatrix();
		bool FnCreateProjectionMatrix(eProjectionType type);

		void FnRegisterCameraInRenderer();

		void FnTurnLayerMask(eLayerType type, bool enable = true);
		void FnEnableLayerMasks() { mLayerMask.set(); }
		void FnDisableLayerMasks() { mLayerMask.reset(); }

		//void FnSortGameObjects();
		void FnAlphaSortGameObjects();
		void FnZSortTransparencyGameObjects();
		void FnDivideAlphaBlendGameObjects(const std::vector<CGameObject*> gameObjs);

		void FnRenderOpaque();			// 불투명 - ex) 일반 솔리드 오브젝트
		void FnRenderCutOut();			// 투명 영역과 불투명 영역 사이에 하드 에지가 있는 투명 효과 - ex) 나뭇잎이나 구멍과 찢어진 부분이 있는 옷감 투명도를 사용할 때 유용
		void FnRenderTransparent();		// ex) 투명한 플라스틱이나 유리

		void FnEnableDepthStencilState();
		void FnDisableDepthStencilState();

		float FnGetSize() { return mSize; }
		Matrix& FnGetViewMatrix() { return mView; }
		Matrix& FnGetProjectionMatrix() { return mProjection; }

	private:
		static Matrix View;
		static Matrix Projection;

		Matrix mView;
		Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;

		std::bitset<(UINT)eLayerType::End> mLayerMask;
		std::vector<CGameObject*> mOpaqueGameObjects;
		std::vector<CGameObject*> mCutOutGameObjects;
		std::vector<CGameObject*> mTransparentGameObjects;
	};
}