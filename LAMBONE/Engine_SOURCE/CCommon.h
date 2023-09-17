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

#define MAX_CARDS_WHOLE 6
#define MAX_CARDS_PICKED 5
#define MAX_PLANTS 45
#define MAX_SUNLIGHT_NATURAL 15

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
