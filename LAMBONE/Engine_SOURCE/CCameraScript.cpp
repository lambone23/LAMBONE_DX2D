#include "CCameraScript.h"
#include "CTransform.h"
#include "CGameObject.h"
#include "CTime.h"

namespace yha
{
	void CCameraScript::FnUpdate()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();
		pos.x += 1.0f * CTime::FnDeltaTime();
		tr->FnSetPosition(pos);
	}
}