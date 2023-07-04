#pragma once
#include "CResource.h"

namespace yha
{
	class CResources
	{
	public:
		template <typename T>
		static std::shared_ptr<T> FnFind(const std::wstring& key)
		{
			// 리소스맵에서 데이터를 탐색한다.
			// 데이터가 있다면 해당데이터를 반환하고
			// 데이터가 없다면 end를 반환해준다.
			std::map<std::wstring, std::shared_ptr<CResource>>::iterator iter = mResources.find(key);

			// 찾고자 하는 데이터가 존재한다면
			// 해당타입으로 형변환하여 반환
			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			// 데이터 없다면 널을 반환
			return nullptr;
		}

		template <typename T>
		//static T* FnLoad(const std::wstring& key, const std::wstring& path)
		static std::shared_ptr<T> FnLoad(const std::wstring& key, const std::wstring& path)
		{
			// 키값으로 탐색
			std::shared_ptr<T> resource = CResources::FnFind<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// 해당 리소스가 없다면
			//resource = new T();
			resource = std::make_shared<T>();
			if (FAILED(resource->FnLoad(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->FnSetKey(key);
			resource->FnSetPath(path);
			mResources.insert(std::make_pair(key, resource));

			//return dynamic_cast<T*>(resource);
			return std::dynamic_pointer_cast<T>(resource);
		}

		template <typename T>
		static void FnInsert(const std::wstring& key, std::shared_ptr<T> resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

		//static void FnRelease()
		//{
		//	for (auto pair : mResources)
		//	{
		//		delete pair.second;
		//		pair.second = nullptr;
		//	}
		//}

	private:
		static std::map<std::wstring, std::shared_ptr<CResource>> mResources;
	};
}

