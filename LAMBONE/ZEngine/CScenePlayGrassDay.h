/*
TODO

FnClickEvent_Board()
C6262  Excessive Stack Usage (���� ������ �ʰ� ���)

*/


#pragma once
#include "..\Engine_SOURCE\CScene.h"
#include "..\Engine_SOURCE\CAnimator.h"

#define MAXCARDS 6
#define MAXPICKED 5
#define MAXCOUNT_PLANTS 45

#define POSITION_CLEAR Vector3(100.0f, 0.f, 0.010f)
#define SCALE_CLEAR Vector3(0.f, 0.f, 0.f)

#define POS_Z_DEFAULT 0.010f
#define POS_Z_FRONT_1 0.009f
#define POS_Z_FRONT_2 0.008f

#define POS_XY_PICKEDLIST_1 -3.5f, 1.1f
#define POS_XY_PICKEDLIST_2 -3.5f, 0.55f
#define POS_XY_PICKEDLIST_3 -3.5f, 0.f
#define POS_XY_PICKEDLIST_4 -3.5f, -0.55f
#define POS_XY_PICKEDLIST_5 -3.5f, -1.1f

#define SCALE_CARD_DEFAULT Vector3(0.8f, (98.f * 0.8f) / 156.f, 0.f)

#define BOARD_X_1 (400.f <= MousePos.x) && (530.f >= MousePos.x)
#define BOARD_X_2 (530.f <= MousePos.x) && (650.f >= MousePos.x)
#define BOARD_X_3 (650.f <= MousePos.x) && (780.f >= MousePos.x)
#define BOARD_X_4 (780.f <= MousePos.x) && (910.f >= MousePos.x)
#define BOARD_X_5 (910.f <= MousePos.x) && (1040.f >= MousePos.x)
#define BOARD_X_6 (1040.f <= MousePos.x) && (1160.f >= MousePos.x)
#define BOARD_X_7 (1160.f <= MousePos.x) && (1280.f >= MousePos.x)
#define BOARD_X_8 (1280.f <= MousePos.x) && (1410.f >= MousePos.x)
#define BOARD_X_9 (1410.f <= MousePos.x) && (1540.f >= MousePos.x)

#define BOARD_Y_1 (130.f <= MousePos.y) && (260.f >= MousePos.y)
#define BOARD_Y_2 (260.f <= MousePos.y) && (410.f >= MousePos.y)
#define BOARD_Y_3 (410.f <= MousePos.y) && (580.f >= MousePos.y)
#define BOARD_Y_4 (580.f <= MousePos.y) && (720.f >= MousePos.y)
#define BOARD_Y_5 (720.f <= MousePos.y) && (880.f >= MousePos.y)

namespace yha
{
	class CScenePlayGrassDay : public CScene
	{
	public:
		CScenePlayGrassDay();
		virtual ~CScenePlayGrassDay();

	private:
		void FnDoInitialize();
		void FnInitialize_UI();
		void FnInitialize_Cards();
		void FnInitialize_Plants();
		void FnInitialize_Zombies();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
		virtual void FnRender_Font() override;

	public:
		virtual void FnOnEnter() override;
		virtual void FnOnExit() override;

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

		/*
			(�ܰ�: 0,1)������ ī�� ��� �ۼ�
		*/
		void FnMakePickedCardList();

		/*
			(�ܰ�: 0)������ Plants�� ���ſ� ���õ� ���� �ִ��� Ȯ��
		*/
		bool FnChkPickedBefore(int _idx);

		/*
			(�ܰ�: 0)�׸��� - Plants ��ü ���
		*/
		void FnDrawWholeCardList();

		/*
			(�ܰ�: 0)�׸��� - Player�� ����� ���
		*/
		void FnDrawPickedCardList(eStepMode _step);

		/*
			(�ܰ�: 0)��ư Ŭ���̺�Ʈ ó�� - ���ø��Reset��ư
		*/
		void FnClickEvent_BtnResetChoose();

		/*
			(�ܰ�: 0)��ư Ŭ���̺�Ʈ ó�� - Play��ư
		*/
		void FnClickEvent_BtnPlay();

