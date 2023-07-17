#include "CCamera.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CApplication.h"
#include "CRenderer.h"
#include "CScene.h"
#include "CSceneManager.h"
#include "CMeshRenderer.h"

extern yha::CApplication MyApplication;

namespace yha
{

	bool FnCompareZSort(CGameObject* a, CGameObject* b)
	{ // ��������
		if (a->FnGetComponent<CTransform>()->FnGetPosition().z
			< b->FnGetComponent<CTransform>()->FnGetPosition().z)
			return false;

		return true;
	}

	Matrix CCamera::View = Matrix::Identity;
	Matrix CCamera::Projection = Matrix::Identity;

	CCamera::CCamera()
		: CComponent(eComponentType::Camera)
		, mType(eProjectionType::OrthoGraphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(5.0f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentGameObjects{}
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
	{
		FnEnableLayerMasks();
	}

	CCamera::~CCamera()
	{
	}

	void CCamera::FnInitialize()
	{
	}

	void CCamera::FnUpdate()
	{
	}

	void CCamera::FnLateUpdate()
	{
		FnCreateViewMatrix();
		FnCreateProjectionMatrix(mType);
		
		FnRegisterCameraInRenderer();
	}

	void CCamera::FnRender()
	{
		View = mView;
		Projection = mProjection;
		
		/*
			FIRST	- Opaque		(front-to-back)
			LAST	- Tranparent	(back-to-front)

			1. FnAlphaSortGameObjects
			: ������ �з�
			eLayerType ������ �з�

			2. FnZSortTransparencyGameObjects
			: ������ ����(������, ����)��
			�ָ� �ִ� �� ���� ����� ������
			��, Z�� �������� ����

			3. FnRenderOpaque
			: ������ ����

			4. FnDisableDepthStencilState
			: OFF - zwrite (Z�� ����X)

			5. FnRenderCutOut
			: ������ ����

			6. FnRenderTransparent
			: ���� ����

			7. FnEnableDepthStencilState
			: ON - zwrite (Z�� ����O)
		*/

		// Sort
		FnAlphaSortGameObjects();
		FnZSortTransparencyGameObjects();

		// Render
		FnRenderOpaque();
		FnDisableDepthStencilState();
		FnRenderCutOut();
		FnRenderTransparent();
		FnEnableDepthStencilState();
	}//END-void CCamera::FnRender

	bool CCamera::FnCreateViewMatrix()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		// View Translate Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// View Rotation Matrix
		Vector3 up = tr->FnUp();
		Vector3 right = tr->FnRight();
		Vector3 foward = tr->FnFoward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = foward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = foward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = foward.z;
		mView *= viewRotate;

		return true;
	}//END-bool CCamera::FnCreateViewMatrix

	bool CCamera::FnCreateProjectionMatrix(eProjectionType type)
	{
		// ��Ⱦ�� ���
		RECT rect = {};
		GetClientRect(MyApplication.FnGetHwnd(), &rect);
		float width = rect.right - rect.left;
		float height = rect.bottom - rect.top;
		mAspectRatio = width / height;;

		if (type == eProjectionType::OrthoGraphic)
		{// 2D - ���ٰ�, ������ X
			float OrthoGraphicRatio = mSize / 1000.0f;
			width *= OrthoGraphicRatio;
			height *= OrthoGraphicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else // ���ٰ�, ������ O
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);

		return true;
	}//END-bool CCamera::FnCreateProjectionMatrix

	void CCamera::FnRegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}//END-void CCamera::FnRegisterCameraInRenderer

	void CCamera::FnTurnLayerMask(eLayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}//END-void CCamera::FnTurnLayerMask

	void CCamera::FnAlphaSortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		// alpha sorting
		CScene* scene = CSceneManager::FnGetActiveScene();

		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i] == true)
			{
				// layer�� �ִ� ���ӿ�����Ʈ�� ������
				CLayer& layer = scene->FnGetLayer((eLayerType)i);
				const std::vector<CGameObject*> gameObjs = layer.FnGetGameObjects();

				FnDivideAlphaBlendGameObjects(gameObjs);
			}
		}
	}//END-void CCamera::FnAlphaSortGameObjects

	void CCamera::FnZSortTransparencyGameObjects()
	{ // �ڿ� �ִ�(Z���� ū) �� ����
		std::sort(mCutOutGameObjects.begin()
			, mCutOutGameObjects.end()
			, FnCompareZSort);
		
		std::sort(mTransparentGameObjects.begin()
			, mTransparentGameObjects.end()
			, FnCompareZSort);
	}//END-void CCamera::FnZSortTransparencyGameObjects

	void CCamera::FnDivideAlphaBlendGameObjects(const std::vector<CGameObject*> gameObjs)
	{
		for (CGameObject* obj : gameObjs)
		{
			// ������ ������Ʈ�� ���ٸ�
			CMeshRenderer* mr = obj->FnGetComponent<CMeshRenderer>();
			if (mr == nullptr)
				continue;

			std::shared_ptr<CMaterial> mt = mr->FnGetMaterial();
			eRenderingMode mode = mt->FnGetRenderingMode();

			switch (mode)
			{
			case yha::graphics::eRenderingMode::Opaque:
				mOpaqueGameObjects.push_back(obj);
				break;
			case yha::graphics::eRenderingMode::CutOut:
				mCutOutGameObjects.push_back(obj);
				break;
			case yha::graphics::eRenderingMode::Transparent:
				mTransparentGameObjects.push_back(obj);
				break;
			default:
				break;
			}
		}
	}//END-void CCamera::FnDivideAlphaBlendGameObjects

	void CCamera::FnRenderOpaque()
	{
		for (CGameObject* gameObj : mOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->FnGetState() != CGameObject::eState::Active)
				continue;

			gameObj->FnRender();
		}
	}//END-void CCamera::FnRenderOpaque

	void CCamera::FnRenderCutOut()
	{
		for (CGameObject* gameObj : mCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->FnGetState() != CGameObject::eState::Active)
				continue;

			gameObj->FnRender();
		}
	}//END-void CCamera::FnRenderCutOut

	void CCamera::FnRenderTransparent()
	{
		for (CGameObject* gameObj : mTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;

			if (gameObj->FnGetState() != CGameObject::eState::Active)
				continue;

			gameObj->FnRender();
		}
	}//END-void CCamera::FnRenderTransparent

	void CCamera::FnEnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)eDSType::Less];
		FnGetDevice()->FnBindDepthStencilState(dsState.Get());
	}//END-void CCamera::FnEnableDepthStencilState

	void CCamera::FnDisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)eDSType::None];
		FnGetDevice()->FnBindDepthStencilState(dsState.Get());
	}//END-void CCamera::FnDisableDepthStencilState
}
