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
			(�ܰ�: 1)Ŭ���̺�Ʈ ó�� - Board ���ý�
			���� : FnClickEvent_SunLight, FnPutPlants, FnRemovePlants
		*/
		static void FnClickEvent();

		/*
			(�ܰ�: 1)�׸��� - ������
		*/
		static void FnDraw();
	};
}
