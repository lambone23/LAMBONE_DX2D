#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CSceneLoading : public CScene
	{
	public:
		CSceneLoading();
		virtual ~CSceneLoading();

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
			ÀÜµð ³«ÇÏ
		*/
		void FnFallGrass();

		/*
			ÀÜµð ±¼¸®±â
		*/
		void FnRollGrass();

	private:
		CGameObject* mCamera_Main;
		CGameObject* mCamera_UI;

		CGameObject* mBG;
		CGameObject* mLight;

		CGameObject* mUI_Loading_Floor;
		CGameObject* mUI_Loading_Grass;
		CGameObject* mUI_Loading_GrassFake;
		CGameObject* mUI_Loading_Tag;

		int mCntFall;
		bool mFlagEnterRollGrass;
		float mChkSecond;
		const float mPi = 3.141592f;
		float mDegree;
		float mTagScale;

		float mGrassScale;
	};
}
