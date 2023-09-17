#include "CWallNut.h"

#include "CPlants.h"

namespace yha
{
	CWallNut::CWallNut()
	{
	}
	CWallNut::~CWallNut()
	{
	}

	void CWallNut::FnInitialize(int _idx)
	{
		CPlants::mPlants[_idx].plants->FnSetName(L"GrassDay_WallNut_" + _idx);

		//-------------------------------------
		// infoPlants - animator
		//-------------------------------------
		// Idle
		std::shared_ptr<CTexture> atlas_WallNut_Idle
			= CResources::FnLoad<CTexture>(L"WallNut_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\Idle\\WallNut_Idle.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,					leftTop
			L"WallNut_Idle",	atlas_WallNut_Idle,		Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1560.f / 16.f, 109.f),	16,				Vector2::Zero,	0.08f
		);

		// Blink
		std::shared_ptr<CTexture> atlas_WallNut_Blink
			= CResources::FnLoad<CTexture>(L"WallNut_Blink", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\Blink\\WallNut_Blink.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,					leftTop
			L"WallNut_Blink",	atlas_WallNut_Blink,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1560.f / 16.f, 109.f),	16,				Vector2::Zero,	0.08f
		);

		// Cracked1_Idle
		std::shared_ptr<CTexture> atlas_WallNut_Cracked1_Idle
			= CResources::FnLoad<CTexture>(L"WallNut_Cracked1_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\Idle\\WallNut_Cracked1_Idle.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,					atlas,							leftTop
			L"WallNut_Cracked1_Idle",	atlas_WallNut_Cracked1_Idle,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1072.f / 11.f, 109.f),	11,				Vector2::Zero,	0.08f
		);

		// Cracked1_Blink
		std::shared_ptr<CTexture> atlas_WallNut_Cracked1_Blink
			= CResources::FnLoad<CTexture>(L"WallNut_Cracked1_Blink", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\Blink\\WallNut_Cracked1_Blink.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,					atlas,							leftTop
			L"WallNut_Cracked1_Blink",	atlas_WallNut_Cracked1_Blink,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1072.f / 11.f, 109.f),	11,				Vector2::Zero,	0.08f
		);

		// Cracked2_Idle
		std::shared_ptr<CTexture> atlas_WallNut_Cracked2_Idle
			= CResources::FnLoad<CTexture>(L"WallNut_Cracked2_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\Idle\\WallNut_Cracked2_Idle.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,					atlas,							leftTop
			L"WallNut_Cracked2_Idle",	atlas_WallNut_Cracked2_Idle,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1462.f / 15.f, 109.f),	15,				Vector2::Zero,	0.08f
		);

		// Cracked2_Blink
		std::shared_ptr<CTexture> atlas_WallNut_Cracked2_Blink
			= CResources::FnLoad<CTexture>(L"WallNut_Cracked2_Blink", L"..\\Resources\\Texture\\MyGame\\Plants\\WallNut\\Blink\\WallNut_Cracked2_Blink.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,					atlas,							leftTop
			L"WallNut_Cracked2_Blink",	atlas_WallNut_Cracked2_Blink,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1462.f / 15.f, 109.f),	15,				Vector2::Zero,	0.08f
		);

		//-------------------------------------
		// infoPlants - collider
		//-------------------------------------
		CPlants::mPlants[_idx].collider->FnSetSize(Vector2(0.3f, 0.3f));
	}//END-void CWallNut::FnInitialize

	void CWallNut::FnColliderManager(int _idx)
	{
		eColliderStateType nowState = CPlants::mPlants[_idx].collider->FnGetColliderState();

		switch (nowState)
		{
		case eColliderStateType::Start:
		{
			CPlants::mPlants[_idx].isAttacked = true;

			switch (CPlants::mPlants[_idx].statusType)
			{
			case eStatusType::Idle:		// 하나도 안깎인 상태에서 처음 공격당함
				CPlants::FnChangeStatus(_idx, eStatusType::Attacked);
				CPlants::mPlants[_idx].attackedTime = 0.f;
				break;
			case eStatusType::Idle_1:	// 살짝 깎인 상태에서 공격당함
				CPlants::FnChangeStatus(_idx, eStatusType::Attacked_1);
				break;
			case eStatusType::Idle_2:	// 거의 깎인 상태에서 공격당함
				CPlants::FnChangeStatus(_idx, eStatusType::Attacked_2);
				break;
			}
		}
		break;
		case eColliderStateType::Ing:
		{
			CPlants::mPlants[_idx].attackedTime += CTime::FnDeltaTime();

			switch (CPlants::mPlants[_idx].statusType)
			{
			case eStatusType::Attacked:
			{
				if ((true == CPlants::mPlants[_idx].isAttacked)
					&& (10.f <= CPlants::mPlants[_idx].attackedTime))
				{// 하나도 안깎인 상태에서 깜빡임 -> 살짝 깎인 상태에서 깜빡임
					CPlants::FnChangeStatus(_idx, eStatusType::Attacked_1);
					CPlants::mPlants[_idx].attackedTime = 0.f;
				}
			}
			break;
			case eStatusType::Attacked_1:
			{
				if ((true == CPlants::mPlants[_idx].isAttacked)
					&& (10.f <= CPlants::mPlants[_idx].attackedTime))
				{// 살짝 깎인 상태에서 깜빡임 -> 거의 깎인 상태에서 깜빡임
					CPlants::FnChangeStatus(_idx, eStatusType::Attacked_2);
					CPlants::mPlants[_idx].attackedTime = 0.f;
				}
			}
			break;
			case eStatusType::Attacked_2:
			{
				if ((true == CPlants::mPlants[_idx].isAttacked)
					&& (10.f <= CPlants::mPlants[_idx].attackedTime))
				{// 거의 깎인 상태에서 깜빡임 -> 사실상 죽음 (eColliderStateType::Fin)을 위한 단계
					CPlants::FnChangeStatus(_idx, eStatusType::DieSoon);
				}
			}
			break;
			}
		}
		break;
		case eColliderStateType::Fin:// 주의 - Idle
		{
			switch (CPlants::mPlants[_idx].statusType)
			{
			case eStatusType::Attacked:
			{// 하나도 안깎인 상태

				CPlants::FnChangeStatus(_idx, eStatusType::Idle);
			}
			break;
			case eStatusType::Attacked_1:
			{// 살짝 깎인 상태

				CPlants::FnChangeStatus(_idx, eStatusType::Idle_1);
			}
			break;
			case eStatusType::Attacked_2:
			{// 거의 깎인 상태

				CPlants::FnChangeStatus(_idx, eStatusType::Idle_2);
			}
			break;
			case eStatusType::DieSoon:
			{// 사실상 죽음 (eColliderStateType::Fin)을 위한 단계

				CPlants::FnChangeStatus(_idx, eStatusType::Dead);
			}
			break;
			}

			CPlants::mPlants[_idx].isAttacked = false;
		}
		break;
		default:
			break;
		}
	}//END-void CWallNut::FnColliderManager

	void CWallNut::FnFsmManager(int _idx)
	{
		switch (CPlants::mPlants[_idx].statusType)
		{
		case eStatusType::Idle:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"WallNut_Idle", true);
			break;
		case eStatusType::Idle_1:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"WallNut_Cracked1_Idle", true);
			break;
		case eStatusType::Idle_2:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"WallNut_Cracked2_Idle", true);
			break;
		case eStatusType::Attacked:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"WallNut_Blink", true);
			break;
		case eStatusType::Attacked_1:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"WallNut_Cracked1_Blink", true);
			break;
		case eStatusType::Attacked_2:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"WallNut_Cracked2_Blink", true);
			break;
		case eStatusType::Dead:
			CPlants::FnRemove(_idx);
			break;
		}
	}//END-void CWallNut::FnFsmManager
}