#include "CGuiEditor.h"
#include "..\\Engine_SOURCE\\CMesh.h"
#include "..\\Engine_SOURCE\\CResources.h"
#include "..\\Engine_SOURCE\\CTransform.h"
#include "..\\Engine_SOURCE\\CMeshRenderer.h"
#include "..\\Engine_SOURCE\\CMaterial.h"
#include "..\\Engine_SOURCE\\CRenderer.h"

#include "CGridScript.h"

namespace gui
{
	using namespace yha::enums;
	std::vector<CWidget*> Editor::mWidgets = {};
	std::vector<CEditorObject*> Editor::mEditorObjects = {};
	std::vector<CDebugObject*> Editor::mDebugObjects = {};

	void Editor::FnInitialize()
	{
		mDebugObjects.resize((UINT)eColliderType::End);

		std::shared_ptr<yha::CMesh> mesh = yha::CResources::FnFind<yha::CMesh>(L"DebugRect");
		std::shared_ptr<yha::CMaterial> material = yha::CResources::FnFind<yha::CMaterial>(L"DebugMaterial");

		mDebugObjects[(UINT)eColliderType::Rect] = new CDebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->FnAddComponent<yha::CTransform>();
		yha::CMeshRenderer* mr = mDebugObjects[(UINT)eColliderType::Rect]->FnAddComponent<yha::CMeshRenderer>();
		mr->FnSetMaterial(material);
		mr->FnSetMesh(mesh);

		CEditorObject* grid = new CEditorObject();
		grid->FnSetName(L"Grid");

		mr = grid->FnAddComponent<yha::CMeshRenderer>();
		mr->FnSetMesh(yha::CResources::FnFind<yha::CMesh>(L"RectMesh"));
		mr->FnSetMaterial(yha::CResources::FnFind<yha::CMaterial>(L"GridMaterial"));
		yha::CGridScript* gridSc = grid->FnAddComponent<yha::CGridScript>();
		gridSc->FnSetCamera(renderer::cameras[0]);

		mEditorObjects.push_back(grid);
	}

	void Editor::FnRun()
	{
		FnUpdate();
		FnLateUpdate();
		FnRender();
	}
	void Editor::FnUpdate()
	{
		for (CEditorObject* obj : mEditorObjects)
		{
			obj->FnUpdate();
		}
	}
	void Editor::FnLateUpdate()
	{
		for (CEditorObject* obj : mEditorObjects)
		{
			obj->FnLateUpdate();
		}
	}
	void Editor::FnRender()
	{
		for (CEditorObject* obj : mEditorObjects)
		{
			obj->FnRender();
		}

		for (const yha::graphics::DebugMesh& mesh
			: renderer::debugMeshs)
		{
			FnDebugRender(mesh);
		}
		renderer::debugMeshs.clear();
	}
	void Editor::FnRelease()
	{
		for (auto widget : mWidgets)
		{
			delete widget;
			widget = nullptr;
		}

		for (auto editorObj : mEditorObjects)
		{
			delete editorObj;
			editorObj = nullptr;
		}

		for (auto debugObj : mDebugObjects)
		{
			delete debugObj;
			debugObj = nullptr;
		}
	}

	void Editor::FnDebugRender(const yha::graphics::DebugMesh& mesh)
	{
		CDebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

		// 위치 크기 회전 정보를 받아와서 해당 게임오브젝트위에 그려주면된다.
		yha::CTransform* tr = debugObj->FnGetComponent<yha::CTransform>();

		Vector3 pos = mesh.position;
		pos.z -= 0.01f;

		tr->FnSetPosition(pos);
		tr->FnSetScale(mesh.scale);
		tr->FnSetRotation(mesh.rotation);

		tr->FnLateUpdate();

		/*yha::CMeshRenderer * mr = debugObj->FnGetComponent<yha::CMeshRenderer>();*/
		
		// main camera
		yha::CCamera* mainCamara = renderer::mainCamera;

		yha::CCamera::FnSetGpuViewMatrix(mainCamara->FnGetViewMatrix());
		yha::CCamera::FnSetGpuProjectionMatrix(mainCamara->FnGetProjectionMatrix());

		debugObj->FnRender();
	}
}
