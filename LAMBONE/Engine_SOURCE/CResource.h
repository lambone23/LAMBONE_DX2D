#pragma once
#include "CEntity.h"

namespace yha
{
	class CResource
	{
	public:
		CResource();
		virtual ~CResource();

	public:
		virtual HRESULT FnLoad(const std::wstring& path) = 0;

		const std::wstring& FnGetKey() { return mKey; }
		const std::wstring& FnGetPath() { return mPath; }
		void FnSetKey(const std::wstring& key) { mKey = key; }
		void FnSetPath(const std::wstring& path) { mPath = path; }

	private:
		std::wstring mKey;
		std::wstring mPath;
	};
}
