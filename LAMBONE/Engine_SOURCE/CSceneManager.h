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
		static void FnDestroy();
		static void FnRelease();

	public:
		template <typename T>
		static bool FnCreateScene(std::wstring name)
		{
			T* scene = new T();

			std::map<std::wstring, CScene*>::iterator iter = mScenes.find(name);

			if (iter != mScenes.end())
				return false;

			mScenes.insert(std::make_pair(name, scene));
			mActiveScene = scene;
			scene->FnInitialize();
			return true;
		}

		static CScene* FnLoadScene(std::wstring name);
		static CScene* FnGetActiveScene() { return mActiveScene; }
		static std::map<std::wstring, CScene*> FnGetScenes() { return mScenes; }

		static std::wstring FnGetActiveSceneName() { return mActiveSceneName; }

	private:
		static CScene* mActiveScene;
		static std::map<std::wstring, CScene*> mScenes;

		static std::wstring mActiveSceneName;

	};
}
