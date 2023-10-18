#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"


namespace yha
{
	class CCards
	{
	public:
		CCards();
		~CCards();

	public:
		static ePlantsType FnGetPickedCardType() { return mPickedCardType; };
		static int FnGetCntPickedCard() { return mCntPickedCard; };
		static bool FnGetFlagIsCardSelected() { return mFlagIsCardSelected; };

	public:
		static void FnSetPickedCardType(ePlantsType _inValue) { mPickedCardType = _inValue; };
		static void FnSetCntPickedCard(int _inValue) { mCntPickedCard = _inValue; };
		static void FnSetFlagIsCardSelected(bool _inValue) { mFlagIsCardSelected = _inValue; };

	public:
		/*
			해제
		*/
		static void FnReleaseALL();

		/*
			(단계: 0, 1)초기화
		*/
		static void FnInitialize();

		/*
			(단계: 0,1)선택한 카드 목록 작성
		*/
		static void FnMakePickedCardList();

		/*
			(단계: 0)선택한 Plants를 과거에 선택된 적이 있는지 확인
		*/
		static bool FnChkPickedBefore(int _idx);

		/*
			(단계: 0)그리기 - Plants 전체 목록
		*/
		static void FnDrawWholeCardList();

		/*
			(단계: 0)그리기 - Player로 사용할 목록
		*/
		static void FnDrawPickedCardList(eStepMode _step);

		/*
			(단계: 0)클릭이벤트 처리 - 전체 카드 목록에서 Card 선택시
		*/
		static void FnClickEvent_WholeCardList();

		/*
			(단계: 0)클릭이벤트 처리 - 선택한 카드 목록에서 Card 선택시
		*/
		static void FnClickEvent_PickedCardList();

		/*
			(단계: 1)클릭이벤트 처리 - Card 선택시
		*/
		static void FnClickEvent();

		/*
			(단계: 1)선택 해제 - 카드
		*/
		static void FnReleaseSelect();

		/*
			(단계: 1)카드 쿨타임
		*/
		static void FnStartCoolTime();

	public:
		struct infoPickedCard
		{// mPickedCardList
			ePlantsType		plantsType;			// 식물 종류
			bool			isDisabled;			// 여부 - 카드 활성화
			bool			isCoolTimeActive;	// 여부 - 쿨타임 활성화
			float			coolTime;			// 기준시간 - 카드 쿨타임
		};

	public:
		// (단계: 0,1) 선택된 카드 목록
		static infoPickedCard mPickedCardList[MAX_CARDS_PICKED];

		//==================================================================
		// UI
		//==================================================================
		//-------------------------------------
		// Both
		// 0. Choose Plants
		// 1. Play
		//-------------------------------------
		static CGameObject* mCard_SunFlower_Disalbed;
		static CGameObject* mCard_WallNut_Disalbed;
		static CGameObject* mCard_PeaShooter_Disalbed;
		static CGameObject* mCard_Chomper_Disalbed;
		static CGameObject* mCard_Jalapeno_Disalbed;
		static CGameObject* mCard_CherryBomb_Disalbed;

		static CGameObject* mCard_SunFlower;
		static CGameObject* mCard_WallNut;
		static CGameObject* mCard_PeaShooter;
		static CGameObject* mCard_Chomper;
		static CGameObject* mCard_Jalapeno;
		static CGameObject* mCard_CherryBomb;

	private:
		// (단계: 0,1) 선택된 카드의 타입
		static ePlantsType mPickedCardType;

		// (단계: 0) 선택된 카드 총 개수, Play버튼 활성화 조건
		static int mCntPickedCard;

		// 선택된 카드 존재 여부 확인용
		static bool mFlagIsCardSelected;
	};
}