		/*
			(�ܰ�: 0)Ŭ���̺�Ʈ ó�� - ��ü ī�� ��Ͽ��� Card ���ý�
		*/
		void FnClickEvent_CardFrom_WholeCardList();

		/*
			(�ܰ�: 0)Ŭ���̺�Ʈ ó�� - ������ ī�� ��Ͽ��� Card ���ý�
		*/
		void FnClickEvent_CardFrom_PickedCardList();

		/*
			(�ܰ�: 1)Ŭ���̺�Ʈ ó�� - Card ���ý�
		*/
		void FnClickEvent_Card();

		/*
			(�ܰ�: 1)Ŭ���̺�Ʈ ó�� - �̱���� ���ý�
		*/
		void FnClickEvent_Shovel();

		/*
			(�ܰ�: 1)Ŭ���̺�Ʈ ó�� - Board ���ý�
		*/
		void FnClickEvent_Board();

		/*
			(�ܰ�: 1)�Ĺ� �ɱ�
		*/
		void FnPutPlants(int _posIdx);

		/*
			(�ܰ�: 1)�Ĺ� �̱�
		*/
		void FnRemovePlants(int _posIdx);

		/*
			(�ܰ�: 1)���� ���� - �̱� ��
		*/
		void FnRelease_Shovel();

		/*
			(�ܰ�: 1)���� ���� - ī��
		*/
		void FnRelease_Card();

		/*
			(�ܰ�: 1)��� - �޺� ����Ʈ �հ�
		*/
		void FnCalculateSunLightScore();

		/*
			(�ܰ�: 1)�׸��� - �޺�
		*/
		void FnDrawSunLights();

		/*
			(�ܰ�: 1)�׸��� - ������
		*/
		void FnDrawBoard();

		/*
			(�ܰ�: 1)FSM - �Ĺ�
		*/
		void FnManageFSM_Plants(ePlantsType _inPlants, int _idx);

		/*
			(�ܰ�: 1)FSM - ����
		*/
		void FnManageFSM_Zombies();

		/*
			(�ܰ�: 1)�浹 ���� - �Ĺ�
		*/
		void FnManageCollider_Plants(ePlantsType _inPlants, int _idx);
		//void FnManageCollider_Plants();

		/*
			(�ܰ�: 1)�浹 ���� - ����
		*/
		void FnManageCollider_Zombies();

		/*
			(�ܰ�: 1)���� ��ȭ Ȯ�� - �Ĺ�
		*/
		void FnChangeStatus_Plants(ePlantsType _inPlants, int _idx, eStatusType _inStatus);

	private:

		struct infoPickedCard
		{// mPickedCardList
			ePlantsType	plantsType;				// �Ĺ� ����
			bool		isDisabled;				// ���� - ī�� Ȱ��ȭ
			bool		isCoolTimeActive;		// ���� - ��Ÿ�� Ȱ��ȭ
			float		coolTime;				// ���ؽð� - ī�� ��Ÿ��
		};

		struct infoBoard
		{
			bool		isPlanted;				// �Ĺ� ��������
			ePlantsType	plantsType;				// �Ĺ� ����
		};

		struct infoPlants
		{
			bool			isPlanted;			// ���� - ����
			bool			isChangeStatus;		// ���� - ���º�ȭ
			eStatusType		statusType;			// ����(����)
			CGameObject*	plants;				// ������Ʈ - �Ĺ�
			CAnimator*		animator;			// �̹���
			CCollider2D*	collider;			// �浹ü

			/*
				�浹 �������� ���� ���� ���
			*/
			bool			isAttacked;			// ���� - �ǰ�
			float			attackedTime;		// ���ؽð� - �ǰ�
		};

		struct infoSunLight 
		{// mSunLights
			bool			isExist;			// ���� - �޺� ���� 
			bool			isExistSunflower;	// ���� - �عٶ�� ���� 
			float			cycleChkTime;		// ���ؽð� - �޺� �����ֱ�
			CGameObject*	sunLight;			// ������Ʈ - �޺�
			Vector3			position;			// ��ǥ
		};

