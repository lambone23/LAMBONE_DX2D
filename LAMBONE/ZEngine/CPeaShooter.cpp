#include "CPeaShooter.h"

#include "CPlants.h"

namespace yha
{
	CPeaShooter::CPeaShooter()
	{
	}
	CPeaShooter::~CPeaShooter()
	{
	}

	void CPeaShooter::FnInitialize(int _idx)
	{
		CPlants::mPlants[_idx].plants->FnSetName(L"GrassDay_Peashooter_" + _idx);

		//-------------------------------------
		// infoPlants - animator
		//-------------------------------------
		// Idle
		std::shared_ptr<CTexture> atlas_Peashooter_Idle
			= CResources::FnLoad<CTexture>(L"PeaShooter_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\PeaShooter\\PeaShooter.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,					leftTop
			L"PeaShooter_Idle",	atlas_Peashooter_Idle,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1384.f / 13.f, 106.f),	13,				Vector2::Zero,	0.08f
		);

		// Attack
		std::shared_ptr<CTexture> atlas_Peashooter_Attack
			= CResources::FnLoad<CTexture>(L"PeaShooter_Attack", L"..\\Resources\\Texture\\MyGame\\Plants\\PeaShooter\\PeaShooter.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,				atlas,						leftTop
			L"PeaShooter_Attack",	atlas_Peashooter_Attack,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1384.f / 13.f, 106.f),	13,				Vector2::Zero,	0.06f
		);

		// Blink
		std::shared_ptr<CTexture> atlas_Peashooter_Blink
			= CResources::FnLoad<CTexture>(L"PeaShooter_Blink", L"..\\Resources\\Texture\\MyGame\\Plants\\PeaShooter\\PeaShooter_Blink.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,				atlas,						leftTop
			L"PeaShooter_Blink",	atlas_Peashooter_Blink,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1384.f / 13.f, 106.f),	13,				Vector2::Zero,	0.08f
		);

		//-------------------------------------
		// infoPlants - collider
		//-------------------------------------
		CPlants::mPlants[_idx].collider->FnSetSize(Vector2(0.3f, 0.3f));
	}//END-void CPeaShooter::FnInitialize

	void CPeaShooter::FnColliderManager(int _idx)
	{
		eColliderStateType nowState = CPlants::mPlants[_idx].collider->FnGetColliderState();

		switch (nowState)
		{
		case eColliderStateType::Start:
		{
			CPlants::FnChangeStatus(_idx, eStatusType::Attacked);
			CPlants::mPlants[_idx].isAttacked = true;
		}
		break;
		case eColliderStateType::Ing:
		{
			CPlants::mPlants[_idx].attackedTime += CTime::FnDeltaTime();

			if ((true == CPlants::mPlants[_idx].isAttacked)
				&& (2.f <= CPlants::mPlants[_idx].attackedTime))
			{
				CPlants::FnChangeStatus(_idx, eStatusType::DieSoon);
			}
		}
		break;
		case eColliderStateType::Fin:// 주의 - Idle
		{
			if ((true == CPlants::mPlants[_idx].isPlanted)
				&& (true == CPlants::mPlants[_idx].isAttacked)
				&& (2.f > CPlants::mPlants[_idx].attackedTime)
				&& (eStatusType::DieSoon != CPlants::mPlants[_idx].statusType))
			{// 공격을 받았지만. 죽지 않은 경우
				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
				CPlants::mPlants[_idx].isAttacked = false;
			}
			else if (eStatusType::DieSoon == CPlants::mPlants[_idx].statusType)
			{// 죽음
				CPlants::FnChangeStatus(_idx, eStatusType::Dead);
			}
		}
		break;

		default:
			break;
		}
	}//END-void CPeaShooter::FnColliderManager

	void CPeaShooter::FnFsmManager(int _idx)
	{
		switch (CPlants::mPlants[_idx].statusType)
		{
		case eStatusType::Idle:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"PeaShooter_Idle", true);
			break;
		case eStatusType::Attack:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"PeaShooter_Attack", true);
			break;
		case eStatusType::Attacked:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"PeaShooter_Blink", true);
			break;
		case eStatusType::Dead:
			CPlants::FnRemove(_idx);
			break;
		}
	}//END-void CPeaShooter::FnFsmManager
}