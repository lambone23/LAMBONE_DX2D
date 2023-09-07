#include "CCollider2D.h"
#include "CGameObject.h"
#include "CRenderer.h"

namespace yha
{
	UINT CCollider2D::mColliderNumber = 0;
	
	CCollider2D::CCollider2D()
		: CComponent(eComponentType::Collider2D)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
		, mColliderState(eColliderStateType::Fin)
		, mColor(eColor::Green)
	{
		mColliderNumber++;
		mColliderID = mColliderNumber;
	}

	CCollider2D::~CCollider2D()
	{
	}

	void CCollider2D::FnInitialize()
	{
		mTransform = FnGetOwner()->FnGetComponent<CTransform>();
	}

	void CCollider2D::FnUpdate()
	{
	}

	void CCollider2D::FnLateUpdate()
	{
		CTransform* tr = FnGetOwner()->FnGetComponent<CTransform>();

		Vector3 scale = tr->FnGetScale();
		scale.x *= mSize.x;
		scale.y *= mSize.y;

		Vector3 pos = tr->FnGetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		mPosition = pos;
		tr->FnSetPosition(pos);

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = scale;
		mesh.rotation = tr->FnGetRotation();
		mesh.type = eColliderType::Rect;
		//mesh.isCollide = mColliderState;
		mesh.color = mColor;

		renderer::FnPushDebugMeshAttribute(mesh);
	}//END-void CCollider2D::FnLateUpdate

	void CCollider2D::FnRender()
	{
	}

	void CCollider2D::FnOnCollisionEnter(CCollider2D* other)
	{
		mColliderState = eColliderStateType::Start;
		
		if (eAttackType::Far == other->FnGetAttackType())
			mIsAttackTypeFar = true;

		const std::vector<CScript*>& scripts = FnGetOwner()->FnGetComponents<CScript>();

		for (CScript* script : scripts)
		{
			script->FnOnCollisionEnter(other);
			mColor = eColor::Red;
		}
	}//END-void CCollider2D::FnOnCollisionEnter

	void CCollider2D::FnOnCollisionStay(CCollider2D* other)
	{
		mColliderState = eColliderStateType::Ing;

		if (eAttackType::Far == other->FnGetAttackType())
			mIsAttackTypeFar = true;

		const std::vector<CScript*>& scripts = FnGetOwner()->FnGetComponents<CScript>();

		for (CScript* script : scripts)
		{
			script->FnOnCollisionStay(other);
		}
	}//END-void CCollider2D::FnOnCollisionStay

	void CCollider2D::FnOnCollisionExit(CCollider2D* other)
	{
		const std::vector<CScript*>& scripts = FnGetOwner()->FnGetComponents<CScript>();

		for (CScript* script : scripts)
		{
			script->FnOnCollisionExit(other);
			mColor = eColor::Green;
		}
		mColliderState = eColliderStateType::Fin;

		if (eAttackType::Far == other->FnGetAttackType())
			mIsAttackTypeFar = false;
	}//END-void CCollider2D::FnOnCollisionExit
}
