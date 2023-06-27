#pragma once
#include "CScene.h"

namespace yha
{
	class CScenePlayGrassNight : public CScene
	{
	public:
		CScenePlayGrassNight();
		virtual ~CScenePlayGrassNight();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
