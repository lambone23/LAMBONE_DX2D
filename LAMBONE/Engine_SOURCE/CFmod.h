#pragma once
#include "ZEngine.h"
#include "CMath.h"

#include "..\\External\\Fmod\\Include\\fmod_studio.hpp"
#include "..\\External\\Fmod\\Include\\fmod.hpp"
#include "..\\External\\Fmod\\Include\\fmod_common.h"
#include "..\\External\\Fmod\\Include\\fmod_codec.h"
//#include "..\\External\\Include\\Fmod\\common_platform.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\External\\Fmod\\Library\\Debug\\fmodL_vc.lib")
#pragma comment(lib, "..\\External\\Fmod\\Library\\Debug\\fmodstudioL_vc.lib")
#else
#pragma comment(lib, "..\\External\\Fmod\\Library\\Debug\\fmod_vc.lib")
#pragma comment(lib, "..\\External\\Fmod\\Library\\Release\\fmodstudio_vc.lib")
#endif

namespace yha
{
	using namespace math;

	class CFmod
	{
	public:
		static void FnInitialize();
		static bool FnCreateSound(const std::string& path, FMOD::Sound** sound);
		static void FnSoundPlay(FMOD::Sound* sound, FMOD::Channel** channel);
		static void FnSet3DListenerAttributes(const Vector3* pos, const Vector3* vel, const Vector3* forward, const Vector3* up);
		static void FnRelease();

	private:
		static FMOD::Studio::System* mSystem;
		static FMOD::System* mCoreSystem;
	};
}
