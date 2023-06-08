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
		// �� ������ ����
		Vector4 pos(0.0f, 0.0f, 0.0f, 1.0f);
	
		if (CInput::FnGetKey(eKeyCode::RIGHT))
			pos += Vector4(0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::LEFT))
			pos += Vector4(-0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::UP))
			pos += Vector4(0.0f, 0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);
		if (CInput::FnGetKey(eKeyCode::DOWN))
			pos += Vector4(0.0f, -0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);



		// ����

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
		//������۷� ��ġ���� ũ������, ����, ������Ʈ ������Ѵ�.

		renderer::mesh->FnBindBuffer();
		renderer::shader->FnBinds();
		graphics::FnGetDevice()->FnDrawIndexed(renderer::mesh->FnGetIndexCount(), 0, 0);
	}
}
