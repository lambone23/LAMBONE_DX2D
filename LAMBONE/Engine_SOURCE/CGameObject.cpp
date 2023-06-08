#include "CGameObject.h"
#include "CRenderer.h"
#include "CGraphicDevice_Dx11.h"

#include "CInput.h"
#include "CTime.h"

//extern yha::graphics::CConstantBuffer* constantBuffer;

namespace yha
{
	CGameObject::CGameObject()
		: mState(eState::Active)
	{
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::FnInitialize()
	{
	}

	void CGameObject::FnUpdate()
	{
		// 공 움직임 구현
		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
	
		if (CInput::FnGetKey(eKeyCode::RIGHT))
			pos += Vector4(0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::LEFT))
			pos += Vector4(-0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::UP))
			pos += Vector4(0.0f, 0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::DOWN))
			pos += Vector4(0.0f, -0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);



		// 렌더

		//yha::graphics::FnGetDevice()->FnSetConstantBuffer(constantBuffer, &pos, sizeof(Vector4));
		//yha::graphics::FnGetDevice()->FnBindConstantBuffer(eShaderStage::VS, eCBType::Transform, constantBuffer);
		//constantBuffer->FnSetData(&pos);
		//constantBuffer->FnBind(eShaderStage::VS);


	}

	void CGameObject::FnLateUpdate()
	{

	}

	void CGameObject::FnRender()
	{
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		renderer::mesh->FnBindBuffer();
		renderer::shader->FnBinds();
		graphics::FnGetDevice()->FnDrawIndexed(renderer::mesh->FnGetIndexCount(), 0, 0);
	}
}
