//#include "CCollider.h"
//#include "CTransform.h"
//#include "CGameObject.h"
//#include "CCamera.h"
//
//namespace yha
//{
//	UINT CCollider::ColliderNumber = 0;
//
//	CCollider::CCollider()
//		: CComponent(EComponentType::Collider)
//		, mCenter(VectorXY::Zero)
//		, mPos(VectorXY::Zero)
//		, mSize(100.0f, 100.0f)
//		, mID(ColliderNumber++)
//		, mCollisionCount(0)
//	{
//	}
//	CCollider::~CCollider()
//	{
//	}
//	void CCollider::Initialize()
//	{
//		CTransform* Tr = FnGetOwner()->FnGetComponent<CTransform>();
//		mPos = Tr->FnGetPos() + mCenter;
//	}
//	void CCollider::Update()
//	{
//		CTransform* Tr = FnGetOwner()->FnGetComponent<CTransform>();
//		mPos = Tr->FnGetPos() + mCenter;
//	}
//
//	void CCollider::Render(HDC hdc)
//	{
//		HPEN Pen = NULL;
//
//		if (mCollisionCount <= 0)
//			Pen = CreatePen(BS_SOLID, 2, RGB(0, 255, 0));
//		else
//			Pen = CreatePen(BS_SOLID, 2, RGB(255, 0, 0));
//
//		HPEN OldPen = (HPEN)SelectObject(hdc, Pen);
//		HBRUSH Brush = (HBRUSH)GetStockObject(NULL_BRUSH);
//		HBRUSH OldBrush = (HBRUSH)SelectObject(hdc, Brush);
//
//		VectorXY Pos = CCamera::FnCalculatePos(mPos);
//		Rectangle(hdc, Pos.X, Pos.Y, Pos.X + mSize.X, Pos.Y + mSize.Y);
//
//		(HPEN)SelectObject(hdc, OldPen);
//		(HBRUSH)SelectObject(hdc, OldBrush);
//		DeleteObject(Pen);
//
//		mCollisionCount = 0;
//	}
//	void CCollider::Release()
//	{
//	}
//	void CCollider::FnOnCollisionEnter(CCollider* Other)
//	{
//		FnGetOwner()->FnOnCollisionEnter(Other);
//	}
//	void CCollider::FnOnCollisionStay(CCollider* Other)
//	{
//		mCollisionCount = 1;
//		FnGetOwner()->FnOnCollisionStay(Other);
//	}
//	void CCollider::FnOnCollisionExit(CCollider* Other)
//	{
//		FnGetOwner()->FnOnCollisionExit(Other);
//	}
//}
