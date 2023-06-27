#pragma once
//#include "CScene.h"
#include <CScene.h>

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

	private:

	};
}
