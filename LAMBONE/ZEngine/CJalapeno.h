#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"

namespace yha
{
	class CJalapeno
	{
	public:
		CJalapeno();
		~CJalapeno();

	public:
		/*
			초기화 - 생성
		*/
		static void FnInitialize(int _idx);

		/*
			충돌 관리
		*/
		static void FnColliderManager(int _idx);

		/*
			FSM
		*/
		static void FnFsmManager(int _idx);

		/*
			FSM 중 Idle에서 한번에 처리하기 위한 총 과정
		*/
		static void FnJalapeno(int _idx);

	public:
		//static std::wstring mJalapenoName[16];
		//static CGameObject* mJalapeno[MAX_JALAPENO];
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
	};
}

