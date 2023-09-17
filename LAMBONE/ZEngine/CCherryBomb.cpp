#include "CCherryBomb.h"

#include "CPlants.h"

namespace yha
{
	CCherryBomb::CCherryBomb()
	{
	}
	CCherryBomb::~CCherryBomb()
	{
	}

	void CCherryBomb::FnInitialize(int _idx)
	{

	}//END-void CCherryBomb::FnInitialize

	void CCherryBomb::FnColliderManager(int _idx)
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
	}//END-void CCherryBomb::FnColliderManager

	void CCherryBomb::FnFsmManager(int _idx)
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
	}//END-void CCherryBomb::FnFsmManager
}