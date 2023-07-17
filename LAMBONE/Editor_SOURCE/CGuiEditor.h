#pragma once
#include "..\\Engine_SOURCE\\CommonInclude.h"
#include "..\\Engine_SOURCE\\ZEngine.h"
#include "..\\Engine_SOURCE\\CGraphics.h"

#include "CGuiWidget.h"
#include "CGuiEditorObject.h"
#include "CGuiDebugObject.h"

namespace gui
{
	class Editor
	{
	public:
		static void FnInitialize();
		static void FnRun();

		static void FnUpdate();
		static void FnLateUpdate();
		static void FnRender();
		static void FnRelease();

		static void FnDebugRender(const yha::graphics::DebugMesh& mesh);

	private:
		static std::vector<CWidget*> mWidgets;
		static std::vector<CEditorObject*> mEditorObjects;
		static std::vector<CDebugObject*> mDebugObjects;
	};
}
