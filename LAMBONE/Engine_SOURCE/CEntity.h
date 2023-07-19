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
		void FnSetID(UINT64 id) { mColliderID = id; }
		UINT64 FnGetID() { return mColliderID; }

	private:
		std::wstring mName;
		UINT64 mColliderID;
	};
}
