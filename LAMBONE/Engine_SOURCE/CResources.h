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
			// ���ҽ��ʿ��� �����͸� Ž���Ѵ�.
			// �����Ͱ� �ִٸ� �ش絥���͸� ��ȯ�ϰ�
			// �����Ͱ� ���ٸ� end�� ��ȯ���ش�.
			std::map<std::wstring, std::shared_ptr<CResource>>::iterator iter = mResources.find(key);

			// ã���� �ϴ� �����Ͱ� �����Ѵٸ�
			// �ش�Ÿ������ ����ȯ�Ͽ� ��ȯ
			if (iter != mResources.end())
			{
				return std::dynamic_pointer_cast<T>(iter->second);
			}

			// ������ ���ٸ� ���� ��ȯ
			return nullptr;
		}

		template <typename T>
		//static T* FnLoad(const std::wstring& key, const std::wstring& path)
		static std::shared_ptr<T> FnLoad(const std::wstring& key, const std::wstring& path)
		{
			// Ű������ Ž��
			std::shared_ptr<T> resource = CResources::FnFind<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// �ش� ���ҽ��� ���ٸ�
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

