#pragma once

namespace yha
{
	class CSunflower
	{
	public:
		CSunflower();
		~CSunflower();

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

