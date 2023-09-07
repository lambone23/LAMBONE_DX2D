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
		virtual void FnRender_Font();

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
		}//END-T* FnGetComponent

		template <typename T>
		//const std::vector<T*>& FnGetComponents()
		const std::vector<T*> FnGetComponents()
		{
			std::vector<T*> comps;

			T* component;
			for (CComponent* comp : mComponents)
			{
				component = dynamic_cast<T*>(comp);
				if (component != nullptr)
					comps.push_back(component);
			}

			for (CScript* script : mScripts)
			{
				component = dynamic_cast<T*>(script);
				if (component != nullptr)
					comps.push_back(component);
			}

			return comps;
		}//END-const std::vector<T*> FnGetComponents

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
			//comp->FnDoInitialize();
			comp->FnInitialize();

			return comp;
		}//END-T* FnAddComponent

		void FnDeleteCollider();

		void FnSetState(eState state) { mState = state; }
		eState FnGetState() { return mState; }

	private:
		eState mState;
		std::vector<CComponent*> mComponents;
		std::vector<CScript*> mScripts;
	};
}