		CGameObject* mCamera_Main;
		CGameObject* mCamera_UI;
		CGameObject* mBG;
		CGameObject* mlight;

		// �޺� ����Ʈ ����
		int mSunLightScore;

		// �� ī���� ���� Ȯ�ο�
		float mSecond;

		// �� ī���� �ӽ� Ȯ�ο�
		double mChkSecondTmp;
		
		// (�ܰ�: 0) ȭ�� ���� ���� ���� Ȯ�ο�
		bool mFlagChkEnter;

		// (�ܰ�: 0) Play�ܰ� ���� ����
		bool mFlagPlayEnter;

		// (�ܰ�: 0) Play�ܰ� ���� ���� Ȯ�ο�
		bool mFlagPlay;

		// (�ܰ�: 0) ���õ� ī�� �� ����, Play��ư Ȱ��ȭ ����
		int mCntPickedCard;

		// (�ܰ�: 0,1) ���õ� ī���� Ÿ��
		ePlantsType mPickedCardType;

		// (�ܰ�: 0,1) ���õ� ī�� ���
		infoPickedCard mPickedCardList[MAXPICKED] = {};

		// ���õ� ī�� ���� ���� Ȯ�ο�
		bool mflagIsCardSelected = false;

		// �̱�� ���� ���� Ȯ�ο�
		bool mflagIsShovelSelected = false;

		// ������ ���� ���
		infoBoard mBoard[MAXCOUNT_PLANTS] = {};

		// �����ǿ� �Ĺ��� �ɾ��� ��ġ ���
		Vector3 positonList[MAXCOUNT_PLANTS]
		= {
			Vector3(-1.7f,	1.3f, 0.010f), // 0
			Vector3(-1.1f,	1.3f, 0.010f), // 1
			Vector3(-0.4f,	1.3f, 0.010f), // 2
			Vector3(0.2f,	1.3f, 0.010f), // 3
			Vector3(0.8f,	1.3f, 0.010f), // 4
			Vector3(1.5f,	1.3f, 0.010f), // 5
			Vector3(2.1f,	1.3f, 0.010f), // 6
			Vector3(2.7f,	1.3f, 0.010f), // 7
			Vector3(3.3f,	1.3f, 0.010f), // 8

			Vector3(-1.7f,	0.6f, 0.010f), // 9
			Vector3(-1.1f,	0.6f, 0.010f), // 10
			Vector3(-0.4f,	0.6f, 0.010f), // 11
			Vector3(0.2f,	0.6f, 0.010f), // 12
			Vector3(0.8f,	0.6f, 0.010f), // 13
			Vector3(1.5f,	0.6f, 0.010f), // 14
			Vector3(2.1f,	0.6f, 0.010f), // 15
			Vector3(2.7f,	0.6f, 0.010f), // 16
			Vector3(3.3f,	0.6f, 0.010f), // 17

			Vector3(-1.7f,	-0.2f, 0.010f), // 18
			Vector3(-1.1f,	-0.2f, 0.010f), // 19
			Vector3(-0.4f,	-0.2f, 0.010f), // 20
			Vector3(0.2f,	-0.2f, 0.010f), // 21
			Vector3(0.8f,	-0.2f, 0.010f), // 22
			Vector3(1.5f,	-0.2f, 0.010f), // 23
			Vector3(2.1f,	-0.2f, 0.010f), // 24
			Vector3(2.7f,	-0.2f, 0.010f), // 25
			Vector3(3.3f,	-0.2f, 0.010f), // 26

			Vector3(-1.7f,	-1.f, 0.010f), // 27
			Vector3(-1.1f,	-1.f, 0.010f), // 28
			Vector3(-0.4f,	-1.f, 0.010f), // 29
			Vector3(0.2f,	-1.f, 0.010f), // 30
			Vector3(0.8f,	-1.f, 0.010f), // 31
			Vector3(1.5f,	-1.f, 0.010f), // 32
			Vector3(2.1f,	-1.f, 0.010f), // 33
			Vector3(2.7f,	-1.f, 0.010f), // 34
			Vector3(3.3f,	-1.f, 0.010f), // 35

			Vector3(-1.7f,	-1.7f, 0.010f), // 36
			Vector3(-1.1f,	-1.7f, 0.010f), // 37
			Vector3(-0.4f,	-1.7f, 0.010f), // 38
			Vector3(0.2f,	-1.7f, 0.010f), // 39
			Vector3(0.8f,	-1.7f, 0.010f), // 40
			Vector3(1.5f,	-1.7f, 0.010f), // 41
			Vector3(2.1f,	-1.7f, 0.010f), // 42
			Vector3(2.7f,	-1.7f, 0.010f), // 43
			Vector3(3.3f,	-1.7f, 0.010f), // 44
		};

