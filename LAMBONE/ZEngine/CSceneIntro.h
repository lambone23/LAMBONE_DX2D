#pragma once
#include "..\Engine_SOURCE\CScene.h"

namespace yha
{
	class CSceneIntro : public CScene
	{
	public:
		CSceneIntro();
		virtual ~CSceneIntro();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		virtual void FnOnEnter() override;
		virtual void FnOnExit() override;

	};
}
