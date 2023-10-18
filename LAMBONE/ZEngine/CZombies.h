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
			해제
		*/
		static void FnReleaseALL();

		static void FnInitialize();

		/*
			(단계: 1)FSM - 좀비
		*/
		static void FnManageFSM();

		/*
			(단계: 1)충돌 관리 - 좀비
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
