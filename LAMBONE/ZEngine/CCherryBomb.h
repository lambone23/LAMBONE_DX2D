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
			�ʱ�ȭ - ����
		*/
		static void FnInitialize(int _idx);

		/*
			�浹 ����
		*/
		static void FnColliderManager(int _idx);

		/*
			FSM
		*/
		static void FnFsmManager(int _idx);

		/*
			FSM �� Idle���� �ѹ��� ó���ϱ� ���� �� ����
		*/
		static void FnCherryBomb(int _idx);

	public:
		static float mChkSecond;
		static int mCntTmp;
	};
}

