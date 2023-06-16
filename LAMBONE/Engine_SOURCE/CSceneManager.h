#pragma once
#include "CScene.h"

namespace yha
{
	class CSceneManager
	{
	public:
		static void FnInitialize();
		static void FnUpdate();
		static void FnLateUpdate();
		static void FnRender();


	private:
		static CScene* mActiveScene;

		//std::map<std::wstring, Scene*> mScenes;
	};
}
