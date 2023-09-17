#pragma once

namespace yha
{
	class CWallNut
	{
	public:
		CWallNut();
		~CWallNut();

	public:
		/*
			檬扁拳 - 积己
		*/
		static void FnInitialize(int _idx);

		/*
			面倒 包府
		*/
		static void FnColliderManager(int _idx);

		/*
			FSM
		*/
		static void FnFsmManager(int _idx);
	};
}

