#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CScenePlayPoolDay : public CScene
	{
	public:
		CScenePlayPoolDay();
		virtual ~CScenePlayPoolDay();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
