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
			����
		*/
		static void FnReleaseALL();

		/*
			(�ܰ�: 0, 1)�ʱ�ȭ
		*/
		static void FnInitialize();

		/*
			(�ܰ�: 0,1)������ ī�� ��� �ۼ�
		*/
		static void FnMakePickedCardList();

		/*
			(�ܰ�: 0)������ Plants�� ���ſ� ���õ� ���� �ִ��� Ȯ��
		*/
		static bool FnChkPickedBefore(int _idx);

		/*
			(�ܰ�: 0)�׸��� - Plants ��ü ���
		*/
		static void FnDrawWholeCardList();

		/*
			(�ܰ�: 0)�׸��� - Player�� ����� ���
		*/
		static void FnDrawPickedCardList(eStepMode _step);

		/*
			(�ܰ�: 0)Ŭ���̺�Ʈ ó�� - ��ü ī�� ��Ͽ��� Card ���ý�
		*/
		static void FnClickEvent_WholeCardList();

		/*
			(�ܰ�: 0)Ŭ���̺�Ʈ ó�� - ������ ī�� ��Ͽ��� Card ���ý�
		*/
		static void FnClickEvent_PickedCardList();

		/*
			(�ܰ�: 1)Ŭ���̺�Ʈ ó�� - Card ���ý�
		*/
		static void FnClickEvent();

		/*
			(�ܰ�: 1)���� ���� - ī��
		*/
		static void FnReleaseSelect();

		/*
			(�ܰ�: 1)ī�� ��Ÿ��
		*/
		static void FnStartCoolTime();

	public:
		struct infoPickedCard
		{// mPickedCardList
			ePlantsType		plantsType;			// �Ĺ� ����
			bool			isDisabled;			// ���� - ī�� Ȱ��ȭ
			bool			isCoolTimeActive;	// ���� - ��Ÿ�� Ȱ��ȭ
			float			coolTime;			// ���ؽð� - ī�� ��Ÿ��
		};

	public:
		// (�ܰ�: 0,1) ���õ� ī�� ���
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
		// (�ܰ�: 0,1) ���õ� ī���� Ÿ��
		static ePlantsType mPickedCardType;

		// (�ܰ�: 0) ���õ� ī�� �� ����, Play��ư Ȱ��ȭ ����
		static int mCntPickedCard;

		// ���õ� ī�� ���� ���� Ȯ�ο�
		static bool mFlagIsCardSelected;
	};
}