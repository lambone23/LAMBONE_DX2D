#include "CZombies.h"

namespace yha
{
	CGameObject* CZombies::mZb_NormalZombie = nullptr;
	CCollider2D* CZombies::cd_NormalZombie = nullptr;
	CAnimator* CZombies::at_NormalZombie = nullptr;
	bool CZombies::FlagNormalZombie = false;
	bool CZombies::FlagNormalZombieOnceIdleDid = false;

	CZombies::CZombies()
	{
	}
	CZombies::~CZombies()
	{
	}

	void CZombies::FnInitialize()
	{
		//==================================================================
		// NormalZombie
		//==================================================================
#pragma region Resource_Zombies_NormalZombie
		mZb_NormalZombie = object::FnInstantiate<CGameObject>(Vector3(100.0f, 0.f, 0.2f), eLayerType::Monster);
		mZb_NormalZombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.0f, -1.0f, 0.2f));

		mZb_NormalZombie->FnSetName(L"GrassDay_NormalZombie");

		cd_NormalZombie = mZb_NormalZombie->FnAddComponent<CCollider2D>();
		cd_NormalZombie->FnSetSize(Vector2(0.2f, 0.53f));
		//cd_NormalZombie->FnSetCenter(Vector2(0.09f, -0.05f));

		CMeshRenderer* mr = mZb_NormalZombie->FnAddComponent<CMeshRenderer>();
		mr->FnSetMesh(CResources::FnFind<CMesh>(L"RectMesh"));
		mr->FnSetMaterial(CResources::FnFind<CMaterial>(L"SpriteAnimaionMaterial"));

		// Animation
		at_NormalZombie = mZb_NormalZombie->FnAddComponent<CAnimator>();

		// Idle
		std::shared_ptr<CTexture> atlas_NormalZombie_Idle = CResources::FnLoad<CTexture>(L"NormalZombie_Idle", L"..\\Resources\\Texture\\MyGame\\Zombies\\NormalZombie\\NormalZombie_Idle.png");
		at_NormalZombie->FnCreate(
			L"Idle"						// name
			, atlas_NormalZombie_Idle	// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(5478.f / 22.f, 216.f)	// size
			, 22						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		// Attack
		std::shared_ptr<CTexture> atlas_NormalZombie_Attack = CResources::FnLoad<CTexture>(L"NormalZombie_Attack", L"..\\Resources\\Texture\\MyGame\\Zombies\\NormalZombie\\NormalZombie_Attack.png");
		at_NormalZombie->FnCreate(
			L"Attack"					// name
			, atlas_NormalZombie_Attack	// atlas
			, Vector2(0.0f, 0.0f)		// leftTop
			, Vector2(5229.f / 21.f, 216.f)	// size
			, 21						// columnLength
			, Vector2::Zero				// offset
			, 0.08f						// duration
		);

		at_NormalZombie->FnPlayAnimation(L"Idle", true);
		mZb_NormalZombie->FnAddComponent<CPlayerScript>();
#pragma endregion
	}//END-void CZombies::FnInitialize


	void CZombies::FnManageFSM()
	{
	}//END-void CZombies::FnManageFSM



	void CZombies::FnManageCollider()
	{
		//==================================================================
		// Zombies
		//==================================================================
		//-------------------------------------
		// NormalZombie Status
		//-------------------------------------
		if (false == FlagNormalZombie)
		{
			mZb_NormalZombie->FnGetComponent<CTransform>()->FnSetPosition(Vector3(2.0f, -1.0f, POS_Z_FRONT_1));
			FlagNormalZombie = true;
		}

		/*			if (eColliderStateType::Start == cd_NormalZombie->FnGetColliderState())
					{
						if (eColliderStateType::Start == cd_Peashooter1->FnGetColliderState())
						{
							at_NormalZombie->FnPlayAnimation(L"Idle", true);
						}
						else
						{
							at_NormalZombie->FnPlayAnimation(L"Attack", true);
							FlagNormalZombieOnceIdleDid = false;
						}

					}
					else */
		if (eColliderStateType::Ing == cd_NormalZombie->FnGetColliderState() && false == FlagNormalZombieOnceIdleDid)
		{
			FlagNormalZombieOnceIdleDid = true;
			at_NormalZombie->FnPlayAnimation(L"Attack", true);
		}
		else if (eColliderStateType::Fin == cd_NormalZombie->FnGetColliderState() && true == FlagNormalZombieOnceIdleDid)
		{
			FlagNormalZombieOnceIdleDid = false;
			at_NormalZombie->FnPlayAnimation(L"Idle", true);
		}
	}//END-void CZombies::FnManageCollider


}