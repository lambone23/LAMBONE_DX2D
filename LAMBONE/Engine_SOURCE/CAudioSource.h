#pragma once
#include "CComponent.h"
#include "CAudioClip.h"

namespace yha
{
	class CAudioSource : public CComponent
	{
	public:
		CAudioSource();
		~CAudioSource();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		void FnPlay();
		void FnStop();
		void FnSetLoop(bool loop);

		void FnSetClip(std::shared_ptr<CAudioClip> clip) { mAudioClip = clip; }
		std::shared_ptr<CAudioClip> FnGetClip() { return mAudioClip; }

	private:
		std::shared_ptr<CAudioClip> mAudioClip;
	};
}
