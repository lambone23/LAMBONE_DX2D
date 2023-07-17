#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CSceneEnding : public CScene
	{
	public:
		CSceneEnding();
		virtual ~CSceneEnding();

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
	};
}
