#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CScenePlayPoolNight : public CScene
	{
	public:
		CScenePlayPoolNight();
		virtual ~CScenePlayPoolNight();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
