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
			������ ��� ��Ÿ����
		*/
		void FnFadeIn();

		/*
			������ ��Ӱ� �������
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
