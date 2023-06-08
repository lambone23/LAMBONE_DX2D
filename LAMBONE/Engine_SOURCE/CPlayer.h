//#pragma once
//#include "CGameObject.h"
//#include "CImage.h"
//
//namespace yha
//{
//	class CRigidbody;
//	class CAnimator;
//	class CRayman : public CGameObject
//	{
//	public:
//		CRayman();
//		~CRayman();
//
//	public:
//		virtual void Initialize() override;
//		virtual void Update() override;
//		virtual void Render(HDC hdc) override;
//		virtual void Release() override;
//
//	public:
//		enum class ERaymanState
//		{
//			Idle,
//			Move,
//			Attack,
//			Jump,
//			BeAttacked,
//			Death,
//			End
//		};
//		enum class ERaymanState_LR
//		{
//			L,
//			R,
//			END
//		};
//
//	public:
//		virtual void FnOnCollisionEnter(class CCollider* Other) override;
//		virtual void FnOnCollisionStay(class CCollider* Other) override;
//		virtual void FnOnCollisionExit(class CCollider* Other) override;
//
//	private:
//		void FnIdleCompleteEvent();
//
//		void FnIdle();
//		void FnMove();
//		void FnAttack();
//		void FnJump();
//		void FnBeAttacked();
//		void FnDeath();
//
//
//
//	private:
//		//CImage* mImage;
//		ERaymanState mState;
//		CAnimator* mAnimator;
//		CRigidbody* mRigidbody;
//
//		ERaymanState_LR mStateLR;
//		bool mFlagJumpOnce;
//		UINT mFixedColumn;
//		UINT mFixedmRow;
//	};
//}
//
//
