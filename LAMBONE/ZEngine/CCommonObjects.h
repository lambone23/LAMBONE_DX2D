#pragma once

#include "CCommon.h"

namespace yha
{
	class CCommonObjects
	{
	public:
		CCommonObjects();
		~CCommonObjects();

	public:

		static Vector3 FnGetPosition(int _idx) { return positonList[_idx]; };
		static bool FnGetFlagChkEnter() { return mFlagChkEnter; };
		static bool FnGetFlagPlayEnter() { return mFlagPlayEnter; };
		static bool FnGetFlagPlay() { return mFlagPlay; };
		static bool FnGetFlagIsShovelSelected() { return mFlagIsShovelSelected; };

	public:
		static void FnSetFlagChkEnter(bool _inValue) { mFlagChkEnter = _inValue; };
		static void FnSetFlagPlayEnter(bool _inValue) { mFlagPlayEnter = _inValue; };
		static void FnSetFlagPlay(bool _inValue) { mFlagPlay = _inValue; };
		static void FnSetFlagIsShovelSelected(bool _inValue) { mFlagIsShovelSelected = _inValue; };

	public:
		/*
			(�ܰ�: 0, 1)�ʱ�ȭ
		*/
		static void FnInitialize();

		/*
			(�ܰ�: 0, 1)�غ� - UI �ڸ�����
		*/
		static void FnReady(eStepMode _inMode);

		/*
			(�ܰ�: 0)��ư Ŭ���̺�Ʈ ó�� - ���ø��Reset��ư
		*/
		static void FnClickEvent_BtnResetChoose();

		/*
			(�ܰ�: 0)��ư Ŭ���̺�Ʈ ó�� - Play��ư
		*/
		static void FnClickEvent_BtnPlay();

		/*
			(�ܰ�: 1)Ŭ���̺�Ʈ ó�� - �̱���� ���ý�
		*/
		static void FnClickEvent_Shovel();

		/*
			(�ܰ�: 1)���� ���� - �̱� ��
		*/
		static void FnRelease_Shovel();

	public:
		//==================================================================
		// UI
		//==================================================================
		//-------------------------------------
		// 0. Choose Plants
		//-------------------------------------
		static CGameObject* mUI_SeedChooserBG;
		static CGameObject* mUI_btn_Play;
		static CGameObject* mUI_btn_Play_Disabled;
		static CGameObject* mUI_btn_ResetChoose;

		static CGameObject* mUI_SelectedCardBG1;
		static CGameObject* mUI_SelectedCardBG2;
		static CGameObject* mUI_SelectedCardBG3;
		static CGameObject* mUI_SelectedCardBG4;
		static CGameObject* mUI_SelectedCardBG5;

		//-------------------------------------
		// 1. Play
		//-------------------------------------
		static CGameObject* mUI_SunPointChk;
		static CGameObject* mUI_ShovelBG;
		static CGameObject* mUI_Shovel;

		static CGameObject* mUI_FlagMeterEmpty;
		static CGameObject* mUI_FlagMeterParts_Zombie;
		static CGameObject* mUI_FlagMeterParts_Flag;
		static CGameObject* mUI_FlagMeterParts_FlagFin;

		static CGameObject* mUI_btn_Menu;

		static CGameObject* mUI_SelectedCard;
		static CGameObject* mUI_SelectedShovel;

		static std::wstring mJalapenoName[16];
		static CGameObject* mJalapeno[MAX_JALAPENO];
		//static CGameObject* mJalapenoExplode[MAX_JALAPENO];

		static CGameObject* mJalapeno_0;
		static CGameObject* mJalapeno_1;
		static CGameObject* mJalapeno_2;
		static CGameObject* mJalapeno_3;
		static CGameObject* mJalapeno_4;
		static CGameObject* mJalapeno_5;
		static CGameObject* mJalapeno_6;
		static CGameObject* mJalapeno_7;

		static CGameObject* mJalapenoExplode_0;
		static CGameObject* mJalapenoExplode_1;
		static CGameObject* mJalapenoExplode_2;
		static CGameObject* mJalapenoExplode_3;
		static CGameObject* mJalapenoExplode_4;
		static CGameObject* mJalapenoExplode_5;
		static CGameObject* mJalapenoExplode_6;
		static CGameObject* mJalapenoExplode_7;

		static float mChkSecond;
		static int mCntTmp;

	private:
		// (�ܰ�: 0) ȭ�� ���� ���� ���� Ȯ�ο�
		static bool mFlagChkEnter;

		// (�ܰ�: 0) Play�ܰ� ���� ����
		static bool mFlagPlayEnter;

		// (�ܰ�: 0) Play�ܰ� ���� ���� Ȯ�ο�
		static bool mFlagPlay;

		// �̱�� ���� ���� Ȯ�ο�
		static bool mFlagIsShovelSelected;

		// �����ǿ� �Ĺ��� �ɾ��� ��ġ ��� (���� - Chomper)
		static Vector3 positonList[MAX_PLANTS];
	};
}