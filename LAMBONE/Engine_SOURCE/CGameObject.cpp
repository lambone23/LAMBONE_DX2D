#include "CGameObject.h"
#include "CRenderer.h"
#include "CGraphicDevice_Dx11.h"

#include "CInput.h"
#include "CTime.h"

#include "CScene.h"
#include "CConstantBuffer.h"

//extern yha::graphics::CConstantBuffer* constantBuffer;

namespace yha
{
	CGameObject::CGameObject
	(
		enums::eGameObjectType _inType
		, Vector4 _inPos
		, Vector4 _inColor
		, float _inSize
		, CScene* _inScene
	)
		: mState(eState::Active)
		, mType(_inType)
		, mSize(_inSize)
		, mScene(_inScene)
	{
		mVertexInfo.pos = _inPos;
		mVertexInfo.color = _inColor;
	}

	CGameObject::~CGameObject()
	{
	}

	void CGameObject::FnInitialize()
	{
	}

	void CGameObject::FnUpdate()
	{
		// 움직임 구현

		if (mType == enums::eGameObjectType::Player)
		{
			float ratio = 16.f / 9.f;
			for (CGameObject* gameObj : mScene->FnGetGameObjects())
			{
				if (gameObj->FnGetType() == enums::eGameObjectType::Player) continue;

				if (fabs(mVertexInfo.pos.x - gameObj->FnGetPos().x) < (mSize / ratio + gameObj->FnGetSize() / ratio)
					&& fabs(mVertexInfo.pos.y - gameObj->FnGetPos().y) < (mSize + gameObj->FnGetSize()))
				{
					if (gameObj->FnGetState() != eState::Dead)
					{
						mSize += 0.005f;
					}
					gameObj->FnSetState(eState::Dead);
				}
			}
		}


		if (mType == enums::eGameObjectType::Player)
		{
			Vector4 pos = mVertexInfo.pos;

			if (CInput::FnGetKey(eKeyCode::RIGHT))
				pos += Vector4(0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
				//pos.x += 0.3f * (float)CTime::FnDeltaTime();
			if (CInput::FnGetKey(eKeyCode::LEFT))
				pos += Vector4(-0.3f * CTime::FnDeltaTime(), 0.0f, 0.0f, 1.0f);
				//pos.x -= 0.3f * (float)CTime::FnDeltaTime();
			if (CInput::FnGetKey(eKeyCode::UP))
				pos += Vector4(0.0f, 0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);
				//pos.y += 0.3f * (float)CTime::FnDeltaTime();
			if (CInput::FnGetKey(eKeyCode::DOWN))
				pos += Vector4(0.0f, -0.3f * CTime::FnDeltaTime(), 0.0f, 1.0f);
				//pos.y -= 0.3f * (float)CTime::FnDeltaTime();

			if (pos != mVertexInfo.pos)
				mVertexInfo.pos = pos;
		}

	}

	void CGameObject::FnLateUpdate()
	{

	}

	void CGameObject::FnRender()
	{
		//상수버퍼로 위치정보 크기정보, 색깔, 업데이트 해줘야한다.

		//renderer::mesh->FnBindBuffer();
		//renderer::shader->FnBinds();
		//graphics::FnGetDevice()->FnDrawIndexed(renderer::mesh->FnGetIndexCount(), 0, 0);

		std::vector<renderer::Vertex> vertexes;
		std::vector<UINT> indexes;

		vertexes.resize(4);
		float ratio = 16.f / 9.f;
		vertexes[0].pos = Vector4(-mSize / ratio, mSize, 0.0f, 0.0f);
		//vertexes[0].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[1].pos = Vector4(mSize / ratio, mSize, 0.0f, 0.0f);
		//vertexes[1].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[2].pos = Vector4(mSize / ratio, -mSize, 0.0f, 0.0f);
		//vertexes[2].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector4(-mSize / ratio, -mSize, 0.0f, 0.0f);
		//vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		mesh = new yha::CMesh();

		mesh->FnCreateVertexBuffer(vertexes.data(), 4);
		mesh->FnCreateIndexBuffer(indexes.data(), indexes.size());

		renderer::constantBuffers[(UINT)eCBType::Transform]->FnSetData(&mVertexInfo);
		renderer::constantBuffers[(UINT)eCBType::Transform]->FnBind(eShaderStage::VS);

		mesh->FnBindBuffer();
		//renderer::mesh->BindBuffer();
		renderer::shader->FnBinds();
		graphics::FnGetDevice()->FnDrawIndexed(mesh->FnGetIndexCount(), 0, 0);
	}
}
