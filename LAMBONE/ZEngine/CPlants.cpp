#include "CPlants.h"

#include "CCards.h"
#include "CSunLights.h"
#include "CBoard.h"

#include "CSunflower.h"
#include "CWallNut.h"
#include "CPeaShooter.h"
#include "CChomper.h"
#include "CJalapeno.h"
#include "CCherryBomb.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CPlants::infoPlants CPlants::mPlants[MAX_PLANTS] = {};

	CPlants::CPlants()
	{
	}
	CPlants::~CPlants()
	{
	}

	void CPlants::FnInitialize(int _idx)
	{
		//==================================================================
		// ����
		//==================================================================	
		if (ePlantsType::Jalapeno != CCards::FnGetPickedCardType())
		{
			//-------------------------------------
			// infoPlants - isPlanted, plantsType
			//-------------------------------------
			mPlants[_idx].isPlanted = true;
			mPlants[_idx].plantsType = CCards::FnGetPickedCardType();

			//-------------------------------------
			// infoPlants - plants
			//-------------------------------------
			mPlants[_idx].plants = object::FnInstantiate<CGameObject>(POSITION_CLEAR, eLayerType::Player);

			CMeshRenderer* mr = mPlants[_idx].plants->FnAddComponent<CMeshRenderer>();
			mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
			mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

			//-------------------------------------
			// infoPlants - animator
			//-------------------------------------
			mPlants[_idx].animator = mPlants[_idx].plants->FnAddComponent<CAnimator>();

			//-------------------------------------
			// infoPlants - statusType
			//-------------------------------------
			FnChangeStatus(_idx, eStatusType::End);
			FnChangeStatus(_idx, eStatusType::Idle);

			//-------------------------------------
			// infoPlants - collider
			//-------------------------------------
			mPlants[_idx].collider = mPlants[_idx].plants->FnAddComponent<CCollider2D>();

			//-------------------------------------
			// infoPlants - isAttacked, attackedTime
			//-------------------------------------
			mPlants[_idx].isAttacked = false;
			mPlants[_idx].attackedTime = 0.f;
		}

		//==================================================================
		// �Ĺ� ������
		//==================================================================
		switch (CCards::FnGetPickedCardType())
		{
		case ePlantsType::Sunflower:
			CSunflower::FnInitialize(_idx);
			break;
		case ePlantsType::WallNut:
			CWallNut::FnInitialize(_idx);
			break;
		case ePlantsType::PeaShooter:
			CPeaShooter::FnInitialize(_idx);
			break;
		case ePlantsType::Chomper:
			CChomper::FnInitialize(_idx);
			break;
		case ePlantsType::Jalapeno:
			CJalapeno::FnInitialize(_idx);
			break;
		case ePlantsType::CherryBomb:
			CCherryBomb::FnInitialize(_idx);
			break;
		}

	}//END-void CPlants::FnInitialize_Plants

	void CPlants::FnPutPlants(int _idx)
	{
		bool chkIsPlantsNow = CPlants::mPlants[_idx].isPlanted;

		//==================================================================
		// �ش� ĭ�� �Ĺ��� �ִ� ����
		//==================================================================
		if (chkIsPlantsNow)
		{
			TCHAR Temp[256] = { 0, };
			MessageBox(MyApplication.FnGetHwnd(), L"�̹� ���� �Ĺ��� �ֽ��ϴ�.\n���� �Ĺ��� ���� �ٸ� ���� �����ϼ���", L"Warning", MB_OK);
		}
		//==================================================================
		// �ش� ĭ�� �Ĺ��� ���� ����
		//==================================================================
		/*
			�޺� ����Ʈ ���ǿ� �����ϸ�
			�Ĺ� ����
			�޺� ����Ʈ ����

			���õ� �Ĺ��� ������ ��ġ�� ���� ����
			���ؽð�(ī�� ��Ÿ��) Start
			���� ���� - ī��
		*/
		else
		{
			int nowSunLightScore = CSunLights::FnGetSunLightScore();

			switch (CCards::FnGetPickedCardType())
			{
			case ePlantsType::Sunflower:
				if (SCORE_SUNFLOWER <= nowSunLightScore)
				{
					FnInitialize(_idx);
					CSunLights::FnSetSunLightScore_isAdd(false, SCORE_SUNFLOWER);

					//-------------------------------------
					// only SunFlower
					//-------------------------------------
					CSunLights::FnStart(_idx);
				}
				break;
			case ePlantsType::WallNut:
				if (SCORE_WALLNUT <= nowSunLightScore)
				{
					FnInitialize(_idx);
					CSunLights::FnSetSunLightScore_isAdd(false, SCORE_WALLNUT);
				}
				break;
			case ePlantsType::PeaShooter:
				if (SCORE_PEASHOOTER <= nowSunLightScore)
				{
					FnInitialize(_idx);
					CSunLights::FnSetSunLightScore_isAdd(false, SCORE_PEASHOOTER);
				}
				break;
			case ePlantsType::Chomper:
				if (SCORE_CHOMPER <= nowSunLightScore)
				{
					FnInitialize(_idx);
					CSunLights::FnSetSunLightScore_isAdd(false, SCORE_CHOMPER);
				}
				break;
			case ePlantsType::Jalapeno:
				if (SCORE_JALAPENO <= nowSunLightScore)
				{
					FnInitialize(_idx);
					CSunLights::FnSetSunLightScore_isAdd(false, SCORE_JALAPENO);
				}
				break;
			case ePlantsType::CherryBomb:
				if (SCORE_CHERRYBOMB <= nowSunLightScore)
				{
					FnInitialize(_idx);
					CSunLights::FnSetSunLightScore_isAdd(false, SCORE_CHERRYBOMB);
				}
				break;
			default:
				break;
			}

			//-------------------------------------
			// ���ؽð�(ī�� ��Ÿ��) Start
			//-------------------------------------
			CCards::FnStartCoolTime();

			//-------------------------------------
			// ���� ���� - ī��
			//-------------------------------------
			CCards::FnReleaseSelect();

		}//end-if (!chkIsPlantsNow)

	}//END-void CPlants::FnPutPlants

	void CPlants::FnRemove(int _idx)
	{
		bool flagIsPlantsNow = CPlants::mPlants[_idx].isPlanted;

		//==================================================================
		// �ش� ĭ�� �Ĺ��� ���� ����
		//==================================================================
		if(!flagIsPlantsNow)
		{
			TCHAR Temp[256] = { 0, };
			MessageBox(MyApplication.FnGetHwnd(), L"�� ������ �Ĺ��� �����ϴ�.\n���� �Ĺ��� �ִ� �ٸ� ���� �����ϼ���", L"Warning", MB_OK);
		}
		//==================================================================
		// �ش� ĭ�� �Ĺ��� �ִ� ����
		//==================================================================
		else
		{
			mPlants[_idx].isPlanted = false;
			mPlants[_idx].plantsType = ePlantsType::End;
			FnChangeStatus(_idx, eStatusType::End);

			//-------------------------------------
			// �̱���� ���õ� ���
			//-------------------------------------
			if (true == CCommonObjects::FnGetFlagIsShovelSelected())
			{
				if (false == mPlants[_idx].isAttacked)
				{
					object::FnDestroy(mPlants[_idx].plants);

					mPlants[_idx].isAttacked = false;
					mPlants[_idx].attackedTime = 0.f;
				}

				// ���� ���� - �̱��
				CCommonObjects::FnRelease_Shovel();
			}
			//-------------------------------------
			// �̱���� ���õ��� ���� ���
			//-------------------------------------
			else
			{
				object::FnDestroy(mPlants[_idx].plants);

				mPlants[_idx].isAttacked = false;
				mPlants[_idx].attackedTime = 0.f;
			}

		}//end-if (!chkIsPlantsNow)

	}//END-void CPlants::FnRemove

	void CPlants::FnColliderTotalManager(int _idx)
	{
		switch (mPlants[_idx].plantsType)
		{
		case ePlantsType::Sunflower:
			CSunflower::FnColliderManager(_idx);
			break;
		case ePlantsType::WallNut:
			CWallNut::FnColliderManager(_idx);
			break;
		case ePlantsType::PeaShooter:
			CPeaShooter::FnColliderManager(_idx);
			break;
		case ePlantsType::Chomper:
			CChomper::FnColliderManager(_idx);
			break;
		case ePlantsType::Jalapeno:
			CJalapeno::FnColliderManager(_idx);
			break;
		case ePlantsType::CherryBomb:
			break;
		}
	}//END-void CPlants::FnColliderTotalManager

	void CPlants::FnFsmTotalManager(int _idx)
	{
		/*
			���� ���´�
			�浹 ���ο� ���� ���º�ȭ�� ����� ����

			���� ��ȭ ���ο� ����
			���� ���� ����

			���� - Chomper ���� ó��
		*/
		//==================================================================
		// SetPosition
		//==================================================================
		//-------------------------------------
		// Save ���� - Chomper ����
		//-------------------------------------
		if (true == mPlants[_idx].isPlanted
			&& ePlantsType::Chomper != mPlants[_idx].plantsType
			&& ePlantsType::Jalapeno != mPlants[_idx].plantsType
			&& eStatusType::DieSoon != mPlants[_idx].statusType)
		{
			mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetPosition(CCommonObjects::FnGetPosition(_idx));
		}
		//-------------------------------------
		// Save ���� - Chomper ���� ó��
		//-------------------------------------
		else if (ePlantsType::Chomper == mPlants[_idx].plantsType
			&& eStatusType::DieSoon != mPlants[_idx].statusType)
		{
			// ��ǥ ����
			Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
			posNumbSet = CCommonObjects::FnGetPosition(_idx);
			posNumbSet.x += 0.2f;
			posNumbSet.y += 0.1f;
			posNumbSet.z = POS_Z_FRONT_1;

			mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
		}
		//-------------------------------------
		// ��ǻ� Dead ���� - Chomper ���� All
		//-------------------------------------
		else if (eStatusType::DieSoon == mPlants[_idx].statusType)
		{
			mPlants[_idx].plants->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		}

		//==================================================================
		// statusType�� FSM
		//==================================================================
		if (true == mPlants[_idx].isChangeStatus)
		{
			mPlants[_idx].isChangeStatus = false;
			
			switch (mPlants[_idx].plantsType)
			{
			case ePlantsType::Sunflower:
				CSunflower::FnFsmManager(_idx);
				break;
			case ePlantsType::WallNut:
				CWallNut::FnFsmManager(_idx);
				break;
			case ePlantsType::PeaShooter:
				CPeaShooter::FnFsmManager(_idx);
				break;
			case ePlantsType::Chomper:
				CChomper::FnFsmManager(_idx);
				break;
			case ePlantsType::Jalapeno:
				CJalapeno::FnFsmManager(_idx);
				break;
			case ePlantsType::CherryBomb:
				CJalapeno::FnFsmManager(_idx);
				break;
			}
		}
	}//END-void CPlants::FnFsmTotalManager

	void CPlants::FnChangeStatus(int _idx, eStatusType _inStatus)
	{
		eStatusType now = _inStatus;
		eStatusType prev = mPlants[_idx].statusType;

		if (now != prev)
		{
			mPlants[_idx].isChangeStatus = true;
			mPlants[_idx].statusType = now;
		}
		else
			mPlants[_idx].isChangeStatus = false;
	}//END-void CPlants::FnChangeStatus_Plants
}