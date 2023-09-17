#include "CJalapeno.h"

#include "CPlants.h"

namespace yha
{
	CJalapeno::CJalapeno()
	{
	}
	CJalapeno::~CJalapeno()
	{
	}

	void CJalapeno::FnInitialize(int _idx)
	{

	}//END-void CJalapeno::FnInitialize

	void CJalapeno::FnColliderManager(int _idx)
	{
		eColliderStateType nowState = CPlants::mPlants[_idx].collider->FnGetColliderState();

		switch (nowState)
		{
		case eColliderStateType::Start:
		{

		}
		break;
		case eColliderStateType::Ing:
		{
			CPlants::mPlants[_idx].attackedTime += CTime::FnDeltaTime();
		}
		break;
		case eColliderStateType::Fin:// ¡÷¿« - Idle
		{

		}
		break;
		default:
			break;
		}
	}//END-void CJalapeno::FnColliderManager

	void CJalapeno::FnFsmManager(int _idx)
	{
		switch (CPlants::mPlants[_idx].statusType)
		{
		case eStatusType::Idle:
			break;
		case eStatusType::Attack:
			break;
		case eStatusType::Attacked:
			break;
		case eStatusType::Dead:
			break;
		}
	}//END-void CJalapeno::FnFsmManager
}