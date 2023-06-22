#include "CCameraScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CTime.h"
#include "CInput.h"

namespace yha
{
	void CCameraScript::FnUpdate()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();
		
		//pos.x += 1.0f * CTime::FnDeltaTime();
		//tr->FnSetPosition(pos);

		if (CInput::FnGetKey(eKeyCode::W))
		{
			pos.z += 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::S))
		{
			pos.z -= 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::A))
		{
			pos.x -= 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::D))
		{
			pos.x += 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::Q))
		{
			pos.y -= 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::E))
		{
			pos.y += 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
	}
}