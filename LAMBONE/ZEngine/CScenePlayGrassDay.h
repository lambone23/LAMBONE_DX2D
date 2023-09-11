/*
TODO

FnClickEvent_Board()
C6262  Excessive Stack Usage (스택 사이즈 초과 사용)

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

		/*
			(단계: 0,1)선택한 카드 목록 작성
		*/
		void FnMakePickedCardList();

		/*
			(단계: 0)선택한 Plants를 과거에 선택된 적이 있는지 확인
		*/
		bool FnChkPickedBefore(int _idx);

		/*
			(단계: 0)그리기 - Plants 전체 목록
		*/
		void FnDrawWholeCardList();

		/*
			(단계: 0)그리기 - Player로 사용할 목록
		*/
		void FnDrawPickedCardList(eStepMode _step);

		/*
			(단계: 0)버튼 클릭이벤트 처리 - 선택목록Reset버튼
		*/
		void FnClickEvent_BtnResetChoose();

		/*
			(단계: 0)버튼 클릭이벤트 처리 - Play버튼
		*/
		void FnClickEvent_BtnPlay();

		/*
			(단계: 0)클릭이벤트 처리 - 전체 카드 목록에서 Card 선택시
		*/
		void FnClickEvent_CardFrom_WholeCardList();

		/*
			(단계: 0)클릭이벤트 처리 - 선택한 카드 목록에서 Card 선택시
		*/
		void FnClickEvent_CardFrom_PickedCardList();

		/*
			(단계: 1)클릭이벤트 처리 - Card 선택시
		*/
		void FnClickEvent_Card();

		/*
			(단계: 1)클릭이벤트 처리 - 뽑기삽을 선택시
		*/
		void FnClickEvent_Shovel();

		/*
			(단계: 1)클릭이벤트 처리 - Board 선택시
		*/
		void FnClickEvent_Board();

		/*
			(단계: 1)식물 심기
		*/
		void FnPutPlants(int _posIdx);

		/*
			(단계: 1)식물 뽑기
		*/
		void FnRemovePlants(int _posIdx);

		/*
			(단계: 1)선택 해제 - 뽑기 삽
		*/
		void FnRelease_Shovel();

		/*
			(단계: 1)선택 해제 - 카드
		*/
		void FnRelease_Card();

		/*
			(단계: 1)계산 - 햇빛 포인트 합계
		*/
		void FnCalculateSunLightScore();

		/*
			(단계: 1)그리기 - 햇빛
		*/
		void FnDrawSunLights();

		/*
			(단계: 1)그리기 - 게임판
		*/
		void FnDrawBoard();

		/*
			(단계: 1)FSM - 식물
		*/
		void FnManageFSM_Plants(ePlantsType _inPlants, int _idx);

		/*
			(단계: 1)FSM - 좀비
		*/
		void FnManageFSM_Zombies();

		/*
			(단계: 1)충돌 관리 - 식물
		*/
		void FnManageCollider_Plants(ePlantsType _inPlants, int _idx);
		//void FnManageCollider_Plants();

		/*
			(단계: 1)충돌 관리 - 좀비
		*/
		void FnManageCollider_Zombies();

		/*
			(단계: 1)상태 변화 확인 - 식물
		*/
		void FnChangeStatus_Plants(ePlantsType _inPlants, int _idx, eStatusType _inStatus);

	private:

		struct infoPickedCard
		{// mPickedCardList
			ePlantsType	plantsType;				// 식물 종류
			bool		isDisabled;				// 여부 - 카드 활성화
			bool		isCoolTimeActive;		// 여부 - 쿨타임 활성화
			float		coolTime;				// 기준시간 - 카드 쿨타임
		};

		struct infoBoard
		{
			bool		isPlanted;				// 식물 생성여부
			ePlantsType	plantsType;				// 식물 종류
		};

		struct infoPlants
		{
			bool			isPlanted;			// 여부 - 생성
			bool			isChangeStatus;		// 여부 - 상태변화
			eStatusType		statusType;			// 상태(현재)
			CGameObject*	plants;				// 오브젝트 - 식물
			CAnimator*		animator;			// 이미지
			CCollider2D*	collider;			// 충돌체

			/*
				충돌 관리에서 별도 제어 요소
			*/
			bool			isAttacked;			// 여부 - 피격
			float			attackedTime;		// 기준시간 - 피격
		};

		struct infoSunLight 
		{// mSunLights
			bool			isExist;			// 여부 - 햇빛 생성 
			bool			isExistSunflower;	// 여부 - 해바라기 존재 
			float			cycleChkTime;		// 기준시간 - 햇빛 생성주기
			CGameObject*	sunLight;			// 오브젝트 - 햇빛
			Vector3			position;			// 좌표
		};

		CGameObject* mCamera_Main;
		CGameObject* mCamera_UI;
		CGameObject* mBG;
		CGameObject* mlight;

		// 햇빛 포인트 점수
		int mSunLightScore;

		// 초 카운팅 고정 확인용
		float mSecond;

		// 초 카운팅 임시 확인용
		double mChkSecondTmp;
		
		// (단계: 0) 화면 최초 진입 여부 확인용
		bool mFlagChkEnter;

		// (단계: 0) Play단계 진입 조건
		bool mFlagPlayEnter;

		// (단계: 0) Play단계 진입 여부 확인용
		bool mFlagPlay;

		// (단계: 0) 선택된 카드 총 개수, Play버튼 활성화 조건
		int mCntPickedCard;

		// (단계: 0,1) 선택된 카드의 타입
		ePlantsType mPickedCardType;

		// (단계: 0,1) 선택된 카드 목록
		infoPickedCard mPickedCardList[MAXPICKED] = {};

		// 선택된 카드 존재 여부 확인용
		bool mflagIsCardSelected = false;

		// 뽑기삽 선택 여부 확인용
		bool mflagIsShovelSelected = false;

		// 게임판 상태 기록
		infoBoard mBoard[MAXCOUNT_PLANTS] = {};

		// 게임판에 식물이 심어질 위치 목록
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

		// 충돌체 - 좀비
		CCollider2D* cd_NormalZombie;

		CAnimator* at_NormalZombie;
		bool FlagNormalZombie = false;
		bool FlagNormalZombieOnceIdleDid = false;
	
	};
}
