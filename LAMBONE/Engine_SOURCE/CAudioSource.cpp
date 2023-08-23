#include "CAudioSource.h"
#include "CAudioClip.h"
#include "CTransform.h"
#include "CGameObject.h"

namespace yha
{
	CAudioSource::CAudioSource()
		: CComponent(eComponentType::AudioSource)
		, mAudioClip(nullptr)
	{
	}

	CAudioSource::~CAudioSource()
	{
	}

	void CAudioSource::FnInitialize()
	{
	}

	void CAudioSource::FnUpdate()
	{
	}

	void CAudioSource::FnLateUpdate()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();
		Vector3 pos = tr->FnGetPosition();
		Vector3 foward = tr->FnFoward();

		mAudioClip->FnSet3DAttributes(pos, foward);
	}

	void CAudioSource::FnRender()
	{
	}

	void CAudioSource::FnPlay()
	{
		mAudioClip->FnPlay();
	}
	void CAudioSource::FnStop()
	{
		mAudioClip->FnStop();
	}
	void CAudioSource::FnSetLoop(bool loop)
	{
		mAudioClip->FnSetLoop(loop);
	}
}