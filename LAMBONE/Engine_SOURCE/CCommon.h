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


