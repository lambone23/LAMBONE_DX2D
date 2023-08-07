#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CSceneIntro : public CScene
	{
	public:
		CSceneIntro();
		virtual ~CSceneIntro();

	private:
		void FnDoInitialize();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		virtual void FnOnEnter() override;
		virtual void FnOnExit() override;

	private:
		CGameObject* mCamera;
		CGameObject* mBG;
		CGameObject* mlight;

		CGameObject* player;
		CGameObject* monster;
		CGameObject* mUI_FlagMeterParts_Zombie;
		CGameObject* mUI_FlagMeterParts_Flag;
		CGameObject* mPl_Chomper;

		//==================================================================
		// Zombies
		//==================================================================
		CGameObject* mZb_NormalZombie;
	};
}
