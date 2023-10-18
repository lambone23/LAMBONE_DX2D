/*
TODO

FnClickEvent_Board()
C6262  Excessive Stack Usage (스택 사이즈 초과 사용)

//■TODO-DELETE-DebugPrint
//■TODO-Chk
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

#include "CGameObject.h"
#include "CInput.h"
#include "CTransform.h"
#include "CMeshRenderer.h"
#include "CResources.h"
#include "CCamera.h"
#include "CSceneManager.h"
#include "CApplication.h"
#include "CGridScript.h"
#include "CObject.h"
#include "CRenderer.h"
#include "CCameraScript.h"
#include "CTime.h"
#include "CComponent.h"
#include "CCollider2D.h"
#include "CPlayerScript.h"
#include "CCollisionManager.h"
#include "CAnimator.h"
#include "CLight.h"
#include "CComputeShader.h"
#include "CPaintShader.h"
#include "CParticleSystem.h"

#include "CFmod.h"
#include "CFontWrapper.h"

#include <vector>
#include <algorithm>

/*
	//■TODO-DELETE-DebugPrint
*/
#define DEBUGPRINT	HWND Tmp_mHwnd = MyApplication.FnGetHwnd();\
					TCHAR Temp[256] = { 0, };\
					_stprintf_s(Temp, L"Chk");\
					MessageBox(Tmp_mHwnd, Temp, L"TitleChk", MB_OK);

/*
	Default Value
*/
#define MAX_CARDS_WHOLE 6
#define MAX_CARDS_PICKED 5
#define MAX_PLANTS 45
#define MAX_SUNLIGHT_NATURAL 15

#define POSITION_CLEAR Vector3(100.0f, 0.f, 0.010f)
#define SCALE_CLEAR Vector3(0.f, 0.f, 0.f)

#define POS_Z_DEFAULT 0.010f
#define POS_Z_FRONT_1 0.009f
#define POS_Z_FRONT_2 0.008f

/*
	Card (PICKEDLIST)
*/
#define POS_XY_PICKEDLIST_1 -3.5f, 1.1f
#define POS_XY_PICKEDLIST_2 -3.5f, 0.55f
#define POS_XY_PICKEDLIST_3 -3.5f, 0.f
#define POS_XY_PICKEDLIST_4 -3.5f, -0.55f
#define POS_XY_PICKEDLIST_5 -3.5f, -1.1f

#define POS_XY_COOLTIME_1 50.f, 185.f
#define POS_XY_COOLTIME_2 50.f, 295.f
#define POS_XY_COOLTIME_3 50.f, 405.f
#define POS_XY_COOLTIME_4 50.f, 515.f
#define POS_XY_COOLTIME_5 50.f, 625.f
#define FONT_SIZE_COOLTIME 77
#define FONT_COLOR_COOLTIME 95, 0, 255, 255

#define SCALE_CARD_DEFAULT Vector3(0.8f, (98.f * 0.8f) / 156.f, 0.f)

/*
	Board
*/
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

/*
	SunLight Score
*/
#define POS_XY_SUNLIGHTSCORE 405.f, 15.f
#define FONT_SIZE_SUNLIGHTSCORE 65
#define FONT_COLOR_SUNLIGHTSCORE 33, 33, 33, 255

/*
	Score
*/
#define SCORE_SUNFLOWER 50
#define SCORE_WALLNUT 50
#define SCORE_PEASHOOTER 100
#define SCORE_CHOMPER 150
#define SCORE_JALAPENO 125
#define SCORE_CHERRYBOMB 150

#define CREATE_SUNLIGHT_LIMIT_SCORE_1 100
#define CREATE_SUNLIGHT_LIMIT_SCORE_2 200

#define CREATE_SUNLIGHT_TIME_EASY 10.f
#define CREATE_SUNLIGHT_TIME_NORAMAL 15.f
#define CREATE_SUNLIGHT_TIME_HARD 20.f

/*
	JALAPENO
*/
#define MAX_JALAPENO 8
#define SCALE_JALAPENO Vector3(0.5f, (89.f * 0.5f) / 69.f, 0.f)
#define SCALE_JALAPENO_EXPLODE Vector3(5.8f, (131.f * 5.8f) / 755.f, 0.f)

#define POS_Y_JALAPENO_EXPLODE_1 0.9f, 1.45f, 0.008f
#define POS_Y_JALAPENO_EXPLODE_2 0.9f, 0.7f, 0.008f
#define POS_Y_JALAPENO_EXPLODE_3 0.9f, -0.1f, 0.008f
#define POS_Y_JALAPENO_EXPLODE_4 0.9f, -0.85f, 0.008f
#define POS_Y_JALAPENO_EXPLODE_5 0.8f, -1.68f, 0.008f

/*
	CherryBomb
*/
#define SCALE_CHERRYBOMB Vector3(1.f, (81.f * 1.f) / 112.f, 0.f)
