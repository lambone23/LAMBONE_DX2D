
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
			ī�޶� �¿� �̵�
		*/
		bool FnMoveCamera(eDirection _dir);

		/*
			(�ܰ�: 0)Player�� ����� Plants����
		*/
		void FnChoosePlants();

		/*
			(�ܰ�: 1)Play Game
		*/
		void FnPlay();

	private:
		CGameObject* mCamera_Main;
		CGameObject* mCamera_UI;
		CGameObject* mBG;
		CGameObject* mLight;

		// �� ī���� - ī�޶� �����ӿ�
		double mChkSecond_MoveCamera;
	};
}
