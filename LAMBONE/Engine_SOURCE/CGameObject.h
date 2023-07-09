#pragma once
#include "CEntity.h"
#include "CComponent.h"
#include "CScript.h"

namespace yha
{
	class CGameObject : public CEntity
	{
	public:
		enum class eState
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

			for (CScript* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		template <typename T>
		T* FnAddComponent()
		{
			T* comp = new T();

			CComponent* buff = dynamic_cast<CComponent*>(comp);
			CScript* script = dynamic_cast<CScript*>(buff);

			if (buff == nullptr)
				return nullptr;

			if (script == nullptr)
				mComponents.push_back(buff);
			else
				mScripts.push_back(script);

			comp->FnSetOwner(this);

			return comp;
		}

		void FnSetState(eState state) { mState = state; }
		eState FnGetState() { return mState; }

	private:
		eState mState;
		std::vector<CComponent*> mComponents;
		std::vector<CScript*> mScripts;
	};
}
