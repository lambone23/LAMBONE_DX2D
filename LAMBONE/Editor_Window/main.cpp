﻿// Editor_Window.cpp : 애플리케이션에 대한 진입점을 정의합니다.

#include "framework.h"
#include "Editor_Window.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "..\Engine_SOURCE\CApplication.h"
#include "..\Engine_SOURCE\CRenderer.h"
#include "..\Engine_SOURCE\CResources.h"
#include "..\Engine_SOURCE\CFmod.h"
#include "..\Engine_SOURCE\CFontWrapper.h"

//#include "CSceneManager.h"
#include "LoadScenes.h"
#include "CGuiEditor.h"

//#include <atlstr.h>

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\ZEngine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\ZEngine.lib")
#endif

yha::CApplication MyApplication;

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(169942);
    //SetProcessDPIAware(); // 모니터 배율 영향 X - But 화면 사이즈가 작아진다.

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_EDITORWINDOW, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_EDITORWINDOW));

    MSG msg;
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 여기서 게임 로직이 돌아가야한다.
            MyApplication.FnRun();
            gui::Editor::FnRun();
            MyApplication.FnPresent();
        }
    }

    renderer::FnRelease();
    yha::CSceneManager::FnRelease();
    yha::CFmod::FnRelease();
    yha::CFontWrapper::FnRelease();
    gui::Editor::FnRelease();

    return (int)msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {};

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_EDITORWINDOW));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    // ■Chk - 하단 공백
    //default //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_EDITORWINDOW);
    //wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_STATIC);
    wcex.lpszMenuName = NULL;
    
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 1600, 900, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    MyApplication.FnSetWindow(hWnd, 1600, 900);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MyApplication.FnInitialize();
    yha::FnInitializeScenes();
    gui::Editor::FnInitialize();

    return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //HDC hdc;
    //static CString str;
    //static POINT MousePos;

    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 메뉴 선택을 구문 분석합니다:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    //case WM_MOUSEMOVE: //마우스 움직일 경우 메시지
    //    MousePos.x = LOWORD(lParam); //x좌표를 받는다.
    //    MousePos.y = HIWORD(lParam); //y좌표를 받는다.

    //    //마우스 좌표의 정수값을 문자열로 변환하여 저장
    //    str.Format(_T("X좌표: %d Y좌표: %d"), MousePos.x, MousePos.y); //현재 마우스의 위치값을 문자열로 변환한다.
    //    //그리기 위해서 DC를 얻어옴
    //    hdc = GetDC(hWnd);
    //    //마우스가 움직일 때마다 현재 마우스위치를 받아온다.
    //    TextOut(hdc, 0, 0, str, lstrlen(str)); //문자열로 변환한 마우스 좌표값을 출력한다.
    //    ReleaseDC(hWnd, hdc);//그리기 영역 해제
    //    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
