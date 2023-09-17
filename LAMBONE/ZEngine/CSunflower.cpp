#include "CSunflower.h"

#include "CPlants.h"

namespace yha
{
	CSunflower::CSunflower()
	{
	}
	CSunflower::~CSunflower()
	{
	}

	void CSunflower::FnInitialize(int _idx)
	{
		CPlants::mPlants[_idx].plants->FnSetName(L"GrassDay_Sunflower_" + _idx);

		//-------------------------------------
		// infoPlants - animator
		//-------------------------------------
		// Idle
		std::shared_ptr<CTexture> atlas_Sunflower_Idle
			= CResources::FnLoad<CTexture>(L"Sunflower_Idle", L"..\\Resources\\Texture\\MyGame\\Plants\\Sunflower\\Sunflower.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,					leftTop
			L"Sunflower_Idle",	atlas_Sunflower_Idle,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1971.f / 18.f, 111.f),	18,				Vector2::Zero,	0.08f
		);

		// Bright
		std::shared_ptr<CTexture> atlas_Sunflower_Bright
			= CResources::FnLoad<CTexture>(L"Sunflower_Bright", L"..\\Resources\\Texture\\MyGame\\Plants\\Sunflower\\Sunflower_Bright.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,				atlas,					leftTop
			L"Sunflower_Bright",	atlas_Sunflower_Bright,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1980.0f / 18.f, 112.0f),	18,				Vector2::Zero,	0.08f
		);

		// Blink
		std::shared_ptr<CTexture> atlas_Sunflower_Blink
			= CResources::FnLoad<CTexture>(L"Sunflower_Blink", L"..\\Resources\\Texture\\MyGame\\Plants\\Sunflower\\Sunflower_Blink.png");
		CPlants::mPlants[_idx].animator->FnCreate(
			// name,			atlas,					leftTop
			L"Sunflower_Blink",	atlas_Sunflower_Blink,	Vector2(0.0f, 0.0f)
			// size,							columnLength,	offset,			duration
			, Vector2(1971.f / 18.f, 111.f),	18,				Vector2::Zero,	0.08f
		);

		//-------------------------------------
		// infoPlants - collider
		//-------------------------------------
		CPlants::mPlants[_idx].collider->FnSetSize(Vector2(0.3f, 0.3f));
	}//END-void CSunflower::FnInitialize

	void CSunflower::FnColliderManager(int _idx)
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
	}//END-void CSunflower::FnColliderManager

	void CSunflower::FnFsmManager(int _idx)
	{
		switch (CPlants::mPlants[_idx].statusType)
		{
		case eStatusType::Idle:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"Sunflower_Idle", true);
			break;
		case eStatusType::Attacked:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"Sunflower_Blink", true);
			break;
		case eStatusType::Dead:
			CPlants::FnRemove(_idx);
			break;
		case eStatusType::Bright_OnlySunflower:
			CPlants::mPlants[_idx].animator->FnPlayAnimation(L"Sunflower_Bright", true);
			break;
		}
	}//END-void CSunflower::FnFsmManager

}