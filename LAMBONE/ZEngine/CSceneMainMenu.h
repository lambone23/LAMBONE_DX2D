#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CSceneMainMenu : public CScene
	{
	public:
		CSceneMainMenu();
		virtual ~CSceneMainMenu();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
