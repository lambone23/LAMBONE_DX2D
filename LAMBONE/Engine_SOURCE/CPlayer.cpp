//#include "CRayman.h"
//
//#include "CTime.h"
//#include "CSceneMgr.h"
//#include "CInput.h"
//#include "CResources.h"
//#include "CTransform.h"
//#include "CAnimator.h"
//#include "CCollider.h"
//#include "CPunch.h"
//#include "CScene.h"
//#include "CObject.h"
//#include "CRigidbody.h"
//
//#include "CCamera.h"
//
//namespace yha
//{
//	//*****************************************************************
//	// [CRayman] 생성자(constructor)와 소멸자(destructor)
//	//*****************************************************************
//
//	CRayman::CRayman()
//		: mFlagJumpOnce(false)
//		, mFixedColumn(20)
//		, mFixedmRow(22)
//	{
//
//	}
//	CRayman::~CRayman()
//	{
//	}
//
//	//*****************************************************************
//	// [CRayman] Cycle
//	// - Initialize
//	// - Update
//	// - Render
//	// - Release
//	//*****************************************************************
//
//	void CRayman::Initialize()
//	{
//		CImage* mImage = CResources::FnLoad<CImage>(L"Rayman", L"..\\Resources\\Rayman\\Rayman.bmp");
//
//		mAnimator = FnAddComponent<CAnimator>();
//		//void CAnimator::FnCreateAnimation(const std::wstring & Name
//		//	, CImage * Sheet, VectorXY LeftTop
//		//	, UINT Column, UINT Row, UINT SpriteLength
//		//	, VectorXY Offset, float Duration)
//
//		//==================================================
//		// Setting - FSM Animation
//		//==================================================
//
//		// Idle
//		mAnimator->FnCreateAnimation(L"Idle_L", mImage, VectorXY(0.0f, 600.0f), mFixedColumn, mFixedmRow, 9, VectorXY::Zero, 0.2);
//		mAnimator->FnCreateAnimation(L"Idle_R", mImage, VectorXY(0.0f, 0.0f), mFixedColumn, mFixedmRow, 9, VectorXY::Zero, 0.2);
//
//		// Move
//		mAnimator->FnCreateAnimation(L"Move_L", mImage, VectorXY(0.0f, 1800.0f), mFixedColumn, mFixedmRow, 5, VectorXY::Zero, 0.2);
//		mAnimator->FnCreateAnimation(L"Move_R", mImage, VectorXY(0.0f, 1200.0f), mFixedColumn, mFixedmRow, 5, VectorXY::Zero, 0.2);
//
//		// Attack
//		mAnimator->FnCreateAnimation(L"Attack01Down_L", mImage, VectorXY(0.0f, 3000.0f), mFixedColumn, mFixedmRow, 12, VectorXY::Zero, 0.11);
//		mAnimator->FnCreateAnimation(L"Attack02Pressed_L", mImage, VectorXY(1800.0f, 3000.0f), mFixedColumn, mFixedmRow, 9, VectorXY::Zero, 0.11);
//		mAnimator->FnCreateAnimation(L"Attack03Up_L", mImage, VectorXY(7200.0f, 3000.0f), mFixedColumn, mFixedmRow, 3, VectorXY::Zero, 0.11);
//
//		mAnimator->FnCreateAnimation(L"Attack01Down_R", mImage, VectorXY(0.0f, 2400.0f), mFixedColumn, mFixedmRow, 12, VectorXY::Zero, 0.11);
//		mAnimator->FnCreateAnimation(L"Attack02Pressed_R", mImage, VectorXY(1800.0f, 2400.0f), mFixedColumn, mFixedmRow, 9, VectorXY::Zero, 0.11);
//		mAnimator->FnCreateAnimation(L"Attack03Up_R", mImage, VectorXY(7200.0f, 2400.0f), mFixedColumn, mFixedmRow, 3, VectorXY::Zero, 0.11);
//
//		// Jump
//		mAnimator->FnCreateAnimation(L"Jump_L", mImage, VectorXY(0.0f, 4200.0f), mFixedColumn, mFixedmRow, 18, VectorXY::Zero, 0.2);
//		mAnimator->FnCreateAnimation(L"Jump_R", mImage, VectorXY(0.0f, 3600.0f), mFixedColumn, mFixedmRow, 18, VectorXY::Zero, 0.15);
//
//		//mAnimator->FnCreateAnimations(L"..\\Resources\\Chalise\\Idle", Vector2::Zero, 0.1f);
//		//mAnimator->FnGetStartEvent(L"Idle_R") = std::bind(&CRayman::FnIdleCompleteEvent, this);
//
//		//==================================================
//		// Initialize State
//		//==================================================
//		mAnimator->FnPlay(L"Idle_R", true);
//
//		CCollider* collider = FnAddComponent<CCollider>();
//		//collider->FnSetCenter(VectorXY(-60.0f, -80.0f));
//		collider->FnSetCenter(VectorXY(-60.0f, -330.0f));
//		collider->FnSetSize(VectorXY(100.0f, 300.0f));
//
//		mRigidbody = FnAddComponent<CRigidbody>();
//		mRigidbody->FnSetMass(1.0f);
//
//		mState = ERaymanState::Idle;
//		mStateLR = ERaymanState_LR::R;
//
//		CGameObject::Initialize();
//	}//END - void CRayman::Initialize
//
//	void CRayman::Update()
//	{
//		CGameObject::Update();
//
//		switch (mState)
//		{
//		case yha::CRayman::ERaymanState::Idle:
//			FnIdle();
//			break;
//		case yha::CRayman::ERaymanState::Move:
//			FnMove();
//			break;
//		case yha::CRayman::ERaymanState::Attack:
//			FnAttack();
//			break;
//		case yha::CRayman::ERaymanState::Jump:
//			FnJump();
//			break;
//		case yha::CRayman::ERaymanState::BeAttacked:
//			FnBeAttacked();
//			break;
//		case yha::CRayman::ERaymanState::Death:
//			FnDeath();
//			break;
//
//		default:
//			break;
//		}
//
//	}//END - void CRayman::Update
//
//	void CRayman::Render(HDC hdc)
//	{
//		CGameObject::Render(hdc);
//	}
//	void CRayman::Release()
//	{
//		CGameObject::Release();
//	}
//
//	//*****************************************************************
//	// [CRayman] 충돌
//	//*****************************************************************
//	void CRayman::FnOnCollisionEnter(CCollider* Other)
//	{
//
//	}
//
//	void CRayman::FnOnCollisionStay(CCollider* Other)
//	{
//
//	}
//
//	void CRayman::FnOnCollisionExit(CCollider* Other)
//	{
//
//	}
//
//	//*****************************************************************
//	// [CRayman] FSM
//	//*****************************************************************
//	void CRayman::FnIdle()
//	{
//		//==================================================
//		// Idle
//		//==================================================
//		// Move -> Idle
//		if (CInput::FnGetKeyUp(EKeyCode::Right))
//			mAnimator->FnPlay(L"Idle_R", true);
//
//		if (CInput::FnGetKeyUp(EKeyCode::Left))
//			mAnimator->FnPlay(L"Idle_L", true);
//
//		// Attack	-> Idle	: Attack 에서 직접 Idle Animation Play
//		// Jump		-> Idle	: Jump 에서 직접 Idle Animation Play
//
//
//		//==================================================
//		// Idle -> Move
//		//==================================================
//		if (CInput::FnGetKeyDown(EKeyCode::Right)
//			|| CInput::FnGetKeyDown(EKeyCode::Left))
//		{
//			mState = ERaymanState::Move;
//		}
//
//		//==================================================
//		// Idle -> Attack
//		//==================================================
//		if (CInput::FnGetKeyDown(EKeyCode::Alt))
//			mState = ERaymanState::Attack;
//
//		//==================================================
//		// Idle -> Jump
//		//==================================================
//		if (CInput::FnGetKeyDown(EKeyCode::Ctrl))
//			mState = ERaymanState::Jump;
//
//	}//END - void CRayman::FnIdle
//
//	void CRayman::FnMove()
//	{
//		//==================================================
//		// Move
//		//==================================================
//		if (CInput::FnGetKeyDown(EKeyCode::Right)
//			&& (CInput::FnGetKeyState(EKeyCode::Left) != EKeyState::Down)
//			&& (CInput::FnGetKeyState(EKeyCode::Left) != EKeyState::Pressed))
//		{
//			mStateLR = ERaymanState_LR::R;
//			mAnimator->FnPlay(L"Move_R", true);
//		}
//		if (CInput::FnGetKeyDown(EKeyCode::Left)
//			&& (CInput::FnGetKeyState(EKeyCode::Right) != EKeyState::Down)
//			&& (CInput::FnGetKeyState(EKeyCode::Right) != EKeyState::Pressed))
//		{
//			mStateLR = ERaymanState_LR::L;
//			mAnimator->FnPlay(L"Move_L", true);
//		}
//
//		CTransform* Tr = FnGetComponent<CTransform>();
//		VectorXY Pos = Tr->FnGetPos();
//
//		//if (CInput::FnGetKey(EKeyCode::A))
//		if (CInput::FnGetKey(EKeyCode::Left))
//			Pos.X -= 170.0f * CTime::FnDeltaTime();
//
//		//if (CInput::FnGetKey(EKeyCode::D))
//		if (CInput::FnGetKey(EKeyCode::Right))
//			Pos.X += 170.0f * CTime::FnDeltaTime();
//
//		Tr->FnSetPos(Pos);
//
//		//Example - Rigidbody 활용
//		//if (Input::GetKey(eKeyCode::A))
//		//	mRigidbody->AddForce(Vector2(-200.0f, 0.0f));
//		////pos.x -= 100.0f * Time::DeltaTime();
//
//		//if (Input::GetKey(eKeyCode::D))
//		//	mRigidbody->AddForce(Vector2(200.0f, 0.0f));
//		////pos.x += 100.0f * Time::DeltaTime();
//
//		//if (Input::GetKey(eKeyCode::W))
//		//	mRigidbody->AddForce(Vector2(0.0f, -200.0f));
//		////pos.y -= 100.0f * Time::DeltaTime();
//
//		//if (Input::GetKey(eKeyCode::S))
//		//	mRigidbody->AddForce(Vector2(0.0f, +200.0f));
//
//		//==================================================
//		// Move -> Idle
//		//==================================================
//		if (CInput::FnGetKeyUp(EKeyCode::Right)
//			|| CInput::FnGetKeyUp(EKeyCode::Left))
//		{
//			mState = ERaymanState::Idle;
//		}
//
//		//==================================================
//		// Move -> Attack
//		//==================================================
//		if (CInput::FnGetKeyDown(EKeyCode::Alt))
//			mState = ERaymanState::Attack;
//
//		//==================================================
//		// Move -> Jump
//		//==================================================
//		if (CInput::FnGetKeyDown(EKeyCode::Ctrl))
//			mState = ERaymanState::Jump;
//
//	}//END - void CRayman::FnMove
//
//	void CRayman::FnAttack()
//	{
//		//==================================================
//		// Attack
//		//==================================================
//		if (CInput::FnGetKeyDown(EKeyCode::Alt))
//		{
//			if (mStateLR == ERaymanState_LR::L)
//				mAnimator->FnPlay(L"Attack01Down_L", false);
//			else
//				mAnimator->FnPlay(L"Attack01Down_R", false);
//		}
//
//		//==================================================
//		// Attack Animation Loop (Key Pressed)
//		//==================================================
//		if (mStateLR == ERaymanState_LR::L)
//		{// L
//
//			if (mAnimator->FnFindAnimation(L"Attack01Down_L")->FnIsComplete())
//			{
//				mAnimator->FnFindAnimation(L"Attack01Down_L")->FnReset();
//				mAnimator->FnPlay(L"Attack02Pressed_L", true);
//			}
//		}
//		else
//		{// R
//
//			if (mAnimator->FnFindAnimation(L"Attack01Down_R")->FnIsComplete())
//			{
//				mAnimator->FnFindAnimation(L"Attack01Down_R")->FnReset();
//				mAnimator->FnPlay(L"Attack02Pressed_R", true);
//			}
//		}
//
//		//==================================================
//		// Attack -> Idle
//		//==================================================
//		if (CInput::FnGetKeyUp(EKeyCode::Alt))
//		{
//			object::Instantiate<CPunch>(VectorXY(800.0f, 400.0f), ELayerType::Punch);
//
//			if (mStateLR == ERaymanState_LR::L)
//				mAnimator->FnPlay(L"Attack03Up_L", false);
//			else
//				mAnimator->FnPlay(L"Attack03Up_R", false);
//		}
//
//		if (mStateLR == ERaymanState_LR::L)
//		{// L
//
//			if (mAnimator->FnFindAnimation(L"Attack03Up_L")->FnIsComplete())
//			{
//				mAnimator->FnFindAnimation(L"Attack03Up_L")->FnReset();
//
//				mState = ERaymanState::Idle;
//				mAnimator->FnPlay(L"Idle_L", true);
//			}
//		}
//		else
//		{// R
//
//			if (mAnimator->FnFindAnimation(L"Attack03Up_R")->FnIsComplete())
//			{
//				mAnimator->FnFindAnimation(L"Attack03Up_R")->FnReset();
//
//				mState = ERaymanState::Idle;
//				mAnimator->FnPlay(L"Idle_R", true);
//			}
//		}
//
//	}//END- void CRayman::FnAttack
//
//	void CRayman::FnJump()
//	{
//		//==================================================
//		// Jump
//		//==================================================
//
//		if (mFlagJumpOnce == false)
//		{
//			if (CInput::FnGetKeyDown(EKeyCode::Ctrl))
//			{
//				mFlagJumpOnce = true;
//
//				// 중력 적용
//				VectorXY Velocity = mRigidbody->FnGetVelocity();
//				Velocity.Y -= 900.0f;
//
//				mRigidbody->FnSetVelocity(Velocity);
//				mRigidbody->FnSetGround(false);
//
//				// Jump Animation Play Once
//				if (mStateLR == ERaymanState_LR::L)
//					mAnimator->FnPlay(L"Jump_L", false);
//				else
//					mAnimator->FnPlay(L"Jump_R", false);
//			}
//		}
//
//		// TODO : 점프 중 좌우 상태 변경
//		CTransform* Tr = FnGetComponent<CTransform>();
//		VectorXY Pos = Tr->FnGetPos();
//
//		if (CInput::FnGetKey(EKeyCode::Left))
//		{
//			Pos.X -= 170.0f * CTime::FnDeltaTime();
//			mStateLR = ERaymanState_LR::L;
//			//mAnimator->FnPlay(L"Jump_L", false);
//		}
//
//		if (CInput::FnGetKey(EKeyCode::Right))
//		{
//			Pos.X += 170.0f * CTime::FnDeltaTime();
//			mStateLR = ERaymanState_LR::R;
//			//mAnimator->FnPlay(L"Jump_R", false);
//		}
//
//
//		Tr->FnSetPos(Pos);
//
//		//==================================================
//		// Jump -> Idle
//		//==================================================
//		if (mStateLR == ERaymanState_LR::L)
//		{// L
//
//			if (mAnimator->FnFindAnimation(L"Jump_L")->FnIsComplete())
//			{
//				mAnimator->FnFindAnimation(L"Jump_L")->FnReset();
//				mFlagJumpOnce = false;
//
//				mState = ERaymanState::Idle;
//				mAnimator->FnPlay(L"Idle_L", true);
//			}
//		}
//		else
//		{// R
//
//			if (mAnimator->FnFindAnimation(L"Jump_R")->FnIsComplete())
//			{
//				mAnimator->FnFindAnimation(L"Jump_R")->FnReset();
//				mFlagJumpOnce = false;
//
//				mState = ERaymanState::Idle;
//				mAnimator->FnPlay(L"Idle_R", true);
//			}
//		}
//	}//END - void CRayman::FnJump
//
//	void CRayman::FnBeAttacked()
//	{
//
//	}
//	void CRayman::FnDeath()
//	{
//	}
//
//
//	void CRayman::FnIdleCompleteEvent(/*const Cuphead* this*/)
//	{
//		//mState =
//		//Transform* tr = GetComponent<Transform>();
//		//Scene* curScene = SceneManager::GetActiveScene();
//		//BaseBullet* bullet = new BaseBullet();
//		//bullet->GetComponent<Transform>()->SetPos(tr->GetPos());
//		//curScene->AddGameObeject(bullet, eLayerType::Bullet);
//	}
//}