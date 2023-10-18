#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"

namespace yha
{
	class CBoard
	{
	public:
		CBoard();
		~CBoard();

	public:
		/*
			(단계: 1)MouseOver이벤트 처리
		*/
		static void FnMouseOverEvent();

		/*
			(단계: 1)Show - 식물 심을 임시 위치
		*/
		static void FnShowTmpPosition();

		/*
			(단계: 1)Show - 식물 뽑을 임시 위치
		*/
		static void FnShowTmpRemovePosition();

		/*
			(단계: 1)클릭이벤트 처리 - Board 선택시
			연동 : FnClickEvent_SunLight, FnPutPlants, FnRemovePlants
		*/
		static void FnClickEvent();

		/*
			(단계: 1)그리기 - 게임판
		*/
		static void FnDraw();
	};
}
