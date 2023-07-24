#pragma once
#include "CComponent.h"
#include "CAnimation.h"

namespace yha
{
	class CAnimator : public CComponent
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

	public:
		CAnimator();
		~CAnimator();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();

	public:
		void FnCreate(
			const std::wstring& name
			, std::shared_ptr<graphics::CTexture> atlas
			, Vector2 leftTop
			, Vector2 size
			, UINT columnLength
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1f);

		CAnimation* FnCreateAnimations(const std::wstring& path, float duration);

		CAnimation* FindAnimation(const std::wstring& name);
		Events* FnFindEvents(const std::wstring& name);
		void FnPlayAnimation(const std::wstring& name, bool loop);
		void FnBinds();

		std::function<void()>& FnStartEvent(const std::wstring key);
		std::function<void()>& FnCompleteEvent(const std::wstring key);
		std::function<void()>& FnEndEvent(const std::wstring key);

	private:
		std::map<std::wstring, CAnimation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		CAnimation* mActiveAnimation;
		bool mbLoop;

		std::shared_ptr<graphics::CTexture> mImageAtlas;
	};
}
