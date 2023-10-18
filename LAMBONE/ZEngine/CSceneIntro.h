#pragma once
#include "..\Engine_SOURCE\CScene.h"
#include "..\Engine_SOURCE\CLight.h"

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
		/*
			서서히 밝게 나타내기
		*/
		void FnFadeIn();

		/*
			서서히 어둡게 사라지기
		*/
		void FnFadeOut();

	private:
		CGameObject* mCamera;
		CGameObject* mBG;
		CGameObject* mLight;
		CLight* mLightComp;

		bool mFlagEnterFadeOut;
		float mChkSecond;
		float mBrightValue;
	};
}
