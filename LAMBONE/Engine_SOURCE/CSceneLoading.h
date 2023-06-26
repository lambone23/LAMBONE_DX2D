#pragma once
#include "CScene.h"

namespace yha
{
	class CSceneLoading : public CScene
	{
	public:
		CSceneLoading();
		virtual ~CSceneLoading();

		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;
	};
}
