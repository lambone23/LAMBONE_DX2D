#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CSceneEnding : public CScene
	{
	public:
		CSceneEnding();
		virtual ~CSceneEnding();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
