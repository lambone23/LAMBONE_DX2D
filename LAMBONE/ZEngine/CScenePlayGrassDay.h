
#pragma once
#include "..\Engine_SOURCE\CScene.h"
#include "..\Engine_SOURCE\CAnimator.h"

namespace yha
{
	class CScenePlayGrassDay : public CScene
	{
	public:
		CScenePlayGrassDay();
		virtual ~CScenePlayGrassDay();

	private:
		void FnDoInitialize();
		
	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
		virtual void FnRender_Font() override;

	public:
		virtual void FnOnEnter() override;
		virtual void FnOnExit() override;

	private:
		/*
			카메라 좌우 이동
		*/
		bool FnMoveCamera(eDirection _dir);

		/*
			(단계: 0)Player로 사용할 Plants고르기
		*/
		void FnChoosePlants();

		/*
			(단계: 1)Play Game
		*/
		void FnPlay();

	private:
		CGameObject* mCamera_Main;
		CGameObject* mCamera_UI;
		CGameObject* mBG;
		CGameObject* mLight;

		// 초 카운팅 - 카메라 움직임용
		double mChkSecond_MoveCamera;
	};
}
