#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"

namespace yha
{
	class CCherryBomb
	{
	public:
		CCherryBomb();
		~CCherryBomb();

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
		static void FnCherryBomb(int _idx);

	public:
		static float mChkSecond;
		static int mCntTmp;
	};
}

