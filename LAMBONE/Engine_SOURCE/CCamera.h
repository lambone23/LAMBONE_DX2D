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

		static Matrix FnGetViewMatrix() { return View; }
		static Matrix FnGetProjectionMatrix() { return Projection; }

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

		void FnRenderOpaque();			// ������ - ex) �Ϲ� �ָ��� ������Ʈ
		void FnRenderCutOut();			// ���� ������ ������ ���� ���̿� �ϵ� ������ �ִ� ���� ȿ�� - ex) �������̳� ���۰� ������ �κ��� �ִ� �ʰ� ������ ����� �� ����
		void FnRenderTransparent();		// ex) ������ �ö�ƽ�̳� ����

		void FnEnableDepthStencilState();
		void FnDisableDepthStencilState();

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