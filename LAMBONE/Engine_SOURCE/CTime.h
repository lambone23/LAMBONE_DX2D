#pragma once
#include "ZEngine.h"

namespace yha
{
	class CTime
	{
	public:
		static void FnInitiailize();
		static void FnUpdate();
		static void FnRender();

	public:
		__forceinline static double FnDeltaTime() { return mDeltaTime; }

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
	};
}
