#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CScenePlayGrassDay : public CScene
	{
	public:
		CScenePlayGrassDay();
		virtual ~CScenePlayGrassDay();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	private:
		CGameObject* mCamera;
		double mChkSecond = 0.0f;

		bool mFlagChkEnterScene = false;
		bool mFlagPlay = false;
		bool mFlagClickEvent_BtnPlay = false;
		bool mFlagShowSeedChooser = true;

		CGameObject* mUI_SeedChooserBG;
		CGameObject* mUI_btn_Play;

		CGameObject* mUI_SunPointChk;
		CGameObject* mUI_ShovelBG;
		CGameObject* mUI_Shovel;

		CGameObject* mUI_FlagMeterEmpty;
		CGameObject* mUI_FlagMeterParts_Zombie;
		CGameObject* mUI_FlagMeterParts_Flag;
		CGameObject* mUI_FlagMeterParts_FlagFin;

		CGameObject* mUI_btn_Menu;

		CGameObject* mCard_SunFlower;
		CGameObject* mCard_SunFlower2;
		CGameObject* mCard_SunFlower3;
		CGameObject* mCard_SunFlower4;
		CGameObject* mCard_SunFlower5;
		CGameObject* mCard_SunFlower6;
		CGameObject* mCard_SunFlower7;
		CGameObject* mCard_SunFlower8;
		//CGameObject* mCard_Peashooter;
		//CGameObject* mCard_WallNut;
		//CGameObject* mCard_CherryBomb;

	public:
		virtual void FnOnEnter() override;
		virtual void FnOnExit() override;
	};
}
