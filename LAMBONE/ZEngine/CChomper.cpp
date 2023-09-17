#include "CChomper.h"

#include "CPlants.h"

namespace yha
{
	CChomper::CChomper()
	{
	}
	CChomper::~CChomper()
	{
	}

	void CChomper::FnInitialize(int _idx)
	{
		CPlants::mPlants[_idx].plants->FnSetName(L"GrassDay_Chomper_" + _idx);

		//-------------------------------------
		// infoPlants - animator
		//-------------------------------------
		// Idle
		std::shared_ptr<CTexture> atlas_Chomper_Idle
			= CResources::FnLoad<CTexture>(L"Chomper_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Idle.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,				leftTop
			L"Chomper_Idle",	atlas_Chomper_Idle,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(2535.f / 13.f, 171.0f),	13,				Vector2::Zero,	0.08f
		);

		// Attack
		std::shared_ptr<CTexture> atlas_Chomper_Attack
			= CResources::FnLoad<CTexture>(L"Chomper_Attack", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Attack.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,					leftTop
			L"Chomper_Attack",	atlas_Chomper_Attack,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1755.0f / 9.f, 171.0f),	9,				Vector2::Zero,	0.08f
		);

		// Digest
		std::shared_ptr<CTexture> atlas_Chomper_Digest
			= CResources::FnLoad<CTexture>(L"Chomper_Digest", L"..\\Resources\\Texture\\MyGame\\Plants\\Chomper\\Chomper_Digest.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,					leftTop
			L"Chomper_Digest",	atlas_Chomper_Digest,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1170.0f / 9.f, 171.0f),	9,				Vector2::Zero,	0.08f
		);

		//-------------------------------------
		// infoPlants - collider
		//-------------------------------------
		CPlants::mPlants[_idx].collider->FnSetSize(Vector2(1.1f, 0.5f));
		CPlants::mPlants[_idx].collider->FnSetCenter(Vector2(0.2f, -0.05f));
	}//END-void CChomper::FnInitialize

	void CChomper::FnColliderManager(int _idx)
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
	}//END-void CChomper::FnColliderManager

	void CChomper::FnFsmManager(int _idx)
	{
		switch (CPlants::mPlants[_idx].statusType)
		{
		case eStatusType::Idle:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"Chomper_Idle", true);
			break;
		case eStatusType::Attack:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"Chomper_Attack", true);
			break;
		case eStatusType::Attacked:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"Chomper_Attack", true);
			break;
		case eStatusType::Dead:
			CPlants::FnRemove(_idx);
			break;
		}
	}//END-void CChomper::FnFsmManager
}