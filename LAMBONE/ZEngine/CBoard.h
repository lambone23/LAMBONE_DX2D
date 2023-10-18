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
			(�ܰ�: 1)MouseOver�̺�Ʈ ó��
		*/
		static void FnMouseOverEvent();

		/*
			(�ܰ�: 1)Show - �Ĺ� ���� �ӽ� ��ġ
		*/
		static void FnShowTmpPosition();

		/*
			(�ܰ�: 1)Show - �Ĺ� ���� �ӽ� ��ġ
		*/
		static void FnShowTmpRemovePosition();

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
