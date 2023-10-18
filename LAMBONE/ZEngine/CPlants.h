#pragma once
#include "CCommon.h"
#include "CCommonObjects.h"

namespace yha
{
	class CPlants
	{
	public:
		CPlants();
		~CPlants();

	public:
		/*
			����
		*/
		static void FnReleaseALL();

		/*
			(�ܰ�: 1)�ʱ�ȭ - ����
		*/
		static void FnInitialize(int _idx);

		/*
			(�ܰ�: 1)�Ĺ� �ɱ�
		*/
		static void FnPutPlants(int _idx);

		/*
			(�ܰ�: 1)�Ĺ� �̱�
		*/
		static void FnRemove(int _idx);

		/*
			(�ܰ�: 1)�浹 ���� - �Ĺ�
		*/
		static void FnColliderTotalManager(int _idx);

		/*
			(�ܰ�: 1)FSM - �Ĺ�
		*/
		static void FnFsmTotalManager(int _idx);

		/*
			(�ܰ�: 1)���� ��ȭ Ȯ�� - �Ĺ�
		*/
		static void FnChangeStatus(int _idx, eStatusType _inStatus);
	
	public:
		struct infoPlants
		{// mPlants
			bool			isPlanted;			// ���� - ����
			ePlantsType		plantsType;			// �Ĺ� ����

			CGameObject*	plants;				// ������Ʈ - �Ĺ�
			CAnimator*		animator;			// �̹���
			CCollider2D*	collider;			// �浹ü

			//-------------------------------------
			// FnChangeStatus���� ���� ���� ���
			//-------------------------------------
			bool			isChangeStatus;		// ���� - ���º�ȭ
			eStatusType		statusType;			// ����(����)

			//-------------------------------------
			// FnManageCollider���� ���� ���� ���
			//-------------------------------------
			bool			isAttacked;			// ���� - �ǰ�
			float			attackedTime;		// ���ؽð� - �ǰ�
		};

	public:
		static infoPlants mPlants[MAX_PLANTS];

	private:

	};
}
