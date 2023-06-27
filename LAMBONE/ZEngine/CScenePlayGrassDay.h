#pragma once
#include "CScene.h"

namespace yha
{
	class CScenePlayGrassDay : public CScene
	{
	public:
		CScenePlayGrassDay();
		virtual ~CScenePlayGrassDay();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
