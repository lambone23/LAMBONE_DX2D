#pragma once
#include "CResource.h"
#include "CFmod.h"

//#include <Fmod/fmod_studio.hpp>
//#include <Fmod/fmod.hpp>
//#include <Fmod/fmod_common.h>
//#include <Fmod/fmod_codec.h>

//#include "..\External\Include\\DirectXTex\DirectXTex.h"

namespace yha
{
	using namespace yha::math;
	class CAudioClip : public CResource
	{
	public:
		CAudioClip();
		~CAudioClip();

	public:
		virtual HRESULT FnLoad(const std::wstring& path) override;

		void FnPlay();
		void FnStop();
		void FnSet3DAttributes(const Vector3 pos, const Vector3 vel);
		void FnSetLoop(bool loop) { mbLoop = loop; }

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
	};
}
