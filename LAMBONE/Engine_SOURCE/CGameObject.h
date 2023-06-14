#pragma once
#include "CEntity.h"
#include "CComponent.h"

#include "CMesh.h"
#include "CShader.h"
#include "CRenderer.h"

namespace yha
{
	class CScene;

	class CGameObject : public CEntity
	{
	public:
		enum eState
		{
			Active,
			Paused,
			Dead,
		};

	public:
		//CGameObject();
		CGameObject(enums::eGameObjectType _inType, Vector4 _inPos, Vector4 _inColor, float _inSize, CScene* _inScene);
		virtual ~CGameObject();

	public:
		virtual void FnInitialize();
		virtual void FnUpdate();
		virtual void FnLateUpdate();
		virtual void FnRender();

	public:
		enums::eGameObjectType FnGetType() { return mType; }
		Vector4 FnGetPos() { return mVertexInfo.pos; }
		float FnGetSize() { return mSize; }
		eState FnGetState() { return mState; }
		void FnSetState(eState inState) { mState = inState; }
		

	private:
		eState mState;
		//std::vector<Component*> mComponents;
		//int y;
		//int x;

		enums::eGameObjectType mType;
		float mSize;

		CMesh* mesh;
		renderer::Vertex mVertexInfo;
		CScene* mScene;

		std::vector<Vector4> mCircleIndexes;
		float mRatioX;
	};
}
