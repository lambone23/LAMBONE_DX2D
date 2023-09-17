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
			(�ܰ�: 1)�ʱ�ȭ - ����
		*/
		static void FnInitialize(int _idx, eSunLightType _inType);

		/*
			(�ܰ�: 1)�޺� ���� ����(�عٶ��)
		*/
		static void FnStart(int _idx);

		/*
			(�ܰ�: 1)�޺� ����
		*/
		static void FnRemove(int _idx, eSunLightType _inType);

		/*
			(�ܰ�: 1)Ŭ���̺�Ʈ ó�� - SunLight ���ý�
		*/
		static void FnClickEvent(int _idx, POINT _MousePos);

		/*
			(�ܰ�: 1)�޺� ���� - �عٶ��
		*/
		static void FnManageSunLight_Sunflower();

		/*
			(�ܰ�: 1)�޺� ���� - �ڿ�
		*/
		static void FnManageSunLight_Natural();

		/*
			(�ܰ�: 1)�׸��� - �޺�
		*/
		static void FnDraw();

	public:

		struct infoSunLight
		{
			bool			isShow;			// ���� - �޺� ����
			float			cycleChkTime;	// ���ؽð� - �޺� �����ֱ�
			CGameObject*	sunLight;		// ������Ʈ - �޺�

			//-------------------------------------
			// Natural ���� ���
			//-------------------------------------
			bool			isArrived;		// ���� - ������ ����
			Vector3			position;		// ��ǥ
			Vector3			destination;	// ��ǥ - ������
		};

	public:
		static infoSunLight mSunLights[MAX_PLANTS];
		static infoSunLight mSunLights_Natural[MAX_SUNLIGHT_NATURAL];

	private:
		// �޺� ����Ʈ ����
		static int mSunLightScore;

		// �� ī���� - �޺� ������
		static float mChkSecond;

		// �޺�(Natural) ���� ������ ��ǥ ���Ű�
		static int mPrevRandomIdx_SunLightNatural;
	};
}
