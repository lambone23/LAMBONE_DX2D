#pragma once
//#include "CScene.h"
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CPlayScene : public CScene
	{
	public:
		CPlayScene();
		virtual ~CPlayScene();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		virtual void FnOnEnter() override;
		virtual void FnOnExit() override;
	};
}
