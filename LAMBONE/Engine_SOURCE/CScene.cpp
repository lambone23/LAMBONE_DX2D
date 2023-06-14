#include "CScene.h"

#include "CConstantBuffer.h"

namespace yha
{
	CScene::CScene()
	{
		srand((unsigned int)time(NULL));
		int randomFirst = rand();

		Vector4 player_Pos(0.0f, 0.0f, 0.0f, 0.0f);
		Vector4 player_Color(1.0f, 1.0f, 1.0f, 1.0f);
		float player_Size = 0.05;

		mGameObjects.push_back(
			new CGameObject
			(
				enums::eGameObjectType::Player
				, player_Pos
				, player_Color
				, player_Size
				, this
			));

		for (int i = 0; i < 50; i++)
		{
			int randPosX = rand() % 50;
			int randPosY = rand() % 50;
			int randXSign = rand() % 2;
			int randYSign = rand() % 2;

			if (randXSign) randPosX *= -1;
			if (randYSign) randPosY *= -1;

			float randColorPrey = (float)(rand() % 10) / 10.f;
			if (0.0f == randColorPrey)
				randColorPrey = 0.5f;

			Vector4 prey_Pos((float)randPosX / 50.f, (float)randPosY / 50.f, 0.0f, 0.0f);
			Vector4 prey_Color(0.0f, randColorPrey, randColorPrey, 1.0f);
			float prey_Size = 0.02;

			mGameObjects.push_back(
				new CGameObject(
					enums::eGameObjectType::Prey
					, prey_Pos
					, prey_Color
					, prey_Size
					, this
				));
		}
	}
	CScene::~CScene()
	{

	}

	void CScene::FnInitialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅

	}

	void CScene::FnUpdate()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			CGameObject::eState gameObjState = gameObj->FnGetState();

			if (gameObjState != CGameObject::eState::Dead)
				gameObj->FnUpdate();
		}
	}

	void CScene::FnLateUpdate()
	{
	}
	void CScene::FnRender()
	{
		for (CGameObject* gameObj : mGameObjects)
		{
			CGameObject::eState gameObjState = gameObj->FnGetState();

			if (gameObjState != CGameObject::eState::Dead)
				gameObj->FnRender();
		}
	}
}
