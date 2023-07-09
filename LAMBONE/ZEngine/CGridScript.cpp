#include "CGridScript.h"
#include "CConstantBuffer.h"
#include "CCamera.h"
#include "CTransform.h"
#include "CApplication.h"
#include "CGameObject.h"
#include "CRenderer.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CGridScript::CGridScript()
		: mCamera(nullptr)
	{
	}
	CGridScript::~CGridScript()
	{
	}
	void CGridScript::FnInitialize()
	{
	}
	void CGridScript::FnUpdate()
	{
		if (mCamera == nullptr)
			return;

		CGameObject* gameObj = mCamera->FnGetOwner();

		CTransform* tr = gameObj->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		float scale = mCamera->FnGetSize();

		HWND hWnd = MyApplication.FnGetHwnd();
		RECT winRect = {};
		GetClientRect(hWnd, &winRect);

		float width = winRect.right - winRect.left;
		float height = winRect.bottom - winRect.top;
		Vector2 resolution(width, height);

		// cs buffer
		graphics::CConstantBuffer* cb = renderer::constantBuffer[(int)eCBType::Grid];

		renderer::GridCB data;
		data.CameraPosition = Vector4(pos.x, pos.y, pos.z, 1.0f);
		data.Resolution = resolution;
		data.CameraScale = Vector2(scale, scale);

		cb->FnSetData(&data);
		cb->FnBind(eShaderStage::VS);
		cb->FnBind(eShaderStage::PS);
	}

	void CGridScript::FnLateUpdate()
	{
	}
	void CGridScript::FnRender()
	{
	}
}