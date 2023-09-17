/*
TODO

FnClickEvent_Board()
C6262  Excessive Stack Usage (스택 사이즈 초과 사용)

//■TODO-DELETE-DebugPrint
*/
/*
	************************
	* Flow
	************************
	0. Main Camera Move to RIGHT
	1. Choose Plants
	2. Main Camera Move to LEFT
	3. Play

	************************
	* Info Board
	************************
		[1]		[2]		[3]		[4]		[5]		[6]		[7]		[8]		[9]
	|---------------------------------------------------------------------------|130(2)
[1]	|	0(0)	1(1)	2(2)	3(3)	4(4)	5()		6()		7()		8()		|195(1.3)
	|---------------------------------------------------------------------------|260(1)
[2]	|	9(5)	10(6)	11(7)	12(8)	13(9)	14()	15()	16()	17()	|335(0.6)
	|---------------------------------------------------------------------------|410(0.2)
[3]	|	18(10)	19(11)	20(12)	21(13)	22(14)	23()	24()	25()	26()	|495(-0.2)
	|---------------------------------------------------------------------------|580(-0.6)
[4]	|	2o7()	28()	29(17)	30(18)	31(19)	32()	33()	34()	35()	|650(-1)
	|---------------------------------------------------------------------------|720(-1.35)
[5]	|	36()	37()	38()	39()	40()	41()	42()	43()	44()	|800(-1.7)
	|---------------------------------------------------------------------------|880(-2)
	400		530		650		780		910		1040	1160	1280	1410	1540
		465		590		715		845		975		1100	1220	1345	1475
		(-1.7)	(-1.1)	(-0.4)	(0.2)	(0.8)	(1.5)	(2.1)	(2.7)	(3.3)
*/

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
		CGameObject* mlight;

		// 초 카운팅 - 카메라 움직임용
		double mChkSecond_MoveCamera;
	};
}
