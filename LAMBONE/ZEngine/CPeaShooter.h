#pragma once

namespace yha
{
	class CPeaShooter
	{
	public:
		CPeaShooter();
		~CPeaShooter();

	public:
		/*
			�ʱ�ȭ - ����
		*/
		static void FnInitialize(int _idx);

		/*
			�浹 ����
		*/
		static void FnColliderManager(int _idx);

		/*
			FSM
		*/
		static void FnFsmManager(int _idx);
	};
}

