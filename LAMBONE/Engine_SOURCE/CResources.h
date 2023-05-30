#pragma once
#include "CResource.h"

namespace yha
{
	class CResources
	{
	public:
		template <typename T>
		static T* FnFind(const std::wstring& key)
		{
			//���ҽ��ʿ��� �����͸� Ž���Ѵ� �����Ͱ� �ִٸ� �ش絥���͸� ��ȯ�ϰ�
			//�����Ͱ� ���ٸ� end�� ��ȯ���ش�.
			std::map<std::wstring, CResource*>::iterator iter = mResources.find(key);

			//ã���� �ϴ� �����Ͱ� �����Ѵٸ�
			//�ش�Ÿ������ ����ȯ�Ͽ� ��ȯ
			if (iter != mResources.end())
			{
				return dynamic_cast<T*>(iter->second);
			}

			//������ ���ٸ� ���� ��ȯ
			return nullptr;
		}

		template <typename T>
		static T* FnLoad(const std::wstring& key, const std::wstring& path)
		{
			// Ű������ Ž��
			T* resource = CResources::FnFind<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}

			// �ش� ���ҽ��� ���ٸ�
			resource = new T();
			if (FAILED(resource->FnLoad(path)))
			{
				assert(false);
				return nullptr;
			}

			resource->FnSetKey(key);
			resource->FnSetPath(path);
			mResources.insert(std::make_pair(key, resource));

			return dynamic_cast<T*>(resource);
		}

		template <typename T>
		static void FnInsert(const std::wstring& key, T* resource)
		{
			mResources.insert(std::make_pair(key, resource));
		}

		static void FnRelease()
		{
			for (auto pair : mResources)
			{
				delete pair.second;
				pair.second = nullptr;
			}
		}

	private:
		static std::map<std::wstring, CResource*> mResources;
	};
}

