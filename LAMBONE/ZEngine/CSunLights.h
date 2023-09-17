#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"

namespace yha
{
	class CSunLights
	{
	public:
		enum class eSunLightType
		{
			Sunflower,
			Natural,
			End
		};

	public:
		CSunLights();
		~CSunLights();

	public:
		static int FnGetSunLightScore() { return mSunLightScore; };
		static float FnGetChkSecond() { return mChkSecond; };

	public:
		static void FnSetSunLightScore_isAdd(bool _isAdd, int _inValue) { _isAdd ? mSunLightScore += _inValue : mSunLightScore -= _inValue; };
		static void FnSetChkSecond(float _inValue) { mChkSecond = _inValue; };

	public:
		/*
			(단계: 1)초기화 - 생성
		*/
		static void FnInitialize(int _idx, eSunLightType _inType);

		/*
			(단계: 1)햇빛 생성 시작(해바라기)
		*/
		static void FnStart(int _idx);

		/*
			(단계: 1)햇빛 제거
		*/
		static void FnRemove(int _idx, eSunLightType _inType);

		/*
			(단계: 1)클릭이벤트 처리 - SunLight 선택시
		*/
		static void FnClickEvent(int _idx, POINT _MousePos);

		/*
			(단계: 1)햇빛 관리 - 해바라기
		*/
		static void FnManageSunLight_Sunflower();

		/*
			(단계: 1)햇빛 관리 - 자연
		*/
		static void FnManageSunLight_Natural();

		/*
			(단계: 1)그리기 - 햇빛
		*/
		static void FnDraw();

	public:

		struct infoSunLight
		{
			bool			isShow;			// 여부 - 햇빛 생성
			float			cycleChkTime;	// 기준시간 - 햇빛 생성주기
			CGameObject*	sunLight;		// 오브젝트 - 햇빛

			//-------------------------------------
			// Natural 전용 요소
			//-------------------------------------
			bool			isArrived;		// 여부 - 도달점 도착
			Vector3			position;		// 좌표
			Vector3			destination;	// 좌표 - 도달점
		};

	public:
		static infoSunLight mSunLights[MAX_PLANTS];
		static infoSunLight mSunLights_Natural[MAX_SUNLIGHT_NATURAL];

	private:
		// 햇빛 포인트 점수
		static int mSunLightScore;

		// 초 카운팅 - 햇빛 생성용
		static float mChkSecond;

		// 햇빛(Natural) 랜덤 생성한 좌표 과거값
		static int mPrevRandomIdx_SunLightNatural;
	};
}
