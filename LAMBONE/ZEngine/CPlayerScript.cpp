#include "CPlayerScript.h"
#include "CCameraScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CTime.h"
#include "CInput.h"

namespace yha
{
	void CPlayerScript::FnUpdate()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();

		if (CInput::FnGetKey(eKeyCode::LEFT))
		{
			pos.x -= 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::RIGHT))
		{
			pos.x += 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::DOWN))
		{
			pos.y -= 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
		else if (CInput::FnGetKey(eKeyCode::UP))
		{
			pos.y += 5.0f * CTime::FnDeltaTime();
			tr->FnSetPosition(pos);
		}
	}
}
