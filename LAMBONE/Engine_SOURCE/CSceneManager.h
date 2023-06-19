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
		static void FnRelease();

	public:
		static CScene* FnGetActiveScene() { return mActiveScene; }
		static CScene* FnLoadScene(std::wstring name);

	private:
		static CScene* mActiveScene;
		static std::map<std::wstring, CScene*> mScenes;
	};
}
