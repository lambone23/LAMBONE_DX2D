#include "CBoard.h"

#include "CCards.h"
#include "CSunLights.h"
#include "CPlants.h"

extern yha::CApplication MyApplication;

namespace yha
{
	CBoard::CBoard()
	{
	}
	CBoard::~CBoard()
	{
	}

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