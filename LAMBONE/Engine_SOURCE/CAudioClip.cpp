#include "CAudioClip.h"
#include "CTransform.h"

namespace yha
{
	CAudioClip::CAudioClip()
		: CResource(eResourceType::AudioClip)
		, mSound(nullptr)
		, mChannel(nullptr)
		, mMinDistance(1.0f)
		, mMaxDistance(1000.0f)
		, mbLoop(false)
	{
	}

	CAudioClip::~CAudioClip()
	{
		//mSound->release();
		//mSound = nullptr;
	}

	HRESULT CAudioClip::FnLoad(const std::wstring& path)
	{
		std::string cPath(path.begin(), path.end());
		if (!CFmod::FnCreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);

		return S_OK;
	}

	void CAudioClip::FnPlay()
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		CFmod::FnSoundPlay(mSound, &mChannel);
	}

	void CAudioClip::FnStop()
	{
		mChannel->stop();
	}

	void CAudioClip::FnSet3DAttributes(const Vector3 pos, const Vector3 vel)
	{
		FMOD_VECTOR fmodPos(pos.x, pos.y, pos.z);
		FMOD_VECTOR fmodVel(vel.x, vel.y, vel.z);

		mChannel->set3DAttributes(&fmodPos, &fmodVel);
	}
}
