#pragma once
#include "ZEngine.h"

namespace yha
{
	class CEntity
	{
	public:
		CEntity();
		virtual ~CEntity();

	public:
		void FnSetName(const std::wstring& name) { mName = name; }
		std::wstring& FnGetName() { return mName; }
		void FnSetID(UINT64 id) { mID = id; }
		UINT64 FnGetID() { return mID; }

	private:
		std::wstring mName;
		UINT64 mID;
	};
}
