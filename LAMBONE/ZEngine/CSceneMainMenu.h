#pragma once
#include "..\Engine_SOURCE\CScene.h"
#include "..\Engine_SOURCE\CLight.h"

namespace yha
{
	class CSceneMainMenu : public CScene
	{
	public:
		CSceneMainMenu();
		virtual ~CSceneMainMenu();

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
		/*
			서서히 밝게 나타내기
		*/
		void FnFadeIn();

		/*
			MouseOver Evnet
		*/
		void FnMouseOver_btn();

	private:
		CGameObject* mCamera_Main;
		CGameObject* mCamera_UI;
		CGameObject* mBG;
		CGameObject* mLight;
		CLight* mLightComp;

		CGameObject* mLambone;
		CGameObject* mUI_btn_Start;
		CGameObject* mUI_btn_Start2;

		bool mFlagFinFadeIn;
		bool mFlagMouseOver;
		float mChkSecond;
		float mBrightValue;
	};
}
