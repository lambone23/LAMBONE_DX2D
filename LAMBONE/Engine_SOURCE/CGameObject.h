#pragma once
#include "CEntity.h"
#include "CComponent.h"

namespace yha
{
	class CGameObject : public CEntity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

	public:
		CGameObject();
		virtual ~CGameObject();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();

	public:
		template <typename T>
		T* FnGetComponent()
		{
			T* component;
			for (CComponent* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		T* FnAddComponent()
		{
			T* comp = new T();

			CComponent* buff
				= dynamic_cast<CComponent*>(comp);

			if (buff == nullptr)
				return nullptr;

			mComponents.push_back(buff);
			comp->FnSetOwner(this);

			return comp;
		}

	private:
		eState mState;
		std::vector<CComponent*> mComponents;
	};
}
