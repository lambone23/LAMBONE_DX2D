#include "CAnimator.h"

namespace yha
{
	CAnimator::CAnimator()
		: CComponent(eComponentType::Animator)
	{
	}

	CAnimator::~CAnimator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void CAnimator::FnInitialize()
	{
	}//END-void CAnimator::FnInitialize

	void CAnimator::FnUpdate()
	{
		if (mActiveAnimation == nullptr)
			return;

		if (mActiveAnimation->FnIsComplete() && mbLoop)
		{
			Events* events = FnFindEvents(mActiveAnimation->FnGetKey());
			if (events)
				events->completeEvent();

			mActiveAnimation->FnReset();
		}

		mActiveAnimation->FnLateUpdate();
	}//END-void CAnimator::FnUpdate

	void CAnimator::FnLateUpdate()
	{
	}//END-void CAnimator::FnLateUpdate

	void CAnimator::FnRender()
	{
	}//END-void CAnimator::FnRender

	void CAnimator::FnCreate(
		const std::wstring& name
		, std::shared_ptr<graphics::CTexture> atlas
		, Vector2 leftTop
		, Vector2 size
		, UINT columnLength
		, Vector2 offset
		, float duration)
	{
		CAnimation* animation = FindAnimation(name);
		if (nullptr != animation)
			return;

		animation = new CAnimation();
		animation->FnSetKey(name);

		animation->FnCreate(
			name
			, atlas
			, leftTop
			, size
			, columnLength
			, offset
			, duration);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = FnFindEvents(name);
		if (events != nullptr)
			return;

		events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}//END-void CAnimator::FnCreate

	CAnimation* CAnimator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, CAnimation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}//END-CAnimation* CAnimator::FindAnimation

	CAnimator::Events* CAnimator::FnFindEvents(const std::wstring& name)
	{
		std::map<std::wstring, Events*>::iterator iter
			= mEvents.find(name);

		if (iter == mEvents.end())
			return nullptr;

		return iter->second;
	}//END-CAnimator::Events* CAnimator::FnFindEvents

	void CAnimator::FnPlayAnimation(const std::wstring& name, bool loop)
	{
		CAnimation* prevAnimation = mActiveAnimation;

		Events* events;
		if (prevAnimation != nullptr)
		{
			events = FnFindEvents(prevAnimation->FnGetKey());
			if (events)
				events->endEvent();
		}

		CAnimation* animation = FindAnimation(name);
		if (animation)
			mActiveAnimation = animation;

		events = FnFindEvents(mActiveAnimation->FnGetKey());
		if (events)
			events->startEvent();

		mbLoop = loop;
		mActiveAnimation->FnReset();
	}//END-void CAnimator::FnPlayAnimation

	void CAnimator::FnBinds()
	{
		if (mActiveAnimation == nullptr)
			return;

		mActiveAnimation->FnBinds();
	}//END-void CAnimator::FnBinds

	std::function<void()>& CAnimator::FnStartEvent(const std::wstring key)
	{
		Events* events = FnFindEvents(key);

		return events->startEvent.mEvent;
	}//END-std::function<void()>& CAnimator::FnStartEvent

	std::function<void()>& CAnimator::FnCompleteEvent(const std::wstring key)
	{
		Events* events = FnFindEvents(key);

		return events->completeEvent.mEvent;
	}//END-std::function<void()>& CAnimator::FnCompleteEvent

	std::function<void()>& CAnimator::FnEndEvent(const std::wstring key)
	{
		Events* events = FnFindEvents(key);

		return events->endEvent.mEvent;
	}//END-std::function<void()>& CAnimator::FnEndEvent
}
