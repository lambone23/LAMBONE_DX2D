#pragma once
#include "..\Engine_SOURCE\CScene.h"

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
		CGameObject* mCamera_Main;
		CGameObject* mCamera_UI;
		CGameObject* mBG;
		CGameObject* mUI_btn_StartAdventure;
	};
}
