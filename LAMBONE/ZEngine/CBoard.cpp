#include "CBoard.h"

#include "CCards.h"
#include "CSunLights.h"
#include "CPlants.h"
#include "CJalapeno.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CBoard::CBoard()
	{

	}
	CBoard::~CBoard()
	{
	}

	void CBoard::FnMouseOverEvent()
	{
		bool flagDo = CCards::FnGetFlagIsCardSelected();
		bool flagDo2 = CCommonObjects::FnGetFlagIsShovelSelected();

		if (flagDo)
			FnShowTmpPosition();
		else
		{
			CCommonObjects::mUI_PositionRuler_H->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_PositionRuler_V->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

			CCommonObjects::mUI_SignX->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_Sunflower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		}

		if(flagDo2)
			FnShowTmpRemovePosition();

	}//END-void CBoard::FnMouseOverEvent

	void CBoard::FnShowTmpPosition()
	{
		ePlantsType plantsType = CCards::FnGetPickedCardType();

		float x = 0.f;
		float y = 0.f;

		int xIdx = 0.f;
		int yIdx = 0.f;

		bool flagDoY = true;
		bool flagDo2 = true;

		HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		::POINT MousePos = {};
		::GetCursorPos(&MousePos);
		::ScreenToClient(Tmp_mHwnd, &MousePos);

		if (BOARD_X_1)
		{
			x = -1.7f;
			xIdx = 0;
		}
		else if (BOARD_X_2)
		{
			x = -1.1f;
			xIdx = 1;
		}
		else if (BOARD_X_3)
		{
			x = -0.4f;
			xIdx = 2;
		}
		else if (BOARD_X_4)
		{
			x = 0.2f;
			xIdx = 3;
		}
		else if (BOARD_X_5)
		{
			x = 0.8f;
			xIdx = 4;
		}
		else if (BOARD_X_6)
		{
			x = 1.5f;
			xIdx = 5;
		}
		else if (BOARD_X_7)
		{
			x = 2.1f;
			xIdx = 6;
		}
		else if (BOARD_X_8)
		{
			x = 2.7f;
			xIdx = 7;
		}
		else if (BOARD_X_9)
		{
			x = 3.3f;
			xIdx = 8;
		}
		else
		{
			flagDoY = false;
		}

		if (flagDoY)
		{
			if (BOARD_Y_1)
			{
				y = 1.3f;
				yIdx = 0;
			}
			else if (BOARD_Y_2)
			{
				y = 0.6f;
				yIdx = 1;
			}
			else if (BOARD_Y_3)
			{
				y = -0.2f;
				yIdx = 2;
			}
			else if (BOARD_Y_4)
			{
				y = -1.f;
				yIdx = 3;
			}
			else if (BOARD_Y_5)
			{
				y = -1.7f;
				yIdx = 4;
			}
			else
			{
				flagDo2 = false;
			}

			if (flagDo2)
			{
				int idx = 0;

				switch (yIdx)
				{
				case 0:
					idx = xIdx;
					break;
				case 1:
					idx = 9 + xIdx;
					break;
				case 2:
					idx = 18 + xIdx;
					break;
				case 3:
					idx = 27 + xIdx;
					break;
				case 4:
					idx = 36 + xIdx;
					break;
				}

				bool chkIsPlantsNow = CPlants::mPlants[idx].isPlanted;

				//==================================================================
				// 해당 칸에 식물이 있는 상태
				//==================================================================
				if (chkIsPlantsNow)
				{
					Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
					posNumbSet = CCommonObjects::FnGetPosition(idx);
					posNumbSet.z = POS_Z_FRONT_2;

					CCommonObjects::mUI_SignX->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);

					CCommonObjects::mUI_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
					CCommonObjects::mUI_Sunflower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
					CCommonObjects::mUI_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
					CCommonObjects::mUI_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
					CCommonObjects::mUI_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
					CCommonObjects::mUI_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
					CCommonObjects::mUI_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
				}
				else
				{
					Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
					posNumbSet = CCommonObjects::FnGetPosition(idx);
					posNumbSet.z = POS_Z_FRONT_2;

					CCommonObjects::mUI_SignX->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

					switch (plantsType)
					{
					case yha::enums::ePlantsType::Sunflower:
						CCommonObjects::mUI_Sunflower->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
						break;
					case yha::enums::ePlantsType::WallNut:
						CCommonObjects::mUI_WallNut->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
						break;
					case yha::enums::ePlantsType::PeaShooter:
						CCommonObjects::mUI_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
						break;
					case yha::enums::ePlantsType::Chomper:
						posNumbSet.x += 0.2f;
						posNumbSet.y += 0.1f;
						CCommonObjects::mUI_Chomper->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
						break;
					case yha::enums::ePlantsType::Jalapeno:
						CCommonObjects::mUI_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
						break;
					case yha::enums::ePlantsType::CherryBomb:
						CCommonObjects::mUI_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
						break;
					}
				}

				CCommonObjects::mUI_PositionRuler_H->FnGetComponent<CTransform>()->FnSetPosition(Vector3(0.8f, y, POS_Z_DEFAULT));
				CCommonObjects::mUI_PositionRuler_V->FnGetComponent<CTransform>()->FnSetPosition(Vector3(x, -0.2f, POS_Z_DEFAULT));
			}//end-if (flagDo2)
		}//end-if (flagDoY)

		if (!flagDoY || !flagDo2)
		{
			CCommonObjects::mUI_PositionRuler_H->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_PositionRuler_V->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);

			CCommonObjects::mUI_SignX->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_Sunflower->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_WallNut->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_PeaShooter->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_Chomper->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_Jalapeno->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
			CCommonObjects::mUI_CherryBomb->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
		}
	}//END-void CBoard::FnShowTmpPosition

	void CBoard::FnShowTmpRemovePosition()
	{
		int xIdx = 0.f;
		int yIdx = 0.f;

		bool flagDoY = true;
		bool flagDo2 = true;

		HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
		::POINT MousePos = {};
		::GetCursorPos(&MousePos);
		::ScreenToClient(Tmp_mHwnd, &MousePos);

		if (BOARD_X_1)
			xIdx = 0;
		else if (BOARD_X_2)
			xIdx = 1;
		else if (BOARD_X_3)
			xIdx = 2;
		else if (BOARD_X_4)
			xIdx = 3;
		else if (BOARD_X_5)
			xIdx = 4;
		else if (BOARD_X_6)
			xIdx = 5;
		else if (BOARD_X_7)
			xIdx = 6;
		else if (BOARD_X_8)
			xIdx = 7;
		else if (BOARD_X_9)
			xIdx = 8;
		else
			flagDoY = false;

		if (flagDoY)
		{
			if (BOARD_Y_1)
				yIdx = 0;
			else if (BOARD_Y_2)
				yIdx = 1;
			else if (BOARD_Y_3)
				yIdx = 2;
			else if (BOARD_Y_4)
				yIdx = 3;
			else if (BOARD_Y_5)
				yIdx = 4;
			else
				flagDo2 = false;

			if (flagDo2)
			{
				int idx = 0;

				switch (yIdx)
				{
				case 0:
					idx = xIdx;
					break;
				case 1:
					idx = 9 + xIdx;
					break;
				case 2:
					idx = 18 + xIdx;
					break;
				case 3:
					idx = 27 + xIdx;
					break;
				case 4:
					idx = 36 + xIdx;
					break;
				}

				Vector3 posNumbSet = Vector3(0.f, 0.f, 0.f);
				posNumbSet = CCommonObjects::FnGetPosition(idx);
				posNumbSet.x += 0.3f;
				posNumbSet.y -= 0.06f;
				posNumbSet.z = POS_Z_FRONT_2;

				CCommonObjects::mUI_Shovel->FnGetComponent<CTransform>()->FnSetPosition(posNumbSet);
			}//end-if (flagDo2)
		}//end-if (flagDoY)
		else
			CCommonObjects::mUI_Shovel->FnGetComponent<CTransform>()->FnSetPosition(POSITION_CLEAR);
	}//END-void CBoard::FnShowTmpRemovePosition
	
	void CBoard::FnClickEvent()
	{
		if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
		{
			HWND Tmp_mHwnd = MyApplication.FnGetHwnd();
			::POINT MousePos = {};
			::GetCursorPos(&MousePos);
			::ScreenToClient(Tmp_mHwnd, &MousePos);

			int idx = 0;			// 클릭 위치 확인용
			bool flagDo = false;	// 클릭에 따른 처리 여부

			//==================================================================
			// 가로(horizontal row)		1번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_1
			if (BOARD_X_1 && BOARD_Y_1)
			{
				idx = 0;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_1)
			{
				idx = 1;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_1)
			{
				idx = 2;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_1)
			{
				idx = 3;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_1)
			{
				idx = 4;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_1)
			{
				idx = 5;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_1)
			{
				idx = 6;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_1)
			{
				idx = 7;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_1)
			{
				idx = 8;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		2번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_2
			if (BOARD_X_1 && BOARD_Y_2)
			{
				idx = 9;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_2)
			{
				idx = 10;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_2)
			{
				idx = 11;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_2)
			{
				idx = 12;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_2)
			{
				idx = 13;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_2)
			{
				idx = 14;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_2)
			{
				idx = 15;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_2)
			{
				idx = 16;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_2)
			{
				idx = 17;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		3번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_3
			if (BOARD_X_1 && BOARD_Y_3)
			{
				idx = 18;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_3)
			{
				idx = 19;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_3)
			{
				idx = 20;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_3)
			{
				idx = 21;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_3)
			{
				idx = 22;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_3)
			{
				idx = 23;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_3)
			{
				idx = 24;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_3)
			{
				idx = 25;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_3)
			{
				idx = 26;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		4번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_4
			if (BOARD_X_1 && BOARD_Y_4)
			{
				idx = 27;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_4)
			{
				idx = 28;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_4)
			{
				idx = 29;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_4)
			{
				idx = 30;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_4)
			{
				idx = 31;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_4)
			{
				idx = 32;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_4)
			{
				idx = 33;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_4)
			{
				idx = 34;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_4)
			{
				idx = 35;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 가로(horizontal row)		5번째
			// 세로(vertical column)	9개의 열
			//==================================================================
#pragma region Y_5
			if (BOARD_X_1 && BOARD_Y_5)
			{
				idx = 36;
				flagDo = true;
			}

			if (BOARD_X_2 && BOARD_Y_5)
			{
				idx = 37;
				flagDo = true;
			}

			if (BOARD_X_3 && BOARD_Y_5)
			{
				idx = 38;
				flagDo = true;
			}

			if (BOARD_X_4 && BOARD_Y_5)
			{
				idx = 39;
				flagDo = true;
			}

			if (BOARD_X_5 && BOARD_Y_5)
			{
				idx = 40;
				flagDo = true;
			}

			if (BOARD_X_6 && BOARD_Y_5)
			{
				idx = 41;
				flagDo = true;
			}

			if (BOARD_X_7 && BOARD_Y_5)
			{
				idx = 42;
				flagDo = true;
			}

			if (BOARD_X_8 && BOARD_Y_5)
			{
				idx = 43;
				flagDo = true;
			}

			if (BOARD_X_9 && BOARD_Y_5)
			{
				idx = 44;
				flagDo = true;
			}
#pragma endregion

			//==================================================================
			// 선택 위치별 처리
			// - SunLight 클릭 처리
			// - 식물 심기 또는 뽑기
			//==================================================================
			if (flagDo)
			{
				//-------------------------------------
				// 클릭 처리 - SunLight
				//-------------------------------------
				CSunLights::FnClickEvent(idx, MousePos);

				//-------------------------------------
				// 심기
				//-------------------------------------
				if (true == CCards::FnGetFlagIsCardSelected()					// 카드	: O
					&& false == CCommonObjects::FnGetFlagIsShovelSelected())	// 삽	: X
				{
					CPlants::FnPutPlants(idx);
				}
				//-------------------------------------
				// 뽑기
				//-------------------------------------
				else if (true == CCommonObjects::FnGetFlagIsShovelSelected()	// 삽	: O
					&& false == CCards::FnGetFlagIsCardSelected())				// 카드	: X
				{
					CPlants::FnRemove(idx);
				}
			}//end-if (flagDo)

		}//end-if (CInput::FnGetKeyDown(eKeyCode::LBUTTON))
	}//END-void CBoard::FnClickEvent

	void CBoard::FnDraw()
	{
		bool flagDoDraw = false;

		for (int idx = 0; idx < MAX_PLANTS; idx++)
		{
			// 그리기 여부 확인
			if (true == CPlants::mPlants[idx].isPlanted)
				flagDoDraw = true;
			else
				continue;

			// 게임판 그리기 - 식물이 심어진 곳만
			if (flagDoDraw)
			{
				CPlants::FnColliderTotalManager(idx);
				CPlants::FnFsmTotalManager(idx);
			}
		}
	}//END-void CBoard::FnDraw
}