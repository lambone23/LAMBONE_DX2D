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
			(단계: 0, 1)초기화
		*/
		static void FnInitialize();

		/*
			(단계: 0, 1)준비 - UI 자리셋팅
		*/
		static void FnReady(eStepMode _inMode);

		/*
			(단계: 0)버튼 클릭이벤트 처리 - 선택목록Reset버튼
		*/
		static void FnClickEvent_BtnResetChoose();

		/*
			(단계: 0)버튼 클릭이벤트 처리 - Play버튼
		*/
		static void FnClickEvent_BtnPlay();

		/*
			(단계: 1)클릭이벤트 처리 - 뽑기삽을 선택시
		*/
		static void FnClickEvent_Shovel();

		/*
			(단계: 1)선택 해제 - 뽑기 삽
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

	private:
		// (단계: 0) 화면 최초 진입 여부 확인용
		static bool mFlagChkEnter;

		// (단계: 0) Play단계 진입 조건
		static bool mFlagPlayEnter;

		// (단계: 0) Play단계 진입 여부 확인용
		static bool mFlagPlay;

		// 뽑기삽 선택 여부 확인용
		static bool mFlagIsShovelSelected;

		// 게임판에 식물이 심어질 위치 목록 (별도 - Chomper)
		static Vector3 positonList[MAX_PLANTS];
	};
}