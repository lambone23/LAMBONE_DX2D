#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CScenePlayGrassNight : public CScene
	{
	public:
		CScenePlayGrassNight();
		virtual ~CScenePlayGrassNight();

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
	};
}
