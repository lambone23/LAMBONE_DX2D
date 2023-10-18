#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"

namespace yha
{
	class CZombies
	{
	public:
		CZombies();
		~CZombies();

	public:
		/*
			����
		*/
		static void FnReleaseALL();

		static void FnInitialize();

		/*
			(�ܰ�: 1)FSM - ����
		*/
		static void FnManageFSM();

		/*
			(�ܰ�: 1)�浹 ���� - ����
		*/
		static void FnManageCollider();

	private:
		static CGameObject* mZb_NormalZombie;
		static CCollider2D* cd_NormalZombie;
		static CAnimator* at_NormalZombie;
		static bool FlagNormalZombie;
		static bool FlagNormalZombieOnceIdleDid;
	};
}
