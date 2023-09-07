#pragma once
#include "CGameObject.h"

namespace yha
{
	class CSunLightScore : public CGameObject
	{
	public:
		CSunLightScore();
		~CSunLightScore();

		void FnInitialize() override;
		void FnUpdate() override;
		void FnLateUpdate() override;
		void FnRender() override;
		void FnRender_Font() override;

	private:
		wchar_t _szFloat[50];
	};
}