		//==================================================================
		// UI
		//==================================================================
		//-------------------------------------
		// Both
		// 0. Choose Plants
		// 1. Play
		//-------------------------------------
		CGameObject* mCard_Picked_SunFlower;
		CGameObject* mCard_Picked_PeaShooter;
		CGameObject* mCard_Picked_WallNut;
		CGameObject* mCard_Picked_Chomper;
		CGameObject* mCard_Picked_Jalapeno;
		CGameObject* mCard_Picked_CherryBomb;

		CGameObject* mCard_Picked_SunFlower_Disalbed;
		CGameObject* mCard_Picked_PeaShooter_Disalbed;
		CGameObject* mCard_Picked_WallNut_Disalbed;
		CGameObject* mCard_Picked_Chomper_Disalbed;
		CGameObject* mCard_Picked_Jalapeno_Disalbed;
		CGameObject* mCard_Picked_CherryBomb_Disalbed;

		//-------------------------------------
		// 0. Choose Plants
		//-------------------------------------
		CGameObject* mUI_SeedChooserBG;
		CGameObject* mUI_btn_Play;
		CGameObject* mUI_btn_Play_Disabled;
		CGameObject* mUI_btn_ResetChoose;

		CGameObject* mCard_SunFlower;
		CGameObject* mCard_PeaShooter;
		CGameObject* mCard_WallNut;
		CGameObject* mCard_Chomper;
		CGameObject* mCard_Jalapeno;
		CGameObject* mCard_CherryBomb;

		CGameObject* mCard_EmptySpace1;
		CGameObject* mCard_EmptySpace2;
		CGameObject* mCard_EmptySpace3;
		CGameObject* mCard_EmptySpace4;
		CGameObject* mCard_EmptySpace5;

		//-------------------------------------
		// 1. Play
		//-------------------------------------
		CGameObject* mUI_SunPointChk;
		CGameObject* mUI_ShovelBG;
		CGameObject* mUI_Shovel;

		CGameObject* mUI_FlagMeterEmpty;
		CGameObject* mUI_FlagMeterParts_Zombie;
		CGameObject* mUI_FlagMeterParts_Flag;
		CGameObject* mUI_FlagMeterParts_FlagFin;

		CGameObject* mUI_btn_Menu;

		CGameObject* mUI_SelectedCard;
		CGameObject* mUI_SelectedShovel;

		//==================================================================
		// Plants
		//==================================================================
		// SunLight
		//std::vector<infoSunLight> mSunLights;
		infoSunLight mSunLights[MAXCOUNT_PLANTS] = {};

		// SunFlower
		infoPlants mPlants_SunFlowers[MAXCOUNT_PLANTS] = {};

		// WallNut
		infoPlants mPlants_WallNuts[MAXCOUNT_PLANTS] = {};

		// Peashooter
		infoPlants mPlants_Peashooters[MAXCOUNT_PLANTS] = {};

		// Chomper
		infoPlants mPlants_Chompers[MAXCOUNT_PLANTS] = {};

		//==================================================================
		// Zombies
		//==================================================================
		CGameObject* mZb_NormalZombie;

		// �浹ü - ����
		CCollider2D* cd_NormalZombie;

		CAnimator* at_NormalZombie;
		bool FlagNormalZombie = false;
		bool FlagNormalZombieOnceIdleDid = false;
	
	};
}
