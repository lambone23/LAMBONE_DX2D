#pragma once
#include "..\\Engine_SOURCE\\CScript.h"
#include "..\\Engine_SOURCE\\CCamera.h"

namespace yha
{
	class CGridScript : public CScript
	{
	public:
		CGridScript();
		~CGridScript();

	public:
		virtual void FnInitialize() override;
		virtual void FnUpdate() override;
		virtual void FnLateUpdate() override;
		virtual void FnRender() override;

	public:
		void FnSetCamera(CCamera* camera) { mCamera = camera; }

	private:
		CCamera* mCamera;
	};
}