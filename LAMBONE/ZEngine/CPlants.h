#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"

namespace yha
{
	class CPlants
	{
	public:
		CPlants();
		~CPlants();

	public:
		/*
			해제
		*/
		static void FnReleaseALL();

		/*
			(단계: 1)초기화 - 생성
		*/
		static void FnInitialize(int _idx);

		/*
			(단계: 1)식물 심기
		*/
		static void FnPutPlants(int _idx);

		/*
			(단계: 1)식물 뽑기
		*/
		static void FnRemove(int _idx);

		/*
			(단계: 1)충돌 관리 - 식물
		*/
		static void FnColliderTotalManager(int _idx);

		/*
			(단계: 1)FSM - 식물
		*/
		static void FnFsmTotalManager(int _idx);

		/*
			(단계: 1)상태 변화 확인 - 식물
		*/
		static void FnChangeStatus(int _idx, eStatusType _inStatus);
	
	public:
		struct infoPlants
		{// mPlants
			bool			isPlanted;			// 여부 - 생성
			ePlantsType		plantsType;			// 식물 종류

			CGameObject*	plants;				// 오브젝트 - 식물
			CAnimator*		animator;			// 이미지
			CCollider2D*	collider;			// 충돌체

			//-------------------------------------
			// FnChangeStatus에서 별도 제어 요소
			//-------------------------------------
			bool			isChangeStatus;		// 여부 - 상태변화
			eStatusType		statusType;			// 상태(현재)

			//-------------------------------------
			// FnManageCollider에서 별도 제어 요소
			//-------------------------------------
			bool			isAttacked;			// 여부 - 피격
			float			attackedTime;		// 기준시간 - 피격
		};

	public:
		static infoPlants mPlants[MAX_PLANTS];

	private:

	};
}
